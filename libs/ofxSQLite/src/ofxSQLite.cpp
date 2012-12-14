/*
**      ofxSQLite addon
**
**      Original Copyright (C) 2010 - 2012 Diederick Huijbers.
**                                          http://www.roxlu.com/
**                                          info@roxlu.com
**
**      ofxSQLite.cpp
**
**      ------------------------------------------------------------------------
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
*/

#include "ofxSQLite.h"
#include "ofxSQLiteInsert.h"
#include "ofxSQLiteUpdate.h"
#include "ofxSQLiteDelete.h"
#include "ofxSQLiteSelect.h"
//#include "ofxSQLiteSimpler.h"

ofxSQLite::ofxSQLite()
:db_name("")
{
}

// @deprecated, use setup()
ofxSQLite::ofxSQLite(std::string sDB):db_name(sDB) {
	// 007 breaks using ofToDataPath()
	//db_file = ofToDataPath(db_name,true);
	setup(sDB);
}

void ofxSQLite::setup(std::string sDB) {
	db_name = sDB;
	db_file  = sDB; 
	if (SQLITE_OK != sqlite3_open(db_file.c_str(), &db)) {
		cout << sqlite3_errmsg(db);
		exit(1);
	}
	cout << "opened:" << db_file << endl;
}

int ofxSQLite::simpleQuery(const char* pSQL) {
	sqlite3_stmt* statement;
	if (SQLITE_OK != sqlite3_prepare_v2(db, pSQL,-1, &statement, 0)) {
        sqlite3_finalize(statement);
		return sqlite3_errcode(db);
	}
	while(SQLITE_ROW == sqlite3_step(statement));
	return sqlite3_finalize(statement);
}

ofxSQLiteInsert ofxSQLite::insert(std::string sTable) {
	ofxSQLiteInsert insert = ofxSQLiteInsert(db, sTable);
	return insert;
}
ofxSQLiteUpdate ofxSQLite::update(std::string sTable) {
	return ofxSQLiteUpdate(db, sTable);
}

ofxSQLiteDelete ofxSQLite::remove(std::string sTable) {
	return ofxSQLiteDelete(db, sTable);
}

ofxSQLiteSelect	ofxSQLite::select(std::string sFields) {
	ofxSQLiteSelect select = ofxSQLiteSelect(db);
	select.select(sFields);
	return select;
}

const char* ofxSQLite::getError() {
	return sqlite3_errmsg(db);
}

int ofxSQLite::lastInsertID() {
	return sqlite3_last_insert_rowid(db);
}

ofxSQLiteSimpler ofxSQLite::operator[](const std::string sKeyValue)  {
	ofxSQLiteSimpler simple(*this, sKeyValue);
	return simple;
}

void ofxSQLite::printTable(std::string sTable) {
	cout << select("*").from(sTable).execute().getResultAsAsciiTable();
}
