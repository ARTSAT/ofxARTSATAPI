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
**      ofxSAT.cpp
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

#include "ofxSAT.h"
#include "ofLog.h"

/*protected */ofxSAT::ofxSAT(void) : _state(false), _tleValid(false)
{
    ofAddListener(_eventTLE, this, &ofxSAT::handleNotifyTLE);
    ofAddListener(_eventData, this, &ofxSAT::handleNotifyData);
    ofAddListener(_eventFinish, this, &ofxSAT::handleNotifyFinish);
    _notifier = NULL;
}

/*public virtual */ofxSAT::~ofxSAT(void)
{
    cleanup();
    ofRemoveListener(_eventFinish, this, &ofxSAT::handleNotifyFinish);
    ofRemoveListener(_eventData, this, &ofxSAT::handleNotifyData);
    ofRemoveListener(_eventTLE, this, &ofxSAT::handleNotifyTLE);
}

/*public */ofxSATError ofxSAT::getTLE(TLERec* tle, ofxSATTime* time) const
{
    ofxSATError error(SATERROR_OK);
    
    if (_tleValid) {
        if (tle != NULL) {
            *tle = _tleTLE;
            if (time != NULL) {
                *time = _tleTime;
            }
        }
        else {
            error = SATERROR_INVALID_PARAM;
        }
    }
    else {
        error = SATERROR_INVALID_STATE;
    }
    return error;
}

/*public virtual */ofxSATError ofxSAT::getAvailableCount(int* result) const
{
    ofxSATError error(SATERROR_OK);
    
    if (_state) {
        if (result != NULL) {
            error = SATERROR_NO_SUPPORT;
        }
        else {
            error = SATERROR_INVALID_PARAM;
        }
    }
    else {
        error = SATERROR_INVALID_STATE;
    }
    return error;
}

/*public virtual */ofxSATError ofxSAT::getAvailableCount(ofxSATTime const& begin, ofxSATTime const& end, int* result) const
{
    ofxSATError error(SATERROR_OK);
    
    if (_state) {
        if (result != NULL) {
            error = SATERROR_NO_SUPPORT;
        }
        else {
            error = SATERROR_INVALID_PARAM;
        }
    }
    else {
        error = SATERROR_INVALID_STATE;
    }
    return error;
}

/*public virtual */ofxSATError ofxSAT::getAvailableTime(std::vector<ofxSATTime>* result) const
{
    ofxSATError error(SATERROR_OK);
    
    if (_state) {
        if (result != NULL) {
            error = SATERROR_NO_SUPPORT;
        }
        else {
            error = SATERROR_INVALID_PARAM;
        }
    }
    else {
        error = SATERROR_INVALID_STATE;
    }
    return error;
}

/*public virtual */ofxSATError ofxSAT::getAvailableTime(ofxSATTime const& begin, ofxSATTime const& end, std::vector<ofxSATTime>* result) const
{
    ofxSATError error(SATERROR_OK);
    
    if (_state) {
        if (result != NULL) {
            error = SATERROR_NO_SUPPORT;
        }
        else {
            error = SATERROR_INVALID_PARAM;
        }
    }
    else {
        error = SATERROR_INVALID_STATE;
    }
    return error;
}

/*public virtual */ofxSATError ofxSAT::getSensorFormat(SensorType sensor, FormatEnum* result) const
{
    ofxSATError error(SATERROR_OK);
    
    if (_state) {
        if (result != NULL) {
            error = SATERROR_NO_SUPPORT;
        }
        else {
            error = SATERROR_INVALID_PARAM;
        }
    }
    else {
        error = SATERROR_INVALID_STATE;
    }
    return error;
}

/*public virtual */ofxSATError ofxSAT::getSensorUnit(SensorType sensor, UnitEnum* result) const
{
    ofxSATError error(SATERROR_OK);
    
    if (_state) {
        if (result != NULL) {
            error = SATERROR_NO_SUPPORT;
        }
        else {
            error = SATERROR_INVALID_PARAM;
        }
    }
    else {
        error = SATERROR_INVALID_STATE;
    }
    return error;
}

/*public virtual */ofxSATError ofxSAT::getSensorMinimum(SensorType sensor, void* result, int size) const
{
    ofxSATError error(SATERROR_OK);
    
    if (_state) {
        if (result != NULL) {
            error = SATERROR_NO_SUPPORT;
        }
        else {
            error = SATERROR_INVALID_PARAM;
        }
    }
    else {
        error = SATERROR_INVALID_STATE;
    }
    return error;
}

/*public virtual */ofxSATError ofxSAT::getSensorMaximum(SensorType sensor, void* result, int size) const
{
    ofxSATError error(SATERROR_OK);
    
    if (_state) {
        if (result != NULL) {
            error = SATERROR_NO_SUPPORT;
        }
        else {
            error = SATERROR_INVALID_PARAM;
        }
    }
    else {
        error = SATERROR_INVALID_STATE;
    }
    return error;
}

/*public virtual */ofxSATError ofxSAT::getSensorData(SensorType sensor, ofxSATTime const& time, void* result, int size, bool* simulation) const
{
    ofxSATError error(SATERROR_OK);
    
    if (_state) {
        error = SATERROR_NO_SUPPORT;
    }
    else {
        error = SATERROR_INVALID_STATE;
    }
    return error;
}

/*public */ofxSATError ofxSAT::setNotifier(Notifier* param)
{
    ofxSATError error(SATERROR_OK);
    
    if (!_state) {
        _notifier = param;
    }
    else {
        error = SATERROR_INVALID_STATE;
    }
    return error;
}

/*public virtual */ofxSATError ofxSAT::setup(void)
{
    ofxSATError error(SATERROR_OK);
    
    if (!_state) {
        _state = true;
    }
    else {
        error = SATERROR_INVALID_STATE;
    }
    return error;
}

/*public virtual */void ofxSAT::cleanup(void)
{
    if (_state) {
        // nop
    }
    _state = false;
    return;
}

/*public virtual */ofxSATError ofxSAT::update(ofxSATTime const& time)
{
    ofxSATError error(SATERROR_OK);
    
    if (_state) {
        // nop
    }
    else {
        error = SATERROR_INVALID_STATE;
    }
    return error;
}

/*protected */void ofxSAT::setTLE(TLERec const& tle, ofxSATTime const& time)
{
    EventTLERec event;
    
    if (!_tleValid || memcmp(&tle, &_tleTLE, sizeof(_tleTLE)) != 0 || time != _tleTime) {
        _tleTLE = tle;
        _tleTime = time;
        _tleValid = true;
        event.tle = tle;
        event.time = time;
        ofNotifyEvent(_eventTLE, event);
    }
    return;
}

/*protected */void ofxSAT::notifyData(ofxSATTime const& time) const
{
    EventDataRec event;
    
    event.time = time;
    ofNotifyEvent(_eventData, event);
    return;
}

/*protected */void ofxSAT::notifyFinish(ofxSATError const& error) const
{
    EventFinishRec event;
    
    event.error = error;
    ofNotifyEvent(_eventFinish, event);
    return;
}

/*protected static */std::string ofxSAT::trimSpace(std::string const& param)
{
    int index;
    std::string result(param);
    
    if ((index = result.find(' ')) != std::string::npos) {
        result.erase(index);
    }
    return result;
}

/*protected static */std::string ofxSAT::trimNonNumeric(std::string const& param)
{
    int i;
    std::string result(param);
    
    for (i = 0; i < result.size(); ++i) {
        if (result[i] != '+' && result[i] != '-' && !isdigit(result[i]) && result[i] != '.') {
            result.erase(i);
            break;
        }
    }
    return result;
}

/*protected static */std::string ofxSAT::replaceString(std::string const& string, std::string const& from, std::string const& to)
{
    int i;
    std::string result(string);
    
    i = 0;
    while ((i = result.find(from, i)) != std::string::npos) {
        result.replace(i, from.size(), to);
        i += to.size();
    }
    return result;
}

/*protected static */ofxSATError ofxSAT::checkSize(FormatEnum format, int size)
{
    ofxSATError error(SATERROR_OK);
    
    switch (format) {
        case FORMAT_BOOL:
            if (size < sizeof(bool)) {
                error = SATERROR_INVALID_PARAM;
            }
            break;
        case FORMAT_INT:
            if (size < sizeof(int)) {
                error = SATERROR_INVALID_PARAM;
            }
            break;
        case FORMAT_DOUBLE:
            if (size < sizeof(double)) {
                error = SATERROR_INVALID_PARAM;
            }
            break;
        case FORMAT_STRING:
            if (size < sizeof(std::string)) {
                error = SATERROR_INVALID_PARAM;
            }
            break;
        case FORMAT_OFXSATTIME:
            if (size < sizeof(ofxSATTime)) {
                error = SATERROR_INVALID_PARAM;
            }
            break;
        default:
            error = SATERROR_FAILED;
            break;
    }
    return error;
}

/*private */void ofxSAT::handleNotifyTLE(EventTLERec& event)
{
    if (_notifier != NULL) {
        _notifier->onNotifyTLE(event.tle, event.time);
    }
    return;
}

/*private */void ofxSAT::handleNotifyData(EventDataRec& event)
{
    if (_notifier != NULL) {
        _notifier->onNotifyData(event.time);
    }
    return;
}

/*private */void ofxSAT::handleNotifyFinish(EventFinishRec& event)
{
    if (_notifier != NULL) {
        _notifier->onNotifyFinish(event.error);
    }
    return;
}

/*protected virtual */void ofxSAT::Notifier::onNotifyTLE(TLERec const& tle, ofxSATTime const& time)
{
    ofLogNotice() << "ofxSAT::Notifier::onNotifyTLE [TLE :" << endl
                  << "    " << tle.line[0] << endl
                  << "    " << tle.line[1] << endl
                  << "    " << time.format("%YYYY/%MM/%DD %hh:%mm:%ss") << endl
                  << "]";
    return;
}

/*protected virtual */void ofxSAT::Notifier::onNotifyData(ofxSATTime const& time)
{
    ofLogNotice() << "ofxSAT::Notifier::onNotifyData [time : " << time.format("%YYYY/%MM/%DD %hh:%mm:%ss") << "]";
    return;
}

/*protected virtual */void ofxSAT::Notifier::onNotifyFinish(ofxSATError const& error)
{
    ofLogNotice() << "ofxSAT::Notifier::onNotifyFinish [error : " << error.print() << "]";
    return;
}
