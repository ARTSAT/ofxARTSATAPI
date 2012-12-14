/*
**      ARTSAT Project
**
**      Original Copyright (C) 2011 - 2012 HORIGUCHI Junshi.
**                                          http://iridium.jp/
**                                          zap00365@nifty.com
**      Portions Copyright (C) <year> <author>
**                                          <website>
**                                          <e-mail>
**      Version     openFrameworks
**      Website     http://artsat.jp/
**      E-mail      info@artsat.jp
**
**      This source code is for Xcode.
**      Xcode 4.2 (LLVM compiler 3.0)
**
**      ofxSATLocalDB.cpp
**
**      ------------------------------------------------------------------------
**
**      THE SOURCE CODE AND THE BINARY OF ARTSAT API IS DISTRIBUTED UNDER THE MIT LICENSE WRITTEN BELOW.
**      THE LICENSE OF ANY DATA GOTTEN THROUGH ARTSAT API FOLLOWS PROVIDED LICENSE ON EACH SATELLITE.
**
**      ARTSAT API のソースコードとバイナリは下記に示す MIT ライセンスの元で配布されます。
**      ARTSAT API を通して取得できるデータのライセンスに関してはデータの提供元となる各衛星の定めるライセンスに準じます。
**
**      The MIT License (MIT)
**
**      Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
**      associated documentation files (the "Software"), to deal in the Software without restriction,
**      including without limitation the rights to use, copy, modify, merge, publish, distribute,
**      sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
**      furnished to do so, subject to the following conditions:
**      The above copyright notice and this permission notice shall be included in all copies or
**      substantial portions of the Software.
**      THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
**      BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
**      IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
**      WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
**      OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
**      以下に定める条件に従い、本ソフトウェアおよび関連文書のファイル（以下「ソフトウェア」）の複製を
**      取得するすべての人に対し、ソフトウェアを無制限に扱うことを無償で許可します。
**      これには、ソフトウェアの複製を使用、複写、変更、結合、掲載、頒布、サブライセンス、および、または販売する権利、
**      およびソフトウェアを提供する相手に同じことを許可する権利も無制限に含まれます。
**      上記の著作権表示および本許諾表示を、ソフトウェアのすべての複製または重要な部分に記載するものとします。
**      ソフトウェアは「現状のまま」で、明示であるか暗黙であるかを問わず、何らの保証もなく提供されます。
**      ここでいう保証とは、商品性、特定の目的への適合性、および権利非侵害についての保証も含みますが、それに限定されるものではありません。
**      作者または著作権者は、契約行為、不法行為、またはそれ以外であろうと、ソフトウェアに起因または関連し、
**      あるいはソフトウェアの使用またはその他の扱いによって生じる一切の請求、損害、その他の義務について何らの責任も負わないものとします。
*/

#include "ofxSATLocalDB.h"
#include "ofUtils.h"

#define REPLACE_FROM            ("://")
#define REPLACE_TO              ("-")
#define SQL_DIRECTORY           ("telemetry")
#define SQL_EXTENSION           (".002.db")
#define SQL_TIME                ("%YYYY-%MM-%DD %hh:%mm:%ss")

/*protected */ofxSATLocalDB::ofxSATLocalDB(void) : _sql(NULL)
{
}

/*protected virtual */ofxSATLocalDB::~ofxSATLocalDB(void)
{
    cleanup();
}

/*protected virtual */ofxSATError ofxSATLocalDB::setup(void)
{
    ofxSATError error(SATERROR_OK);
    
    if ((error = super::setup()) == SATERROR_OK) {
        if ((error = openSQL()) == SATERROR_OK) {
            // nop
        }
        if (error != SATERROR_OK) {
            super::cleanup();
        }
    }
    return error;
}

/*protected virtual */void ofxSATLocalDB::cleanup(void)
{
    closeSQL();
    super::cleanup();
    return;
}

/*protected */ofxSATError ofxSATLocalDB::beginSQLTransaction(void) const
{
    ofxSATError error(SATERROR_OK);
    
    if (_sql != NULL) {
        if (_sql->simpleQuery("BEGIN TRANSACTION;") != SQLITE_OK) {
            error = SATERROR_FAILED;
        }
    }
    else {
        error = SATERROR_INVALID_STATE;
    }
    return error;
}

/*protected */void ofxSATLocalDB::endSQLTransaction(void) const
{
    if (_sql != NULL) {
        _sql->simpleQuery("END TRANSACTION;");
    }
    return;
}

/*protected */ofxSATError ofxSATLocalDB::makeSQLTable(std::string const& table, std::string const& content) const
{
    ofxSATError error(SATERROR_OK);
    
    if (_sql != NULL) {
        if (_sql->simpleQuery(("CREATE TABLE IF NOT EXISTS " + table + "(" + content + ");").c_str()) != SQLITE_OK) {
            error = SATERROR_FAILED;
        }
    }
    else {
        error = SATERROR_INVALID_STATE;
    }
    return error;
}

/*protected */ofxSATError ofxSATLocalDB::optimizeSQL(void) const
{
    ofxSATError error(SATERROR_OK);
    
    if (_sql != NULL) {
        if (_sql->simpleQuery("VACUUM;") != SQLITE_OK) {
            error = SATERROR_FAILED;
        }
    }
    else {
        error = SATERROR_INVALID_STATE;
    }
    return error;
}

/*protected static */std::string ofxSATLocalDB::convertToSQLTime(ofxSATTime const& param)
{
    return param.format(SQL_TIME);
}

/*protected static */ofxSATError ofxSATLocalDB::convertSQLTimeTo(std::string const& string, ofxSATTime* result)
{
    ofxSATTime time;
    ofxSATError error(SATERROR_OK);
    
    if (result != NULL) {
        if ((error = time.parse(SQL_TIME, string)) == SATERROR_OK) {
            *result = time;
        }
    }
    else {
        error = SATERROR_INVALID_PARAM;
    }
    return error;
}

/*private */ofxSATError ofxSATLocalDB::openSQL(void)
{
    std::string path;
    ofxSATError error(SATERROR_OK);
    
    if (_sql != NULL) {
        if (_id != getID()) {
            closeSQL();
        }
    }
    if (_sql == NULL) {
        if (!getID().empty()) {
            path = ofToDataPath("");
            #if TARGET_OS_IPHONE
            path = ofFilePath::join(ofFilePath::getEnclosingDirectory(path), "Library");
            #endif
            path = ofFilePath::join(path, SQL_DIRECTORY);
            if (!ofDirectory::doesDirectoryExist(path, false)) {
                if (!ofDirectory::createDirectory(path, false)) {
                    error = SATERROR_FAILED;
                }
            }
            if (error == SATERROR_OK) {
                path = ofFilePath::join(path, replaceString(getID(), REPLACE_FROM, REPLACE_TO) + SQL_EXTENSION);
                if (sqlite3_threadsafe() == 1) {
                    if ((_sql = new ofxSQLite(path)) != NULL) {
                        _id = getID();
                    }
                    else {
                        error = SATERROR_NO_MEMORY;
                    }
                }
                else {
                    ofLogError() << "ofxSATLocalDB::openSQL(" << getID() << ") [sqlite3_threadsafe() != 1]";
                    error = SATERROR_INVALID_STATE;
                }
            }
        }
        else {
            error = SATERROR_INVALID_STATE;
        }
    }
    return error;
}

/*private */void ofxSATLocalDB::closeSQL(void)
{
    if (_sql != NULL) {
        _sql->simpleQuery("END TRANSACTION;");
        _sql->simpleQuery("VACUUM;");
        delete _sql;
    }
    _sql = NULL;
    return;
}
