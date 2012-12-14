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
**      ofxEasyCubeSAT.cpp
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

#include "ofxEasyCubeSAT.h"
#include "ofxInvaderSAT.h"
#ifdef __USE_NAKASUKALAB
#include "ofxXiIVSAT.h"
#include "ofxXiVSAT.h"
#endif

#define ALGORITHMIC             (-1)
#define NOSUPPORT               (-2)

static  ofxEasyCubeSAT::TableRec const
                                ofxeasycubesat_table[] = {
    {// SENSOR_POWER_SOLARPX
        .format                 = ofxEasyCubeSAT::FORMAT_DOUBLE,
        .unit                   = ofxEasyCubeSAT::UNIT_W
    },
    {// SENSOR_POWER_SOLARMX
        .format                 = ofxEasyCubeSAT::FORMAT_DOUBLE,
        .unit                   = ofxEasyCubeSAT::UNIT_W
    },
    {// SENSOR_POWER_SOLARPY
        .format                 = ofxEasyCubeSAT::FORMAT_DOUBLE,
        .unit                   = ofxEasyCubeSAT::UNIT_W
    },
    {// SENSOR_POWER_SOLARMY
        .format                 = ofxEasyCubeSAT::FORMAT_DOUBLE,
        .unit                   = ofxEasyCubeSAT::UNIT_W
    },
    {// SENSOR_POWER_SOLARPZ
        .format                 = ofxEasyCubeSAT::FORMAT_DOUBLE,
        .unit                   = ofxEasyCubeSAT::UNIT_W
    },
    {// SENSOR_POWER_SOLARMZ
        .format                 = ofxEasyCubeSAT::FORMAT_DOUBLE,
        .unit                   = ofxEasyCubeSAT::UNIT_W
    },
    {// SENSOR_POWER_BATTERY
        .format                 = ofxEasyCubeSAT::FORMAT_DOUBLE,
        .unit                   = ofxEasyCubeSAT::UNIT_W
    },
    {// SENSOR_TEMPERATURE_SOLARPX
        .format                 = ofxEasyCubeSAT::FORMAT_DOUBLE,
        .unit                   = ofxEasyCubeSAT::UNIT_degC
    },
    {// SENSOR_TEMPERATURE_SOLARMX
        .format                 = ofxEasyCubeSAT::FORMAT_DOUBLE,
        .unit                   = ofxEasyCubeSAT::UNIT_degC
    },
    {// SENSOR_TEMPERATURE_SOLARPY
        .format                 = ofxEasyCubeSAT::FORMAT_DOUBLE,
        .unit                   = ofxEasyCubeSAT::UNIT_degC
    },
    {// SENSOR_TEMPERATURE_SOLARMY
        .format                 = ofxEasyCubeSAT::FORMAT_DOUBLE,
        .unit                   = ofxEasyCubeSAT::UNIT_degC
    },
    {// SENSOR_TEMPERATURE_SOLARPZ
        .format                 = ofxEasyCubeSAT::FORMAT_DOUBLE,
        .unit                   = ofxEasyCubeSAT::UNIT_degC
    },
    {// SENSOR_TEMPERATURE_SOLARMZ
        .format                 = ofxEasyCubeSAT::FORMAT_DOUBLE,
        .unit                   = ofxEasyCubeSAT::UNIT_degC
    },
    {// SENSOR_TEMPERATURE_BATTERY
        .format                 = ofxEasyCubeSAT::FORMAT_DOUBLE,
        .unit                   = ofxEasyCubeSAT::UNIT_degC
    },
    {// SENSOR_GYRO_X
        .format                 = ofxEasyCubeSAT::FORMAT_DOUBLE,
        .unit                   = ofxEasyCubeSAT::UNIT_rad_s
    },
    {// SENSOR_GYRO_Y
        .format                 = ofxEasyCubeSAT::FORMAT_DOUBLE,
        .unit                   = ofxEasyCubeSAT::UNIT_rad_s
    },
    {// SENSOR_GYRO_Z
        .format                 = ofxEasyCubeSAT::FORMAT_DOUBLE,
        .unit                   = ofxEasyCubeSAT::UNIT_rad_s
    },
    {// SENSOR_MAGNETOMETER_X
        .format                 = ofxEasyCubeSAT::FORMAT_DOUBLE,
        .unit                   = ofxEasyCubeSAT::UNIT_T
    },
    {// SENSOR_MAGNETOMETER_Y
        .format                 = ofxEasyCubeSAT::FORMAT_DOUBLE,
        .unit                   = ofxEasyCubeSAT::UNIT_T
    },
    {// SENSOR_MAGNETOMETER_Z
        .format                 = ofxEasyCubeSAT::FORMAT_DOUBLE,
        .unit                   = ofxEasyCubeSAT::UNIT_T
    }
};
static  ofxEasyCubeSAT::SensorType const
                                ofxeasycubesat_translate[ofxEasyCubeSAT::MODEL_LIMIT][ofxEasyCubeSAT::SENSOR_LIMIT] = {
    {
        ofxInvaderSAT::SENSOR_POWER_SOLARPX,       ofxInvaderSAT::SENSOR_POWER_SOLARMX,
        ofxInvaderSAT::SENSOR_POWER_SOLARPY,       ofxInvaderSAT::SENSOR_POWER_SOLARMY,
        ofxInvaderSAT::SENSOR_POWER_SOLARPZ,       ofxInvaderSAT::SENSOR_POWER_SOLARMZ,
        ofxInvaderSAT::SENSOR_POWER_BATTERY,
        ofxInvaderSAT::SENSOR_TEMPERATURE_SOLARPX, ofxInvaderSAT::SENSOR_TEMPERATURE_SOLARMX,
        ofxInvaderSAT::SENSOR_TEMPERATURE_SOLARPY, ofxInvaderSAT::SENSOR_TEMPERATURE_SOLARMY,
        ofxInvaderSAT::SENSOR_TEMPERATURE_SOLARPZ, ofxInvaderSAT::SENSOR_TEMPERATURE_SOLARMZ,
        ofxInvaderSAT::SENSOR_TEMPERATURE_BATTERY,
        ofxInvaderSAT::SENSOR_GYRO_X,
        ofxInvaderSAT::SENSOR_GYRO_Y,
        ofxInvaderSAT::SENSOR_GYRO_Z,
        ofxInvaderSAT::SENSOR_MAGNETOMETER_X,
        ofxInvaderSAT::SENSOR_MAGNETOMETER_Y,
        ofxInvaderSAT::SENSOR_MAGNETOMETER_Z
    },
    #ifdef __USE_NAKASUKALAB
    {
        ALGORITHMIC,                               ALGORITHMIC,
        ALGORITHMIC,                               ALGORITHMIC,
        ALGORITHMIC,                               ALGORITHMIC,
        NOSUPPORT,
        ofxXiIVSAT::SENSOR_TEMPERATURE_PX,         ofxXiIVSAT::SENSOR_TEMPERATURE_MX,
        ofxXiIVSAT::SENSOR_TEMPERATURE_PY,         ofxXiIVSAT::SENSOR_TEMPERATURE_MY,
        ofxXiIVSAT::SENSOR_TEMPERATURE_PZ,         ofxXiIVSAT::SENSOR_TEMPERATURE_MZ,
        ofxXiIVSAT::SENSOR_TEMPERATURE_BATTERY,
        NOSUPPORT,
        NOSUPPORT,
        NOSUPPORT,
        NOSUPPORT,
        NOSUPPORT,
        NOSUPPORT
    },
    {
        ALGORITHMIC,                               ALGORITHMIC,
        ALGORITHMIC,                               ALGORITHMIC,
        ALGORITHMIC,                               ALGORITHMIC,
        NOSUPPORT,
        ofxXiVSAT::SENSOR_TEMPERATURE_PX,          ofxXiVSAT::SENSOR_TEMPERATURE_MX,
        ofxXiVSAT::SENSOR_TEMPERATURE_PY,          ofxXiVSAT::SENSOR_TEMPERATURE_MY,
        ofxXiVSAT::SENSOR_TEMPERATURE_PZ,          ofxXiVSAT::SENSOR_TEMPERATURE_MZ,
        ofxXiVSAT::SENSOR_TEMPERATURE_BATTERY,
        NOSUPPORT,
        NOSUPPORT,
        NOSUPPORT,
        NOSUPPORT,
        NOSUPPORT,
        NOSUPPORT
    }
    #endif
};

/*public */ofxEasyCubeSAT::ofxEasyCubeSAT(void) : _sat(NULL)
{
    _model = MODEL_LIMIT;
}

/*public virtual */ofxEasyCubeSAT::~ofxEasyCubeSAT(void)
{
    cleanup();
}

/*public */ofxSATError ofxEasyCubeSAT::setModel(ModelEnum param)
{
    ofxSATError error(SATERROR_OK);
    
    if (!isValid()) {
        _model = param;
    }
    else {
        error = SATERROR_INVALID_STATE;
    }
    return error;
}

/*public virtual */ofxSATError ofxEasyCubeSAT::getAvailableCount(int* result) const
{
    ofxSATError error(SATERROR_OK);
    
    if ((error = super::getAvailableCount(result)) == SATERROR_NO_SUPPORT) {
        error = _sat->getAvailableCount(result);
    }
    return error;
}

/*public virtual */ofxSATError ofxEasyCubeSAT::getAvailableCount(ofxSATTime const& begin, ofxSATTime const& end, int* result) const
{
    ofxSATError error(SATERROR_OK);
    
    if ((error = super::getAvailableCount(begin, end, result)) == SATERROR_NO_SUPPORT) {
        error = _sat->getAvailableCount(begin, end, result);
    }
    return error;
}

/*public virtual */ofxSATError ofxEasyCubeSAT::getAvailableTime(std::vector<ofxSATTime>* result) const
{
    ofxSATError error(SATERROR_OK);
    
    if ((error = super::getAvailableTime(result)) == SATERROR_NO_SUPPORT) {
        error = _sat->getAvailableTime(result);
    }
    return error;
}

/*public virtual */ofxSATError ofxEasyCubeSAT::getAvailableTime(ofxSATTime const& begin, ofxSATTime const& end, std::vector<ofxSATTime>* result) const
{
    ofxSATError error(SATERROR_OK);
    
    if ((error = super::getAvailableTime(begin, end, result)) == SATERROR_NO_SUPPORT) {
        error = _sat->getAvailableTime(begin, end, result);
    }
    return error;
}

/*public virtual */ofxSATError ofxEasyCubeSAT::getSensorFormat(SensorType sensor, FormatEnum* result) const
{
    ofxSATError error(SATERROR_OK);
    
    if ((error = super::getSensorFormat(sensor, result)) == SATERROR_NO_SUPPORT) {
        error = SATERROR_OK;
        if (0 <= sensor && sensor < SENSOR_LIMIT) {
            *result = ofxeasycubesat_table[sensor].format;
        }
        else {
            error = SATERROR_INVALID_PARAM;
        }
    }
    return error;
}

/*public virtual */ofxSATError ofxEasyCubeSAT::getSensorUnit(SensorType sensor, UnitEnum* result) const
{
    ofxSATError error(SATERROR_OK);
    
    if ((error = super::getSensorUnit(sensor, result)) == SATERROR_NO_SUPPORT) {
        error = SATERROR_OK;
        if (0 <= sensor && sensor < SENSOR_LIMIT) {
            *result = ofxeasycubesat_table[sensor].unit;
        }
        else {
            error = SATERROR_INVALID_PARAM;
        }
    }
    return error;
}

/*public virtual */ofxSATError ofxEasyCubeSAT::getSensorMinimum(SensorType sensor, void* result, int size) const
{
    SensorType type;
    #ifdef __USE_NAKASUKALAB
    double a;
    double b;
    #endif
    ofxSATError error(SATERROR_OK);
    
    if ((error = super::getSensorMinimum(sensor, result, size)) == SATERROR_NO_SUPPORT) {
        error = SATERROR_OK;
        if (0 <= sensor && sensor < SENSOR_LIMIT) {
            type = ofxeasycubesat_translate[_model][sensor];
            switch (type) {
                case ALGORITHMIC:
                    switch (_model) {
                        case MODEL_INVADER:
                            error = SATERROR_NO_SUPPORT;
                            break;
                        #ifdef __USE_NAKASUKALAB
                        case MODEL_XIIV:
                            switch (sensor) {
                                case SENSOR_POWER_SOLARPX:
                                case SENSOR_POWER_SOLARMX:
                                case SENSOR_POWER_SOLARPY:
                                case SENSOR_POWER_SOLARMY:
                                case SENSOR_POWER_SOLARPZ:
                                case SENSOR_POWER_SOLARMZ:
                                    if ((error = _sat->getSensorMinimum(ofxXiIVSAT::SENSOR_VOLTAGE_SOLAR, &a, sizeof(a))) == SATERROR_OK) {
                                        switch (sensor) {
                                            case SENSOR_POWER_SOLARPX:
                                                type = ofxXiIVSAT::SENSOR_CURRENT_SOLARPX;
                                                break;
                                            case SENSOR_POWER_SOLARMX:
                                                type = ofxXiIVSAT::SENSOR_CURRENT_SOLARMX;
                                                break;
                                            case SENSOR_POWER_SOLARPY:
                                                type = ofxXiIVSAT::SENSOR_CURRENT_SOLARPY;
                                                break;
                                            case SENSOR_POWER_SOLARMY:
                                                type = ofxXiIVSAT::SENSOR_CURRENT_SOLARMY;
                                                break;
                                            case SENSOR_POWER_SOLARPZ:
                                                type = ofxXiIVSAT::SENSOR_CURRENT_SOLARPZ;
                                                break;
                                            case SENSOR_POWER_SOLARMZ:
                                                type = ofxXiIVSAT::SENSOR_CURRENT_SOLARMZ;
                                                break;
                                            default:
                                                error = SATERROR_NO_SUPPORT;
                                                break;
                                        }
                                        if (error == SATERROR_OK) {
                                            if ((error = _sat->getSensorMinimum(type, &b, sizeof(b))) == SATERROR_OK) {
                                                if ((error = checkSize(FORMAT_DOUBLE, size)) == SATERROR_OK) {
                                                    *static_cast<double*>(result) = a * b / 1000.0; // V * mA / 1000.0 = W
                                                }
                                            }
                                        }
                                    }
                                    break;
                                default:
                                    error = SATERROR_NO_SUPPORT;
                                    break;
                            }
                            break;
                        case MODEL_XIV:
                            switch (sensor) {
                                case SENSOR_POWER_SOLARPX:
                                case SENSOR_POWER_SOLARMX:
                                case SENSOR_POWER_SOLARPY:
                                case SENSOR_POWER_SOLARMY:
                                case SENSOR_POWER_SOLARPZ:
                                case SENSOR_POWER_SOLARMZ:
                                    if ((error = _sat->getSensorMinimum(ofxXiVSAT::SENSOR_VOLTAGE_SOLAR, &a, sizeof(a))) == SATERROR_OK) {
                                        switch (sensor) {
                                            case SENSOR_POWER_SOLARPX:
                                                type = ofxXiVSAT::SENSOR_CURRENT_SOLARPX;
                                                break;
                                            case SENSOR_POWER_SOLARMX:
                                                type = ofxXiVSAT::SENSOR_CURRENT_SOLARMX;
                                                break;
                                            case SENSOR_POWER_SOLARPY:
                                                type = ofxXiVSAT::SENSOR_CURRENT_SOLARPY;
                                                break;
                                            case SENSOR_POWER_SOLARMY:
                                                type = ofxXiVSAT::SENSOR_CURRENT_SOLARMY;
                                                break;
                                            case SENSOR_POWER_SOLARPZ:
                                                type = ofxXiVSAT::SENSOR_CURRENT_SOLARPZ;
                                                break;
                                            case SENSOR_POWER_SOLARMZ:
                                                type = ofxXiVSAT::SENSOR_CURRENT_SOLARMZ;
                                                break;
                                            default:
                                                error = SATERROR_NO_SUPPORT;
                                                break;
                                        }
                                        if (error == SATERROR_OK) {
                                            if ((error = _sat->getSensorMinimum(type, &b, sizeof(b))) == SATERROR_OK) {
                                                if ((error = checkSize(FORMAT_DOUBLE, size)) == SATERROR_OK) {
                                                    *static_cast<double*>(result) = a * b / 1000.0; // V * mA / 1000.0 = W
                                                }
                                            }
                                        }
                                    }
                                    break;
                                default:
                                    error = SATERROR_NO_SUPPORT;
                                    break;
                            }
                            break;
                        #endif
                        default:
                            error = SATERROR_INVALID_STATE;
                            break;
                    }
                    break;
                case NOSUPPORT:
                    error = SATERROR_NO_SUPPORT;
                    break;
                default:
                    error = _sat->getSensorMinimum(type, result, size);
                    break;
            }
        }
        else {
            error = SATERROR_INVALID_PARAM;
        }
    }
    return error;
}

/*public virtual */ofxSATError ofxEasyCubeSAT::getSensorMaximum(SensorType sensor, void* result, int size) const
{
    SensorType type;
    #ifdef __USE_NAKASUKALAB
    double a;
    double b;
    #endif
    ofxSATError error(SATERROR_OK);
    
    if ((error = super::getSensorMaximum(sensor, result, size)) == SATERROR_NO_SUPPORT) {
        error = SATERROR_OK;
        if (0 <= sensor && sensor < SENSOR_LIMIT) {
            type = ofxeasycubesat_translate[_model][sensor];
            switch (type) {
                case ALGORITHMIC:
                    switch (_model) {
                        case MODEL_INVADER:
                            error = SATERROR_NO_SUPPORT;
                            break;
                        #ifdef __USE_NAKASUKALAB
                        case MODEL_XIIV:
                            switch (sensor) {
                                case SENSOR_POWER_SOLARPX:
                                case SENSOR_POWER_SOLARMX:
                                case SENSOR_POWER_SOLARPY:
                                case SENSOR_POWER_SOLARMY:
                                case SENSOR_POWER_SOLARPZ:
                                case SENSOR_POWER_SOLARMZ:
                                    if ((error = _sat->getSensorMaximum(ofxXiIVSAT::SENSOR_VOLTAGE_SOLAR, &a, sizeof(a))) == SATERROR_OK) {
                                        switch (sensor) {
                                            case SENSOR_POWER_SOLARPX:
                                                type = ofxXiIVSAT::SENSOR_CURRENT_SOLARPX;
                                                break;
                                            case SENSOR_POWER_SOLARMX:
                                                type = ofxXiIVSAT::SENSOR_CURRENT_SOLARMX;
                                                break;
                                            case SENSOR_POWER_SOLARPY:
                                                type = ofxXiIVSAT::SENSOR_CURRENT_SOLARPY;
                                                break;
                                            case SENSOR_POWER_SOLARMY:
                                                type = ofxXiIVSAT::SENSOR_CURRENT_SOLARMY;
                                                break;
                                            case SENSOR_POWER_SOLARPZ:
                                                type = ofxXiIVSAT::SENSOR_CURRENT_SOLARPZ;
                                                break;
                                            case SENSOR_POWER_SOLARMZ:
                                                type = ofxXiIVSAT::SENSOR_CURRENT_SOLARMZ;
                                                break;
                                            default:
                                                error = SATERROR_NO_SUPPORT;
                                                break;
                                        }
                                        if (error == SATERROR_OK) {
                                            if ((error = _sat->getSensorMaximum(type, &b, sizeof(b))) == SATERROR_OK) {
                                                if ((error = checkSize(FORMAT_DOUBLE, size)) == SATERROR_OK) {
                                                    *static_cast<double*>(result) = a * b / 1000.0; // V * mA / 1000.0 = W
                                                }
                                            }
                                        }
                                    }
                                    break;
                                default:
                                    error = SATERROR_NO_SUPPORT;
                                    break;
                            }
                            break;
                        case MODEL_XIV:
                            switch (sensor) {
                                case SENSOR_POWER_SOLARPX:
                                case SENSOR_POWER_SOLARMX:
                                case SENSOR_POWER_SOLARPY:
                                case SENSOR_POWER_SOLARMY:
                                case SENSOR_POWER_SOLARPZ:
                                case SENSOR_POWER_SOLARMZ:
                                    if ((error = _sat->getSensorMaximum(ofxXiVSAT::SENSOR_VOLTAGE_SOLAR, &a, sizeof(a))) == SATERROR_OK) {
                                        switch (sensor) {
                                            case SENSOR_POWER_SOLARPX:
                                                type = ofxXiVSAT::SENSOR_CURRENT_SOLARPX;
                                                break;
                                            case SENSOR_POWER_SOLARMX:
                                                type = ofxXiVSAT::SENSOR_CURRENT_SOLARMX;
                                                break;
                                            case SENSOR_POWER_SOLARPY:
                                                type = ofxXiVSAT::SENSOR_CURRENT_SOLARPY;
                                                break;
                                            case SENSOR_POWER_SOLARMY:
                                                type = ofxXiVSAT::SENSOR_CURRENT_SOLARMY;
                                                break;
                                            case SENSOR_POWER_SOLARPZ:
                                                type = ofxXiVSAT::SENSOR_CURRENT_SOLARPZ;
                                                break;
                                            case SENSOR_POWER_SOLARMZ:
                                                type = ofxXiVSAT::SENSOR_CURRENT_SOLARMZ;
                                                break;
                                            default:
                                                error = SATERROR_NO_SUPPORT;
                                                break;
                                        }
                                        if (error == SATERROR_OK) {
                                            if ((error = _sat->getSensorMaximum(type, &b, sizeof(b))) == SATERROR_OK) {
                                                if ((error = checkSize(FORMAT_DOUBLE, size)) == SATERROR_OK) {
                                                    *static_cast<double*>(result) = a * b / 1000.0; // V * mA / 1000.0 = W
                                                }
                                            }
                                        }
                                    }
                                    break;
                                default:
                                    error = SATERROR_NO_SUPPORT;
                                    break;
                            }
                            break;
                        #endif
                        default:
                            error = SATERROR_INVALID_STATE;
                            break;
                    }
                    break;
                case NOSUPPORT:
                    error = SATERROR_NO_SUPPORT;
                    break;
                default:
                    error = _sat->getSensorMaximum(type, result, size);
                    break;
            }
        }
        else {
            error = SATERROR_INVALID_PARAM;
        }
    }
    return error;
}

/*public virtual */ofxSATError ofxEasyCubeSAT::getSensorData(SensorType sensor, ofxSATTime const& time, void* result, int size, bool* simulation) const
{
    SensorType type;
    #ifdef __USE_NAKASUKALAB
    double a;
    double b;
    bool x;
    bool y;
    #endif
    ofxSATError error(SATERROR_OK);
    
    if ((error = super::getSensorData(sensor, time, result, size, simulation)) == SATERROR_NO_SUPPORT) {
        error = SATERROR_OK;
        if (0 <= sensor && sensor < SENSOR_LIMIT) {
            type = ofxeasycubesat_translate[_model][sensor];
            switch (type) {
                case ALGORITHMIC:
                    switch (_model) {
                        case MODEL_INVADER:
                            error = SATERROR_NO_SUPPORT;
                            break;
                        #ifdef __USE_NAKASUKALAB
                        case MODEL_XIIV:
                            switch (sensor) {
                                case SENSOR_POWER_SOLARPX:
                                case SENSOR_POWER_SOLARMX:
                                case SENSOR_POWER_SOLARPY:
                                case SENSOR_POWER_SOLARMY:
                                case SENSOR_POWER_SOLARPZ:
                                case SENSOR_POWER_SOLARMZ:
                                    if ((error = _sat->getSensorData(ofxXiIVSAT::SENSOR_VOLTAGE_SOLAR, time, &a, sizeof(a), &x)) == SATERROR_OK) {
                                        switch (sensor) {
                                            case SENSOR_POWER_SOLARPX:
                                                type = ofxXiIVSAT::SENSOR_CURRENT_SOLARPX;
                                                break;
                                            case SENSOR_POWER_SOLARMX:
                                                type = ofxXiIVSAT::SENSOR_CURRENT_SOLARMX;
                                                break;
                                            case SENSOR_POWER_SOLARPY:
                                                type = ofxXiIVSAT::SENSOR_CURRENT_SOLARPY;
                                                break;
                                            case SENSOR_POWER_SOLARMY:
                                                type = ofxXiIVSAT::SENSOR_CURRENT_SOLARMY;
                                                break;
                                            case SENSOR_POWER_SOLARPZ:
                                                type = ofxXiIVSAT::SENSOR_CURRENT_SOLARPZ;
                                                break;
                                            case SENSOR_POWER_SOLARMZ:
                                                type = ofxXiIVSAT::SENSOR_CURRENT_SOLARMZ;
                                                break;
                                            default:
                                                error = SATERROR_NO_SUPPORT;
                                                break;
                                        }
                                        if (error == SATERROR_OK) {
                                            if ((error = _sat->getSensorData(type, time, &b, sizeof(b), &y)) == SATERROR_OK) {
                                                if (result != NULL) {
                                                    if ((error = checkSize(FORMAT_DOUBLE, size)) == SATERROR_OK) {
                                                        *static_cast<double*>(result) = a * b / 1000.0; // V * mA / 1000.0 = W
                                                    }
                                                }
                                                if (error == SATERROR_OK) {
                                                    if (simulation != NULL) {
                                                        *simulation = x || y;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    break;
                                default:
                                    error = SATERROR_NO_SUPPORT;
                                    break;
                            }
                            break;
                        case MODEL_XIV:
                            switch (sensor) {
                                case SENSOR_POWER_SOLARPX:
                                case SENSOR_POWER_SOLARMX:
                                case SENSOR_POWER_SOLARPY:
                                case SENSOR_POWER_SOLARMY:
                                case SENSOR_POWER_SOLARPZ:
                                case SENSOR_POWER_SOLARMZ:
                                    if ((error = _sat->getSensorData(ofxXiVSAT::SENSOR_VOLTAGE_SOLAR, time, &a, sizeof(a), &x)) == SATERROR_OK) {
                                        switch (sensor) {
                                            case SENSOR_POWER_SOLARPX:
                                                type = ofxXiVSAT::SENSOR_CURRENT_SOLARPX;
                                                break;
                                            case SENSOR_POWER_SOLARMX:
                                                type = ofxXiVSAT::SENSOR_CURRENT_SOLARMX;
                                                break;
                                            case SENSOR_POWER_SOLARPY:
                                                type = ofxXiVSAT::SENSOR_CURRENT_SOLARPY;
                                                break;
                                            case SENSOR_POWER_SOLARMY:
                                                type = ofxXiVSAT::SENSOR_CURRENT_SOLARMY;
                                                break;
                                            case SENSOR_POWER_SOLARPZ:
                                                type = ofxXiVSAT::SENSOR_CURRENT_SOLARPZ;
                                                break;
                                            case SENSOR_POWER_SOLARMZ:
                                                type = ofxXiVSAT::SENSOR_CURRENT_SOLARMZ;
                                                break;
                                            default:
                                                error = SATERROR_NO_SUPPORT;
                                                break;
                                        }
                                        if (error == SATERROR_OK) {
                                            if ((error = _sat->getSensorData(type, time, &b, sizeof(b), &y)) == SATERROR_OK) {
                                                if (result != NULL) {
                                                    if ((error = checkSize(FORMAT_DOUBLE, size)) == SATERROR_OK) {
                                                        *static_cast<double*>(result) = a * b / 1000.0; // V * mA / 1000.0 = W
                                                    }
                                                }
                                                if (error == SATERROR_OK) {
                                                    if (simulation != NULL) {
                                                        *simulation = x || y;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    break;
                                default:
                                    error = SATERROR_NO_SUPPORT;
                                    break;
                            }
                            break;
                        #endif
                        default:
                            error = SATERROR_INVALID_STATE;
                            break;
                    }
                    break;
                case NOSUPPORT:
                    error = SATERROR_NO_SUPPORT;
                    break;
                default:
                    error = _sat->getSensorData(type, time, result, size, simulation);
                    break;
            }
        }
        else {
            error = SATERROR_INVALID_PARAM;
        }
    }
    return error;
}

/*public virtual */ofxSATError ofxEasyCubeSAT::setup(void)
{
    ofxSATError error(SATERROR_OK);
    
    if ((error = super::setup()) == SATERROR_OK) {
        switch (_model) {
            case MODEL_INVADER:
                _sat = new ofxInvaderSAT;
                break;
            #ifdef __USE_NAKASUKALAB
            case MODEL_XIIV:
                _sat = new ofxXiIVSAT;
                break;
            case MODEL_XIV:
                _sat = new ofxXiVSAT;
                break;
            #endif
            default:
                error = SATERROR_INVALID_STATE;
                break;
        }
        if (error == SATERROR_OK) {
            if (_sat != NULL) {
                _sat->setNotifier(this);
                if ((error = _sat->setup()) == SATERROR_OK) {
                    setID(_sat->getID());
                }
                else {
                    delete _sat;
                    _sat = NULL;
                }
            }
            else {
                error = SATERROR_NO_MEMORY;
            }
        }
        if (error != SATERROR_OK) {
            super::cleanup();
        }
    }
    return error;
}

/*public virtual */void ofxEasyCubeSAT::cleanup(void)
{
    if (_sat != NULL) {
        _sat->cleanup();
        delete _sat;
    }
    _sat = NULL;
    super::cleanup();
    return;
}

/*public virtual */ofxSATError ofxEasyCubeSAT::update(ofxSATTime const& time)
{
    ofxSATError error(SATERROR_OK);
    
    if ((error = super::update(time)) == SATERROR_OK) {
        error = _sat->update(time);
    }
    return error;
}

/*private virtual */void ofxEasyCubeSAT::onNotifyTLE(TLERec const& tle, ofxSATTime const& time)
{
    setTLE(tle, time);
    return;
}

/*private virtual */void ofxEasyCubeSAT::onNotifyData(ofxSATTime const& time)
{
    notifyData(time);
    return;
}

/*private virtual */void ofxEasyCubeSAT::onNotifyFinish(ofxSATError const& error)
{
    notifyFinish(error);
    return;
}
