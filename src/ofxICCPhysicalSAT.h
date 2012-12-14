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
**      ofxICCPhysicalSAT.h
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

#ifndef __OFX_ICCPHYSICALSAT_H
#define __OFX_ICCPHYSICALSAT_H

//! @cond
#include "ofxSATType.h"
#include "ofxSAT.h"
#include "ofThread.h"

class ofxICCPhysicalSAT : public ofxSAT, private ofThread {
    public:
        typedef ofxICCPhysicalSAT       self;
        typedef ofxSAT                  super;
    
    public:
        enum SensorEnum {
            // TODO: BEGIN
            SENSOR_EXAMPLE_X            = super::SENSOR_LIMIT,
            SENSOR_EXAMPLE_Y,
            // TODO: END
            SENSOR_LIMIT
        };
    
    public:
        //! @cond
        struct TableRec {
            FormatEnum                  format;
            UnitEnum                    unit;
            union {
                struct {
                    char                no[32];
                    char                yes[32];
                } boolHint;
                struct {
                    int                 lower;
                    int                 upper;
                } intHint;
                struct {
                    double              lower;
                    double              upper;
                } doubleHint;
                struct {
                    char                format[32];
                } ofxSATTimeHint;
            };
        };
        //! @endcond
    
    private:
        mutable ofMutex                 _mutexValue;
        mutable ofMutex                 _mutexCrawl;
        mutable bool                    _crawl;
        mutable bool                    _immediate;
                bool                    _valid;
                ofxSATTime              _time;
                // TODO: BEGIN
                double                  _valueExampleX;
                double                  _valueExampleY;
                // TODO: END
                ofxSATTimeDiff          _update;
                ofxSATTimeDiff          _retry;
    
    public:
        explicit                        ofxICCPhysicalSAT               (void);
        virtual                         ~ofxICCPhysicalSAT              (void);
                ofxSATError             setUpdateInterval               (ofxSATTimeDiff const& param);
                ofxSATTimeDiff const&   getUpdateInterval               (void) const;
                ofxSATError             setRetryInterval                (ofxSATTimeDiff const& param);
                ofxSATTimeDiff const&   getRetryInterval                (void) const;
        virtual ofxSATError             getAvailableCount               (int* result) const;
        virtual ofxSATError             getAvailableCount               (ofxSATTime const& begin, ofxSATTime const& end, int* result) const;
        virtual ofxSATError             getAvailableTime                (std::vector<ofxSATTime>* result) const;
        virtual ofxSATError             getAvailableTime                (ofxSATTime const& begin, ofxSATTime const& end, std::vector<ofxSATTime>* result) const;
        virtual ofxSATError             getSensorFormat                 (SensorType sensor, FormatEnum* result) const;
        virtual ofxSATError             getSensorUnit                   (SensorType sensor, UnitEnum* result) const;
        virtual ofxSATError             getSensorMinimum                (SensorType sensor, void* result, int size) const;
        virtual ofxSATError             getSensorMaximum                (SensorType sensor, void* result, int size) const;
        virtual ofxSATError             getSensorData                   (SensorType sensor, ofxSATTime const& time, void* result, int size, bool* simulation = NULL) const;
                // TODO: BEGIN
                ofxSATError             getSensorExampleX               (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError             getSensorExampleY               (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                // TODO: END
        virtual ofxSATError             setup                           (void);
        virtual void                    cleanup                         (void);
        virtual ofxSATError             update                          (ofxSATTime const& time = ofxSATTime::currentTime());
    private:
        virtual void                    threadedFunction                (void);
                TableRec const*         getTableBySensor                (SensorType sensor) const;
                void                    pushCrawl                       (bool immediate) const;
                bool                    popCrawl                        (void) const;
                bool                    remainsCrawl                    (void) const;
                bool                    isImmediate                     (void) const;
    private:
                                        ofxICCPhysicalSAT               (ofxICCPhysicalSAT const&);
                ofxICCPhysicalSAT&      operator=                       (ofxICCPhysicalSAT const&);
};

/*public */inline ofxSATTimeDiff const& ofxICCPhysicalSAT::getUpdateInterval(void) const
{
    return _update;
}

/*public */inline ofxSATTimeDiff const& ofxICCPhysicalSAT::getRetryInterval(void) const
{
    return _retry;
}

// TODO: BEGIN
/*public */inline ofxSATError ofxICCPhysicalSAT::getSensorExampleX(ofxSATTime const& time, double* result, bool* simulation) const
{
    return getSensorData(SENSOR_EXAMPLE_X, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxICCPhysicalSAT::getSensorExampleY(ofxSATTime const& time, double* result, bool* simulation) const
{
    return getSensorData(SENSOR_EXAMPLE_Y, time, result, sizeof(*result), simulation);
}
// TODO: END
//! @endcond

#endif
