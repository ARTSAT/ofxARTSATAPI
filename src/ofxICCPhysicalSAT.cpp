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
**      ofxICCPhysicalSAT.cpp
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

#include "ofxICCPhysicalSAT.h"
#include <float.h>
#include "ofAppRunner.h"

//! @cond
#define DEFAULT_UPDATE          (1)
#define DEFAULT_RETRY           (60)
#define THREAD_SLEEP            (100)

static  ofxICCPhysicalSAT::TableRec const
                                ofxiccphysicalsat_table[] = {
    // TODO: BEGIN
    {// SENSOR_EXAMPLE_X
        .format                 = ofxICCPhysicalSAT::FORMAT_DOUBLE,
        .unit                   = ofxICCPhysicalSAT::UNIT_NONE,
        .doubleHint             = {
            DBL_MIN,
            DBL_MAX
        }
    },
    {// SENSOR_EXAMPLE_Y
        .format                 = ofxICCPhysicalSAT::FORMAT_DOUBLE,
        .unit                   = ofxICCPhysicalSAT::UNIT_NONE,
        .doubleHint             = {
            DBL_MIN,
            DBL_MAX
        }
    }
    // TODO: END
};

/*public */ofxICCPhysicalSAT::ofxICCPhysicalSAT(void)
{
    _update.set(DEFAULT_UPDATE);
    _retry.set(DEFAULT_RETRY);
}

/*public virtual */ofxICCPhysicalSAT::~ofxICCPhysicalSAT(void)
{
    cleanup();
}

/*public */ofxSATError ofxICCPhysicalSAT::setUpdateInterval(ofxSATTimeDiff const& param)
{
    ofxSATError error(SATERROR_OK);
    
    if (!isValid()) {
        _update = param;
    }
    else {
        error = SATERROR_INVALID_STATE;
    }
    return error;
}

/*public */ofxSATError ofxICCPhysicalSAT::setRetryInterval(ofxSATTimeDiff const& param)
{
    ofxSATError error(SATERROR_OK);
    
    if (!isValid()) {
        _retry = param;
    }
    else {
        error = SATERROR_INVALID_STATE;
    }
    return error;
}

/*public virtual */ofxSATError ofxICCPhysicalSAT::getAvailableCount(int* result) const
{
    ofxSATError error(SATERROR_OK);
    
    if ((error = super::getAvailableCount(result)) == SATERROR_NO_SUPPORT) {
        error = SATERROR_OK;
        _mutexValue.lock();
        *result = (_valid) ? (1) : (0);
        _mutexValue.unlock();
    }
    return error;
}

/*public virtual */ofxSATError ofxICCPhysicalSAT::getAvailableCount(ofxSATTime const& begin, ofxSATTime const& end, int* result) const
{
    ofxSATError error(SATERROR_OK);
    
    if ((error = super::getAvailableCount(begin, end, result)) == SATERROR_NO_SUPPORT) {
        error = SATERROR_OK;
        _mutexValue.lock();
        *result = (_valid && begin <= _time && _time < end) ? (1) : (0);
        _mutexValue.unlock();
    }
    return error;
}

/*public virtual */ofxSATError ofxICCPhysicalSAT::getAvailableTime(std::vector<ofxSATTime>* result) const
{
    std::vector<ofxSATTime> temp;
    ofxSATError error(SATERROR_OK);
    
    if ((error = super::getAvailableTime(result)) == SATERROR_NO_SUPPORT) {
        error = SATERROR_OK;
        _mutexValue.lock();
        if (_valid) {
            temp.push_back(_time);
        }
        _mutexValue.unlock();
        *result = temp;
    }
    return error;
}

/*public virtual */ofxSATError ofxICCPhysicalSAT::getAvailableTime(ofxSATTime const& begin, ofxSATTime const& end, std::vector<ofxSATTime>* result) const
{
    std::vector<ofxSATTime> temp;
    ofxSATError error(SATERROR_OK);
    
    if ((error = super::getAvailableTime(begin, end, result)) == SATERROR_NO_SUPPORT) {
        error = SATERROR_OK;
        _mutexValue.lock();
        if (_valid && begin <= _time && _time < end) {
            temp.push_back(_time);
        }
        _mutexValue.unlock();
        *result = temp;
    }
    return error;
}

/*public virtual */ofxSATError ofxICCPhysicalSAT::getSensorFormat(SensorType sensor, FormatEnum* result) const
{
    TableRec const* table;
    ofxSATError error(SATERROR_OK);
    
    if ((error = super::getSensorFormat(sensor, result)) == SATERROR_NO_SUPPORT) {
        error = SATERROR_OK;
        if ((table = getTableBySensor(sensor)) != NULL) {
            *result = table->format;
        }
        else {
            error = SATERROR_INVALID_PARAM;
        }
    }
    return error;
}

/*public virtual */ofxSATError ofxICCPhysicalSAT::getSensorUnit(SensorType sensor, UnitEnum* result) const
{
    TableRec const* table;
    ofxSATError error(SATERROR_OK);
    
    if ((error = super::getSensorUnit(sensor, result)) == SATERROR_NO_SUPPORT) {
        error = SATERROR_OK;
        if ((table = getTableBySensor(sensor)) != NULL) {
            *result = table->unit;
        }
        else {
            error = SATERROR_INVALID_PARAM;
        }
    }
    return error;
}

/*public virtual */ofxSATError ofxICCPhysicalSAT::getSensorMinimum(SensorType sensor, void* result, int size) const
{
    TableRec const* table;
    ofxSATError error(SATERROR_OK);
    
    if ((error = super::getSensorMinimum(sensor, result, size)) == SATERROR_NO_SUPPORT) {
        error = SATERROR_OK;
        if ((table = getTableBySensor(sensor)) != NULL) {
            if ((error = checkSize(table->format, size)) == SATERROR_OK) {
                switch (table->format) {
                    case FORMAT_BOOL:
                        *static_cast<bool*>(result) = false;
                        break;
                    case FORMAT_INT:
                        *static_cast<int*>(result) = table->intHint.lower;
                        break;
                    case FORMAT_DOUBLE:
                        *static_cast<double*>(result) = table->doubleHint.lower;
                        break;
                    case FORMAT_STRING:
                    case FORMAT_OFXSATTIME:
                        error = SATERROR_NO_RESULT;
                        break;
                    default:
                        error = SATERROR_FAILED;
                        break;
                }
            }
        }
        else {
            error = SATERROR_INVALID_PARAM;
        }
    }
    return error;
}

/*public virtual */ofxSATError ofxICCPhysicalSAT::getSensorMaximum(SensorType sensor, void* result, int size) const
{
    TableRec const* table;
    ofxSATError error(SATERROR_OK);
    
    if ((error = super::getSensorMaximum(sensor, result, size)) == SATERROR_NO_SUPPORT) {
        error = SATERROR_OK;
        if ((table = getTableBySensor(sensor)) != NULL) {
            if ((error = checkSize(table->format, size)) == SATERROR_OK) {
                switch (table->format) {
                    case FORMAT_BOOL:
                        *static_cast<bool*>(result) = true;
                        break;
                    case FORMAT_INT:
                        *static_cast<int*>(result) = table->intHint.upper;
                        break;
                    case FORMAT_DOUBLE:
                        *static_cast<double*>(result) = table->doubleHint.upper;
                        break;
                    case FORMAT_STRING:
                    case FORMAT_OFXSATTIME:
                        error = SATERROR_NO_RESULT;
                        break;
                    default:
                        error = SATERROR_FAILED;
                        break;
                }
            }
        }
        else {
            error = SATERROR_INVALID_PARAM;
        }
    }
    return error;
}

/*public virtual */ofxSATError ofxICCPhysicalSAT::getSensorData(SensorType sensor, ofxSATTime const& time, void* result, int size, bool* simulation) const
{
    TableRec const* table;
    // TODO: BEGIN
    double tempExampleX;
    double tempExampleY;
    // TODO: END
    ofxSATError error(SATERROR_OK);
    
    if ((error = super::getSensorData(sensor, time, result, size, simulation)) == SATERROR_NO_SUPPORT) {
        error = SATERROR_OK;
        if ((table = getTableBySensor(sensor)) != NULL) {
            _mutexValue.lock();
            if (_valid && time == _time) {
                // TODO: BEGIN
                tempExampleX = _valueExampleX;
                tempExampleY = _valueExampleY;
                // TODO: END
            }
            else {
                error = SATERROR_NO_RESULT;
            }
            _mutexValue.unlock();
            if (error == SATERROR_OK) {
                if (result != NULL) {
                    if ((error = checkSize(table->format, size)) == SATERROR_OK) {
                        switch (sensor) {
                            // TODO: BEGIN
                            case SENSOR_EXAMPLE_X:
                                if (tempExampleX != NAN) {
                                    *static_cast<double*>(result) = tempExampleX;
                                }
                                else {
                                    error = SATERROR_NO_RESULT;
                                }
                                break;
                            case SENSOR_EXAMPLE_Y:
                                if (tempExampleY != NAN) {
                                    *static_cast<double*>(result) = tempExampleY;
                                }
                                else {
                                    error = SATERROR_NO_RESULT;
                                }
                                break;
                            // TODO: END
                            default:
                                error = SATERROR_FAILED;
                                break;
                        }
                    }
                }
                if (error == SATERROR_OK) {
                    if (simulation != NULL) {
                        *simulation = false;
                    }
                }
            }
        }
        else {
            error = SATERROR_INVALID_PARAM;
        }
    }
    return error;
}

/*public virtual */ofxSATError ofxICCPhysicalSAT::setup(void)
{
    ofxSATError error(SATERROR_OK);
    
    if ((error = super::setup()) == SATERROR_OK) {
        _mutexValue.lock();
        _valid = false;
        _mutexValue.unlock();
        pushCrawl(true);
        startThread();
        if (error != SATERROR_OK) {
            super::cleanup();
        }
    }
    return error;
}

/*public virtual */void ofxICCPhysicalSAT::cleanup(void)
{
    waitForThread();
    super::cleanup();
    return;
}

/*public virtual */ofxSATError ofxICCPhysicalSAT::update(ofxSATTime const& time)
{
    ofxSATError error(SATERROR_OK);
    
    if ((error = super::update(time)) == SATERROR_OK) {
        pushCrawl(true);
    }
    return error;
}

/*private virtual */void ofxICCPhysicalSAT::threadedFunction(void)
{
    ofxSATTime last;
    ofxSATTime now;
    // TODO: BEGIN
    double tempExampleX;
    double tempExampleY;
    // TODO: END
    ofxSATError error(SATERROR_OK);
    
    last = ofxSATTime::currentTime();
    while (isThreadRunning()) {
        if (isValid()) {
            now = ofxSATTime::currentTime();
            if (isImmediate() || error == SATERROR_OK) {
                if (popCrawl()) {
                    
                    // TODO: BEGIN
                    tempExampleX = -ofRandomuf(); // read sensor data from physical device X...
                    tempExampleY = +ofRandomuf(); // read sensor data from physical device Y...
                    // TODO: END
                    
                    _mutexValue.lock();
                    // TODO: BEGIN
                    _valueExampleX = tempExampleX;
                    _valueExampleY = tempExampleY;
                    // TODO: END
                    _time = ofxSATTime::currentTime();
                    _valid = true;
                    _mutexValue.unlock();
                    notifyData(_time);
                    if (!remainsCrawl() || error != SATERROR_OK) {
                        last = ofxSATTime::currentTime();
                        notifyFinish(error);
                    }
                }
                else if (now - last >= _update) {
                    pushCrawl(false);
                }
                else {
                    ofSleepMillis(THREAD_SLEEP);
                }
            }
            else if (now - last >= _retry) {
                error = SATERROR_OK;
            }
            else {
                ofSleepMillis(THREAD_SLEEP);
            }
        }
        else {
            ofSleepMillis(THREAD_SLEEP);
        }
    }
    return;
}

/*private */ofxICCPhysicalSAT::TableRec const* ofxICCPhysicalSAT::getTableBySensor(SensorType sensor) const
{
    TableRec const* result(NULL);
    
    if (0 <= sensor && sensor < SENSOR_LIMIT) {
        result = &ofxiccphysicalsat_table[sensor];
    }
    return result;
}

/*private */void ofxICCPhysicalSAT::pushCrawl(bool immediate) const
{
    _mutexCrawl.lock();
    _crawl = true;
    _immediate = immediate;
    _mutexCrawl.unlock();
    return;
}

/*private */bool ofxICCPhysicalSAT::popCrawl(void) const
{
    bool result(false);
    
    _mutexCrawl.lock();
    if (_crawl) {
        _crawl = false;
        result = true;
    }
    _immediate = false;
    _mutexCrawl.unlock();
    return result;
}

/*private */bool ofxICCPhysicalSAT::remainsCrawl(void) const
{
    bool result(false);
    
    _mutexCrawl.lock();
    if (_crawl) {
        result = true;
    }
    _mutexCrawl.unlock();
    return result;
}

/*private */bool ofxICCPhysicalSAT::isImmediate(void) const
{
    bool result(false);
    
    _mutexCrawl.lock();
    if (_immediate) {
        result = true;
    }
    _mutexCrawl.unlock();
    return result;
}
//! @endcond
