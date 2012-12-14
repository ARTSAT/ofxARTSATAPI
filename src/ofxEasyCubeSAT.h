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
**      ofxEasyCubeSAT.h
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

#ifndef __OFX_EASYCUBESAT_H
#define __OFX_EASYCUBESAT_H

/*!
    @file
    CubeSAT を抽象化した仮想の衛星を操作する機能を提供するクラスを含みます。
 */

#include "ofxSATType.h"
#include "ofxSAT.h"

//! CubeSAT を抽象化した仮想の衛星を操作する機能を提供するクラス
/*!
    ofxEasyCubeSAT クラスはさまざまな CubeSAT を抽象化した仮想の衛星からデータを取得する機能を提供します。
 
    ofxEasyCubeSAT クラスの代表的な使い方
    @code
    #include "ofMain.h"
    #include "ofxARTSATAPI.h"
 
    // クラスの定義
    class testApp : public ofBaseApp, private ofxSAT::Notifier {
        private:
            // ofxEasyCubeSAT クラスのインスタンス
            ofxEasyCubeSAT _cubesat;
 
        public:
            void setup(void);
            void exit(void);
            void draw(void);
        private:
            // 通知を受け取るための関数
            virtual void onNotifyTLE(ofxSAT::TLERec const& tle, ofxSATTime const& time);
            virtual void onNotifyData(ofxSATTime const& time);
    };
 
    // クラスの実装
    void testApp::setup(void)
    {
        // 通知を受け取るために通知先を設定
        if (_cubesat.setNotifier(this) == SATERROR_OK) {
            // 衛星のモデルを設定
            if (_cubesat.setModel(ofxEasyCubeSAT::MODEL_INVADER) == SATERROR_OK) {
                // 初期化して開始
                if (_cubesat.setup() == SATERROR_OK) {
                    cout << "Hello ARTSAT." << endl;
                }
            }
        }
        return;
    }
 
    void testApp::exit(void)
    {
        // リソースを解放して終了
        _cubesat.cleanup();
        return;
    }
 
    void testApp::draw(void)
    {
        ofxSATTime begin;
        ofxSATTime end;
        std::vector<ofxSATTime> available;
        double value;
        int i;
 
        // １時間前から現在の時刻までを計算
        end = ofxSATTime::currentTime();
        begin = ofxSATTime(end).subHour(1);
 
        // １時間前から現在の時刻までの間でデータを取得可能な時刻のリストを取得
        if (_cubesat.getAvailableTime(begin, end, &available) == SATERROR_OK) {
            for (i = 0; i < available.size(); ++i) {
                // データが存在する時刻の「+X 面の太陽電池の温度」を取得
                if (_cubesat.getSensorTemperatureSolarPX(available[i], &value) == SATERROR_OK) {
                    cout << "the temperature of solar panel +X is " << value << " degC." << endl;
                }
            }
        }
        return;
    }
 
    // TLE 情報が更新されたときに呼び出される関数
    void testApp::onNotifyTLE(ofxSAT::TLERec const& tle, ofxSATTime const& time)
    {
        // 親クラスの実装を呼び出して情報を出力（オプション）
        ofxSAT::Notifier::onNotifyTLE(tle, time);
 
        cout << "new TLE received." << endl;
        return;
    }
 
    // センサデータが更新されたときに呼び出される関数
    void testApp::onNotifyData(ofxSATTime const& time)
    {
        // 親クラスの実装を呼び出して情報を出力（オプション）
        ofxSAT::Notifier::onNotifyData(time);
 
        cout << "new telemetry data received." << endl;
        return;
    }
    @endcode
 */
class ofxEasyCubeSAT : public ofxSAT, private ofxSAT::Notifier {
    public:
        /*!
            自クラスを表す型の別名です。
         */
        typedef ofxEasyCubeSAT          self;
        /*!
            親クラスを表す型の別名です。
         */
        typedef ofxSAT                  super;
    
    public:
        /*!
            衛星がサポートしているセンサを表す定数です。
            ofxEasyCubeSAT::SENSOR_LIMIT は具体的なセンサを表す値ではなくセンサ定数の最大値を表します。
         */
        enum SensorEnum {
            //! +X 面の太陽電池の発電電力量
            SENSOR_POWER_SOLARPX        = super::SENSOR_LIMIT,
            //! -X 面の太陽電池の発電電力量
            SENSOR_POWER_SOLARMX,
            //! +Y 面の太陽電池の発電電力量
            SENSOR_POWER_SOLARPY,
            //! -Y 面の太陽電池の発電電力量
            SENSOR_POWER_SOLARMY,
            //! +Z 面の太陽電池の発電電力量
            SENSOR_POWER_SOLARPZ,
            //! -Z 面の太陽電池の発電電力量
            SENSOR_POWER_SOLARMZ,
            //! 内蔵蓄電池の放電電力量
            SENSOR_POWER_BATTERY,
            //! +X 面の太陽電池の温度
            SENSOR_TEMPERATURE_PX,
            //! -X 面の太陽電池の温度
            SENSOR_TEMPERATURE_MX,
            //! +Y 面の太陽電池の温度
            SENSOR_TEMPERATURE_PY,
            //! -Y 面の太陽電池の温度
            SENSOR_TEMPERATURE_MY,
            //! +Z 面の太陽電池の温度
            SENSOR_TEMPERATURE_PZ,
            //! -Z 面の太陽電池の温度
            SENSOR_TEMPERATURE_MZ,
            //! 内蔵蓄電池の温度
            SENSOR_TEMPERATURE_BATTERY,
            //! X 軸の角速度
            SENSOR_GYRO_X,
            //! Y 軸の角速度
            SENSOR_GYRO_Y,
            //! Z 軸の角速度
            SENSOR_GYRO_Z,
            //! X 軸の磁力
            SENSOR_MAGNETOMETER_X,
            //! Y 軸の磁力
            SENSOR_MAGNETOMETER_Y,
            //! Z 軸の磁力
            SENSOR_MAGNETOMETER_Z,
            // default
            //! センサ定数の最大値
            SENSOR_LIMIT
        };
        /*!
            ofxEasyCubeSAT クラスがサポートしている衛星のモデルを表す定数です。
            ofxEasyCubeSAT::MODEL_LIMIT は具体的なモデルを表す値ではなくモデル定数の最大値を表します。
         */
        enum ModelEnum {
            //! INVADER 衛星
            MODEL_INVADER,
            #ifdef __USE_NAKASUKALAB
            //! XI-IV 衛星
            MODEL_XIIV,
            //! XI-V 衛星
            MODEL_XIV,
            #endif
            // default
            //! モデル定数の最大値
            MODEL_LIMIT
        };
    
    public:
        //! @cond
        struct TableRec {
            FormatEnum                  format;
            UnitEnum                    unit;
        };
        //! @endcond
    
    private:
                ofxSAT*                 _sat;
                ModelEnum               _model;
    
    public:
        /*!
            コンストラクタです。
            初期化に必要な最低限の処理をおこないます。
         */
        explicit                        ofxEasyCubeSAT                  (void);
        /*!
            デストラクタです。
            管理しているリソースを解放します。
         */
        virtual                         ~ofxEasyCubeSAT                 (void);
        /*!
            衛星のモデルを設定します。
            @param [in] param ofxEasyCubeSAT::ModelEnum 型のモデル定数
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
         */
                ofxSATError             setModel                        (ModelEnum param);
        /*!
            衛星のモデルを取得します。
            @return 現在の値
         */
                ModelEnum               getModel                        (void) const;
        /*!
            センサデータを取得可能な時刻の数を取得します。
            @param [out] result 取得結果
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
            @retval ::SATERROR_NETWORK_DOWN ネットワークが未接続
            @retval ::SATERROR_NETWORK_CODE HTTP ステータスが不正
            @retval ::SATERROR_NO_RESULT データが存在しない
            @retval ::SATERROR_FAILED 内部エラー
         */
        virtual ofxSATError             getAvailableCount               (int* result) const;
        /*!
            引数に指定した時間範囲の中でセンサデータを取得可能な時刻の数を取得します。
            時間範囲は [begin, end) で指定します。
            @param [in] begin 開始時刻（以上）
            @param [in] end 終了時刻（未満）
            @param [out] result 取得結果
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
            @retval ::SATERROR_NETWORK_DOWN ネットワークが未接続
            @retval ::SATERROR_NETWORK_CODE HTTP ステータスが不正
            @retval ::SATERROR_NO_RESULT データが存在しない
            @retval ::SATERROR_FAILED 内部エラー
         */
        virtual ofxSATError             getAvailableCount               (ofxSATTime const& begin, ofxSATTime const& end, int* result) const;
        /*!
            センサデータを取得可能な時刻のリストを取得します。
            @code
            std::vector<ofxSATTime> result;
            ofxSATError error;
         
            error = _cubesat.getAvailableTime(&result);
            if (error == SATERROR_OK) {
                for (i = 0; i < result.size(); ++i) {
                    cout << "result = " << result[i].format("%YYYY/%MM/%DD %hh:%mm:%ss") << endl;
                }
            }
            else {
                cout << "error = " << error.print() << endl;
            }
            @endcode
            @param [out] result 取得結果
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
            @retval ::SATERROR_NETWORK_DOWN ネットワークが未接続
            @retval ::SATERROR_NETWORK_CODE HTTP ステータスが不正
            @retval ::SATERROR_INVALID_FORMAT データのフォーマットが不正
            @retval ::SATERROR_NO_RESULT データが存在しない
            @retval ::SATERROR_FAILED 内部エラー
         */
        virtual ofxSATError             getAvailableTime                (std::vector<ofxSATTime>* result) const;
        /*!
            引数に指定した時間範囲の中でセンサデータを取得可能な時刻のリストを取得します。
            時間範囲は [begin, end) で指定します。
            @code
            ofxSATTime begin;
            ofxSATTime end;
            std::vector<ofxSATTime> result;
            ofxSATError error;
         
            // 現在の時刻から１日前までの範囲を計算
            end = ofxSATTime::currentTime();
            begin = ofxSATTime(end).subDay(1);
         
            error = _cubesat.getAvailableTime(begin, end, &result);
            if (error == SATERROR_OK) {
                for (i = 0; i < result.size(); ++i) {
                    cout << "result = " << result[i].format("%YYYY/%MM/%DD %hh:%mm:%ss") << endl;
                }
            }
            else {
                cout << "error = " << error.print() << endl;
            }
            @endcode
            @param [in] begin 開始時刻（以上）
            @param [in] end 終了時刻（未満）
            @param [out] result 取得結果
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
            @retval ::SATERROR_NETWORK_DOWN ネットワークが未接続
            @retval ::SATERROR_NETWORK_CODE HTTP ステータスが不正
            @retval ::SATERROR_INVALID_FORMAT データのフォーマットが不正
            @retval ::SATERROR_NO_RESULT データが存在しない
            @retval ::SATERROR_FAILED 内部エラー
         */
        virtual ofxSATError             getAvailableTime                (ofxSATTime const& begin, ofxSATTime const& end, std::vector<ofxSATTime>* result) const;
        /*!
            センサの種類に応じた書式を取得します。
            @param [in] sensor ofxEasyCubeSAT::SensorEnum 型のセンサ定数
            @param [out] result 取得結果
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
         */
        virtual ofxSATError             getSensorFormat                 (SensorType sensor, FormatEnum* result) const;
        /*!
            センサの種類に応じた単位を取得します。
            @param [in] sensor ofxEasyCubeSAT::SensorEnum 型のセンサ定数
            @param [out] result 取得結果
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
         */
        virtual ofxSATError             getSensorUnit                   (SensorType sensor, UnitEnum* result) const;
        /*!
            センサの種類に応じた最小値を取得します。
            @param [in] sensor ofxEasyCubeSAT::SensorEnum 型のセンサ定数
            @param [out] result 取得結果
            @param [in] size result に指定した変数のバイト数
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
            @retval ::SATERROR_NO_SUPPORT センサがサポートされていない
            @retval ::SATERROR_NO_RESULT データが存在しない
            @retval ::SATERROR_FAILED 内部エラー
         */
        virtual ofxSATError             getSensorMinimum                (SensorType sensor, void* result, int size) const;
        /*!
            センサの種類に応じた最大値を取得します。
            @param [in] sensor ofxEasyCubeSAT::SensorEnum 型のセンサ定数
            @param [out] result 取得結果
            @param [in] size result に指定した変数のバイト数
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
            @retval ::SATERROR_NO_SUPPORT センサがサポートされていない
            @retval ::SATERROR_NO_RESULT データが存在しない
            @retval ::SATERROR_FAILED 内部エラー
         */
        virtual ofxSATError             getSensorMaximum                (SensorType sensor, void* result, int size) const;
        /*!
            センサの種類に応じた指定された時刻のデータを取得します。
            データ自体を取得する必要がないときは result 引数に NULL を、
            シミュレーションか否かを取得する必要がないときには simulation 引数に NULL を指定することができます。
         
            使い方１：データとシミュレーション結果を取得するとき
            @code
            ofxSATTime time;
            double value;
            bool simulation;
            ofxSATError error;
         
            time = ofxSATTime::currentTime();
            error = _cubesat.getSensorData(ofxEasyCubeSAT::SENSOR_POWER_SOLARPX, time, &value, sizeof(value), &simulation);
            if (error == SATERROR_OK) {
                cout << "value = " << value << endl;
            }
            else {
                cout << "error = " << error.print() << endl;
            }
            @endcode
            使い方２：データのみを取得するとき
            @code
            ofxSATTime time;
            double value;
            ofxSATError error;
         
            time = ofxSATTime::currentTime();
            error = _cubesat.getSensorData(ofxEasyCubeSAT::SENSOR_POWER_SOLARPX, time, &value, sizeof(value), NULL);
            if (error == SATERROR_OK) {
                cout << "value = " << value << endl;
            }
            else {
                cout << "error = " << error.print() << endl;
            }
            @endcode
            @param [in] sensor ofxEasyCubeSAT::SensorEnum 型のセンサ定数
            @param [in] time データを取得する時刻
            @param [out] result 取得結果
                @arg NULL : 結果を返さない
                @arg その他
            @param [in] size result に指定した変数のバイト数
            @param [out] simulation 取得結果はシミュレーション
                @arg NULL : 結果を返さない
                @arg その他
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
            @retval ::SATERROR_NETWORK_DOWN ネットワークが未接続
            @retval ::SATERROR_NETWORK_CODE HTTP ステータスが不正
            @retval ::SATERROR_INVALID_FORMAT データのフォーマットが不正
            @retval ::SATERROR_NO_SUPPORT センサがサポートされていない
            @retval ::SATERROR_NO_RESULT データが存在しない
            @retval ::SATERROR_WAIT_RESULT 結果は後で通知される
            @retval ::SATERROR_FAILED 内部エラー
         */
        virtual ofxSATError             getSensorData                   (SensorType sensor, ofxSATTime const& time, void* result, int size, bool* simulation = NULL) const;
        /*!
            指定された時刻の「+X 面の太陽電池の発電電力量」を取得します。
            データ自体を取得する必要がないときは result 引数に NULL を、
            シミュレーションか否かを取得する必要がないときには simulation 引数に NULL を指定することができます。
            @param [in] time データを取得する時刻
            @param [out] result 取得結果
                @arg NULL : 結果を返さない
                @arg その他
            @param [out] simulation 取得結果はシミュレーション
                @arg NULL : 結果を返さない
                @arg その他
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
            @retval ::SATERROR_NETWORK_DOWN ネットワークが未接続
            @retval ::SATERROR_NETWORK_CODE HTTP ステータスが不正
            @retval ::SATERROR_INVALID_FORMAT データのフォーマットが不正
            @retval ::SATERROR_NO_SUPPORT センサがサポートされていない
            @retval ::SATERROR_NO_RESULT データが存在しない
            @retval ::SATERROR_WAIT_RESULT 結果は後で通知される
            @retval ::SATERROR_FAILED 内部エラー
         */
                ofxSATError             getSensorPowerSolarPX           (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
        /*!
            指定された時刻の「-X 面の太陽電池の発電電力量」を取得します。
            データ自体を取得する必要がないときは result 引数に NULL を、
            シミュレーションか否かを取得する必要がないときには simulation 引数に NULL を指定することができます。
            @param [in] time データを取得する時刻
            @param [out] result 取得結果
                @arg NULL : 結果を返さない
                @arg その他
            @param [out] simulation 取得結果はシミュレーション
                @arg NULL : 結果を返さない
                @arg その他
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
            @retval ::SATERROR_NETWORK_DOWN ネットワークが未接続
            @retval ::SATERROR_NETWORK_CODE HTTP ステータスが不正
            @retval ::SATERROR_INVALID_FORMAT データのフォーマットが不正
            @retval ::SATERROR_NO_SUPPORT センサがサポートされていない
            @retval ::SATERROR_NO_RESULT データが存在しない
            @retval ::SATERROR_WAIT_RESULT 結果は後で通知される
            @retval ::SATERROR_FAILED 内部エラー
         */
                ofxSATError             getSensorPowerSolarMX           (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
        /*!
            指定された時刻の「+Y 面の太陽電池の発電電力量」を取得します。
            データ自体を取得する必要がないときは result 引数に NULL を、
            シミュレーションか否かを取得する必要がないときには simulation 引数に NULL を指定することができます。
            @param [in] time データを取得する時刻
            @param [out] result 取得結果
                @arg NULL : 結果を返さない
                @arg その他
            @param [out] simulation 取得結果はシミュレーション
                @arg NULL : 結果を返さない
                @arg その他
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
            @retval ::SATERROR_NETWORK_DOWN ネットワークが未接続
            @retval ::SATERROR_NETWORK_CODE HTTP ステータスが不正
            @retval ::SATERROR_INVALID_FORMAT データのフォーマットが不正
            @retval ::SATERROR_NO_SUPPORT センサがサポートされていない
            @retval ::SATERROR_NO_RESULT データが存在しない
            @retval ::SATERROR_WAIT_RESULT 結果は後で通知される
            @retval ::SATERROR_FAILED 内部エラー
         */
                ofxSATError             getSensorPowerSolarPY           (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
        /*!
            指定された時刻の「-Y 面の太陽電池の発電電力量」を取得します。
            データ自体を取得する必要がないときは result 引数に NULL を、
            シミュレーションか否かを取得する必要がないときには simulation 引数に NULL を指定することができます。
            @param [in] time データを取得する時刻
            @param [out] result 取得結果
                @arg NULL : 結果を返さない
                @arg その他
            @param [out] simulation 取得結果はシミュレーション
                @arg NULL : 結果を返さない
                @arg その他
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
            @retval ::SATERROR_NETWORK_DOWN ネットワークが未接続
            @retval ::SATERROR_NETWORK_CODE HTTP ステータスが不正
            @retval ::SATERROR_INVALID_FORMAT データのフォーマットが不正
            @retval ::SATERROR_NO_SUPPORT センサがサポートされていない
            @retval ::SATERROR_NO_RESULT データが存在しない
            @retval ::SATERROR_WAIT_RESULT 結果は後で通知される
            @retval ::SATERROR_FAILED 内部エラー
         */
                ofxSATError             getSensorPowerSolarMY           (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
        /*!
            指定された時刻の「+Z 面の太陽電池の発電電力量」を取得します。
            データ自体を取得する必要がないときは result 引数に NULL を、
            シミュレーションか否かを取得する必要がないときには simulation 引数に NULL を指定することができます。
            @param [in] time データを取得する時刻
            @param [out] result 取得結果
                @arg NULL : 結果を返さない
                @arg その他
            @param [out] simulation 取得結果はシミュレーション
                @arg NULL : 結果を返さない
                @arg その他
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
            @retval ::SATERROR_NETWORK_DOWN ネットワークが未接続
            @retval ::SATERROR_NETWORK_CODE HTTP ステータスが不正
            @retval ::SATERROR_INVALID_FORMAT データのフォーマットが不正
            @retval ::SATERROR_NO_SUPPORT センサがサポートされていない
            @retval ::SATERROR_NO_RESULT データが存在しない
            @retval ::SATERROR_WAIT_RESULT 結果は後で通知される
            @retval ::SATERROR_FAILED 内部エラー
         */
                ofxSATError             getSensorPowerSolarPZ           (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
        /*!
            指定された時刻の「-Z 面の太陽電池の発電電力量」を取得します。
            データ自体を取得する必要がないときは result 引数に NULL を、
            シミュレーションか否かを取得する必要がないときには simulation 引数に NULL を指定することができます。
            @param [in] time データを取得する時刻
            @param [out] result 取得結果
                @arg NULL : 結果を返さない
                @arg その他
            @param [out] simulation 取得結果はシミュレーション
                @arg NULL : 結果を返さない
                @arg その他
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
            @retval ::SATERROR_NETWORK_DOWN ネットワークが未接続
            @retval ::SATERROR_NETWORK_CODE HTTP ステータスが不正
            @retval ::SATERROR_INVALID_FORMAT データのフォーマットが不正
            @retval ::SATERROR_NO_SUPPORT センサがサポートされていない
            @retval ::SATERROR_NO_RESULT データが存在しない
            @retval ::SATERROR_WAIT_RESULT 結果は後で通知される
            @retval ::SATERROR_FAILED 内部エラー
         */
                ofxSATError             getSensorPowerSolarMZ           (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
        /*!
            指定された時刻の「内蔵蓄電池の放電電力量」を取得します。
            データ自体を取得する必要がないときは result 引数に NULL を、
            シミュレーションか否かを取得する必要がないときには simulation 引数に NULL を指定することができます。
            @param [in] time データを取得する時刻
            @param [out] result 取得結果
                @arg NULL : 結果を返さない
                @arg その他
            @param [out] simulation 取得結果はシミュレーション
                @arg NULL : 結果を返さない
                @arg その他
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
            @retval ::SATERROR_NETWORK_DOWN ネットワークが未接続
            @retval ::SATERROR_NETWORK_CODE HTTP ステータスが不正
            @retval ::SATERROR_INVALID_FORMAT データのフォーマットが不正
            @retval ::SATERROR_NO_SUPPORT センサがサポートされていない
            @retval ::SATERROR_NO_RESULT データが存在しない
            @retval ::SATERROR_WAIT_RESULT 結果は後で通知される
            @retval ::SATERROR_FAILED 内部エラー
         */
                ofxSATError             getSensorPowerBattery           (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
        /*!
            指定された時刻の「+X 面の太陽電池の温度」を取得します。
            データ自体を取得する必要がないときは result 引数に NULL を、
            シミュレーションか否かを取得する必要がないときには simulation 引数に NULL を指定することができます。
            @param [in] time データを取得する時刻
            @param [out] result 取得結果
                @arg NULL : 結果を返さない
                @arg その他
            @param [out] simulation 取得結果はシミュレーション
                @arg NULL : 結果を返さない
                @arg その他
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
            @retval ::SATERROR_NETWORK_DOWN ネットワークが未接続
            @retval ::SATERROR_NETWORK_CODE HTTP ステータスが不正
            @retval ::SATERROR_INVALID_FORMAT データのフォーマットが不正
            @retval ::SATERROR_NO_SUPPORT センサがサポートされていない
            @retval ::SATERROR_NO_RESULT データが存在しない
            @retval ::SATERROR_WAIT_RESULT 結果は後で通知される
            @retval ::SATERROR_FAILED 内部エラー
         */
                ofxSATError             getSensorTemperaturePX          (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
        /*!
            指定された時刻の「-X 面の太陽電池の温度」を取得します。
            データ自体を取得する必要がないときは result 引数に NULL を、
            シミュレーションか否かを取得する必要がないときには simulation 引数に NULL を指定することができます。
            @param [in] time データを取得する時刻
            @param [out] result 取得結果
                @arg NULL : 結果を返さない
                @arg その他
            @param [out] simulation 取得結果はシミュレーション
                @arg NULL : 結果を返さない
                @arg その他
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
            @retval ::SATERROR_NETWORK_DOWN ネットワークが未接続
            @retval ::SATERROR_NETWORK_CODE HTTP ステータスが不正
            @retval ::SATERROR_INVALID_FORMAT データのフォーマットが不正
            @retval ::SATERROR_NO_SUPPORT センサがサポートされていない
            @retval ::SATERROR_NO_RESULT データが存在しない
            @retval ::SATERROR_WAIT_RESULT 結果は後で通知される
            @retval ::SATERROR_FAILED 内部エラー
         */
                ofxSATError             getSensorTemperatureMX          (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
        /*!
            指定された時刻の「+Y 面の太陽電池の温度」を取得します。
            データ自体を取得する必要がないときは result 引数に NULL を、
            シミュレーションか否かを取得する必要がないときには simulation 引数に NULL を指定することができます。
            @param [in] time データを取得する時刻
            @param [out] result 取得結果
                @arg NULL : 結果を返さない
                @arg その他
            @param [out] simulation 取得結果はシミュレーション
                @arg NULL : 結果を返さない
                @arg その他
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
            @retval ::SATERROR_NETWORK_DOWN ネットワークが未接続
            @retval ::SATERROR_NETWORK_CODE HTTP ステータスが不正
            @retval ::SATERROR_INVALID_FORMAT データのフォーマットが不正
            @retval ::SATERROR_NO_SUPPORT センサがサポートされていない
            @retval ::SATERROR_NO_RESULT データが存在しない
            @retval ::SATERROR_WAIT_RESULT 結果は後で通知される
            @retval ::SATERROR_FAILED 内部エラー
         */
                ofxSATError             getSensorTemperaturePY          (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
        /*!
            指定された時刻の「-Y 面の太陽電池の温度」を取得します。
            データ自体を取得する必要がないときは result 引数に NULL を、
            シミュレーションか否かを取得する必要がないときには simulation 引数に NULL を指定することができます。
            @param [in] time データを取得する時刻
            @param [out] result 取得結果
                @arg NULL : 結果を返さない
                @arg その他
            @param [out] simulation 取得結果はシミュレーション
                @arg NULL : 結果を返さない
                @arg その他
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
            @retval ::SATERROR_NETWORK_DOWN ネットワークが未接続
            @retval ::SATERROR_NETWORK_CODE HTTP ステータスが不正
            @retval ::SATERROR_INVALID_FORMAT データのフォーマットが不正
            @retval ::SATERROR_NO_SUPPORT センサがサポートされていない
            @retval ::SATERROR_NO_RESULT データが存在しない
            @retval ::SATERROR_WAIT_RESULT 結果は後で通知される
            @retval ::SATERROR_FAILED 内部エラー
         */
                ofxSATError             getSensorTemperatureMY          (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
        /*!
            指定された時刻の「+Z 面の太陽電池の温度」を取得します。
            データ自体を取得する必要がないときは result 引数に NULL を、
            シミュレーションか否かを取得する必要がないときには simulation 引数に NULL を指定することができます。
            @param [in] time データを取得する時刻
            @param [out] result 取得結果
                @arg NULL : 結果を返さない
                @arg その他
            @param [out] simulation 取得結果はシミュレーション
                @arg NULL : 結果を返さない
                @arg その他
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
            @retval ::SATERROR_NETWORK_DOWN ネットワークが未接続
            @retval ::SATERROR_NETWORK_CODE HTTP ステータスが不正
            @retval ::SATERROR_INVALID_FORMAT データのフォーマットが不正
            @retval ::SATERROR_NO_SUPPORT センサがサポートされていない
            @retval ::SATERROR_NO_RESULT データが存在しない
            @retval ::SATERROR_WAIT_RESULT 結果は後で通知される
            @retval ::SATERROR_FAILED 内部エラー
         */
                ofxSATError             getSensorTemperaturePZ          (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
        /*!
            指定された時刻の「-Z 面の太陽電池の温度」を取得します。
            データ自体を取得する必要がないときは result 引数に NULL を、
            シミュレーションか否かを取得する必要がないときには simulation 引数に NULL を指定することができます。
            @param [in] time データを取得する時刻
            @param [out] result 取得結果
                @arg NULL : 結果を返さない
                @arg その他
            @param [out] simulation 取得結果はシミュレーション
                @arg NULL : 結果を返さない
                @arg その他
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
            @retval ::SATERROR_NETWORK_DOWN ネットワークが未接続
            @retval ::SATERROR_NETWORK_CODE HTTP ステータスが不正
            @retval ::SATERROR_INVALID_FORMAT データのフォーマットが不正
            @retval ::SATERROR_NO_SUPPORT センサがサポートされていない
            @retval ::SATERROR_NO_RESULT データが存在しない
            @retval ::SATERROR_WAIT_RESULT 結果は後で通知される
            @retval ::SATERROR_FAILED 内部エラー
         */
                ofxSATError             getSensorTemperatureMZ          (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
        /*!
            指定された時刻の「内蔵蓄電池の温度」を取得します。
            データ自体を取得する必要がないときは result 引数に NULL を、
            シミュレーションか否かを取得する必要がないときには simulation 引数に NULL を指定することができます。
            @param [in] time データを取得する時刻
            @param [out] result 取得結果
                @arg NULL : 結果を返さない
                @arg その他
            @param [out] simulation 取得結果はシミュレーション
                @arg NULL : 結果を返さない
                @arg その他
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
            @retval ::SATERROR_NETWORK_DOWN ネットワークが未接続
            @retval ::SATERROR_NETWORK_CODE HTTP ステータスが不正
            @retval ::SATERROR_INVALID_FORMAT データのフォーマットが不正
            @retval ::SATERROR_NO_SUPPORT センサがサポートされていない
            @retval ::SATERROR_NO_RESULT データが存在しない
            @retval ::SATERROR_WAIT_RESULT 結果は後で通知される
            @retval ::SATERROR_FAILED 内部エラー
         */
                ofxSATError             getSensorTemperatureBattery     (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
        /*!
            指定された時刻の「X 軸の角速度」を取得します。
            データ自体を取得する必要がないときは result 引数に NULL を、
            シミュレーションか否かを取得する必要がないときには simulation 引数に NULL を指定することができます。
            @param [in] time データを取得する時刻
            @param [out] result 取得結果
                @arg NULL : 結果を返さない
                @arg その他
            @param [out] simulation 取得結果はシミュレーション
                @arg NULL : 結果を返さない
                @arg その他
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
            @retval ::SATERROR_NETWORK_DOWN ネットワークが未接続
            @retval ::SATERROR_NETWORK_CODE HTTP ステータスが不正
            @retval ::SATERROR_INVALID_FORMAT データのフォーマットが不正
            @retval ::SATERROR_NO_SUPPORT センサがサポートされていない
            @retval ::SATERROR_NO_RESULT データが存在しない
            @retval ::SATERROR_WAIT_RESULT 結果は後で通知される
            @retval ::SATERROR_FAILED 内部エラー
         */
                ofxSATError             getSensorGyroX                  (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
        /*!
            指定された時刻の「Y 軸の角速度」を取得します。
            データ自体を取得する必要がないときは result 引数に NULL を、
            シミュレーションか否かを取得する必要がないときには simulation 引数に NULL を指定することができます。
            @param [in] time データを取得する時刻
            @param [out] result 取得結果
                @arg NULL : 結果を返さない
                @arg その他
            @param [out] simulation 取得結果はシミュレーション
                @arg NULL : 結果を返さない
                @arg その他
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
            @retval ::SATERROR_NETWORK_DOWN ネットワークが未接続
            @retval ::SATERROR_NETWORK_CODE HTTP ステータスが不正
            @retval ::SATERROR_INVALID_FORMAT データのフォーマットが不正
            @retval ::SATERROR_NO_SUPPORT センサがサポートされていない
            @retval ::SATERROR_NO_RESULT データが存在しない
            @retval ::SATERROR_WAIT_RESULT 結果は後で通知される
            @retval ::SATERROR_FAILED 内部エラー
         */
                ofxSATError             getSensorGyroY                  (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
        /*!
            指定された時刻の「Z 軸の角速度」を取得します。
            データ自体を取得する必要がないときは result 引数に NULL を、
            シミュレーションか否かを取得する必要がないときには simulation 引数に NULL を指定することができます。
            @param [in] time データを取得する時刻
            @param [out] result 取得結果
                @arg NULL : 結果を返さない
                @arg その他
            @param [out] simulation 取得結果はシミュレーション
                @arg NULL : 結果を返さない
                @arg その他
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
            @retval ::SATERROR_NETWORK_DOWN ネットワークが未接続
            @retval ::SATERROR_NETWORK_CODE HTTP ステータスが不正
            @retval ::SATERROR_INVALID_FORMAT データのフォーマットが不正
            @retval ::SATERROR_NO_SUPPORT センサがサポートされていない
            @retval ::SATERROR_NO_RESULT データが存在しない
            @retval ::SATERROR_WAIT_RESULT 結果は後で通知される
            @retval ::SATERROR_FAILED 内部エラー
         */
                ofxSATError             getSensorGyroZ                  (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
        /*!
            指定された時刻の「X 軸の磁力」を取得します。
            データ自体を取得する必要がないときは result 引数に NULL を、
            シミュレーションか否かを取得する必要がないときには simulation 引数に NULL を指定することができます。
            @param [in] time データを取得する時刻
            @param [out] result 取得結果
                @arg NULL : 結果を返さない
                @arg その他
            @param [out] simulation 取得結果はシミュレーション
                @arg NULL : 結果を返さない
                @arg その他
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
            @retval ::SATERROR_NETWORK_DOWN ネットワークが未接続
            @retval ::SATERROR_NETWORK_CODE HTTP ステータスが不正
            @retval ::SATERROR_INVALID_FORMAT データのフォーマットが不正
            @retval ::SATERROR_NO_SUPPORT センサがサポートされていない
            @retval ::SATERROR_NO_RESULT データが存在しない
            @retval ::SATERROR_WAIT_RESULT 結果は後で通知される
            @retval ::SATERROR_FAILED 内部エラー
         */
                ofxSATError             getSensorMagnetometerX          (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
        /*!
            指定された時刻の「Y 軸の磁力」を取得します。
            データ自体を取得する必要がないときは result 引数に NULL を、
            シミュレーションか否かを取得する必要がないときには simulation 引数に NULL を指定することができます。
            @param [in] time データを取得する時刻
            @param [out] result 取得結果
                @arg NULL : 結果を返さない
                @arg その他
            @param [out] simulation 取得結果はシミュレーション
                @arg NULL : 結果を返さない
                @arg その他
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
            @retval ::SATERROR_NETWORK_DOWN ネットワークが未接続
            @retval ::SATERROR_NETWORK_CODE HTTP ステータスが不正
            @retval ::SATERROR_INVALID_FORMAT データのフォーマットが不正
            @retval ::SATERROR_NO_SUPPORT センサがサポートされていない
            @retval ::SATERROR_NO_RESULT データが存在しない
            @retval ::SATERROR_WAIT_RESULT 結果は後で通知される
            @retval ::SATERROR_FAILED 内部エラー
         */
                ofxSATError             getSensorMagnetometerY          (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
        /*!
            指定された時刻の「Z 軸の磁力」を取得します。
            データ自体を取得する必要がないときは result 引数に NULL を、
            シミュレーションか否かを取得する必要がないときには simulation 引数に NULL を指定することができます。
            @param [in] time データを取得する時刻
            @param [out] result 取得結果
                @arg NULL : 結果を返さない
                @arg その他
            @param [out] simulation 取得結果はシミュレーション
                @arg NULL : 結果を返さない
                @arg その他
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
            @retval ::SATERROR_NETWORK_DOWN ネットワークが未接続
            @retval ::SATERROR_NETWORK_CODE HTTP ステータスが不正
            @retval ::SATERROR_INVALID_FORMAT データのフォーマットが不正
            @retval ::SATERROR_NO_SUPPORT センサがサポートされていない
            @retval ::SATERROR_NO_RESULT データが存在しない
            @retval ::SATERROR_WAIT_RESULT 結果は後で通知される
            @retval ::SATERROR_FAILED 内部エラー
         */
                ofxSATError             getSensorMagnetometerZ          (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
        /*!
            データの取得やさまざまな機能を利用できるように初期化をおこないます。
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_NO_MEMORY 空きメモリが不足
         */
        virtual ofxSATError             setup                           (void);
        /*!
            データの取得やさまざまな機能を利用するために確保したリソースを解放します。
            @return なし
         */
        virtual void                    cleanup                         (void);
        /*!
            希望する時刻のデータを更新するように要求します。
            @param [in] time 希望する時刻
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
         */
        virtual ofxSATError             update                          (ofxSATTime const& time = ofxSATTime::currentTime());
    private:
        virtual void                    onNotifyTLE                     (TLERec const& tle, ofxSATTime const& time);
        virtual void                    onNotifyData                    (ofxSATTime const& time);
        virtual void                    onNotifyFinish                  (ofxSATError const& error);
    private:
                                        ofxEasyCubeSAT                  (ofxEasyCubeSAT const&);
                ofxEasyCubeSAT&         operator=                       (ofxEasyCubeSAT const&);
};

/*public */inline ofxEasyCubeSAT::ModelEnum ofxEasyCubeSAT::getModel(void) const
{
    return _model;
}

/*public */inline ofxSATError ofxEasyCubeSAT::getSensorPowerSolarPX(ofxSATTime const& time, double* result, bool* simulation) const
{
    return getSensorData(SENSOR_POWER_SOLARPX, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxEasyCubeSAT::getSensorPowerSolarMX(ofxSATTime const& time, double* result, bool* simulation) const
{
    return getSensorData(SENSOR_POWER_SOLARMX, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxEasyCubeSAT::getSensorPowerSolarPY(ofxSATTime const& time, double* result, bool* simulation) const
{
    return getSensorData(SENSOR_POWER_SOLARPY, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxEasyCubeSAT::getSensorPowerSolarMY(ofxSATTime const& time, double* result, bool* simulation) const
{
    return getSensorData(SENSOR_POWER_SOLARMY, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxEasyCubeSAT::getSensorPowerSolarPZ(ofxSATTime const& time, double* result, bool* simulation) const
{
    return getSensorData(SENSOR_POWER_SOLARPZ, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxEasyCubeSAT::getSensorPowerSolarMZ(ofxSATTime const& time, double* result, bool* simulation) const
{
    return getSensorData(SENSOR_POWER_SOLARMZ, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxEasyCubeSAT::getSensorPowerBattery(ofxSATTime const& time, double* result, bool* simulation) const
{
    return getSensorData(SENSOR_POWER_BATTERY, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxEasyCubeSAT::getSensorTemperaturePX(ofxSATTime const& time, double* result, bool* simulation) const
{
    return getSensorData(SENSOR_TEMPERATURE_PX, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxEasyCubeSAT::getSensorTemperatureMX(ofxSATTime const& time, double* result, bool* simulation) const
{
    return getSensorData(SENSOR_TEMPERATURE_MX, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxEasyCubeSAT::getSensorTemperaturePY(ofxSATTime const& time, double* result, bool* simulation) const
{
    return getSensorData(SENSOR_TEMPERATURE_PY, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxEasyCubeSAT::getSensorTemperatureMY(ofxSATTime const& time, double* result, bool* simulation) const
{
    return getSensorData(SENSOR_TEMPERATURE_MY, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxEasyCubeSAT::getSensorTemperaturePZ(ofxSATTime const& time, double* result, bool* simulation) const
{
    return getSensorData(SENSOR_TEMPERATURE_PZ, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxEasyCubeSAT::getSensorTemperatureMZ(ofxSATTime const& time, double* result, bool* simulation) const
{
    return getSensorData(SENSOR_TEMPERATURE_MZ, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxEasyCubeSAT::getSensorTemperatureBattery(ofxSATTime const& time, double* result, bool* simulation) const
{
    return getSensorData(SENSOR_TEMPERATURE_BATTERY, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxEasyCubeSAT::getSensorGyroX(ofxSATTime const& time, double* result, bool* simulation) const
{
    return getSensorData(SENSOR_GYRO_X, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxEasyCubeSAT::getSensorGyroY(ofxSATTime const& time, double* result, bool* simulation) const
{
    return getSensorData(SENSOR_GYRO_Y, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxEasyCubeSAT::getSensorGyroZ(ofxSATTime const& time, double* result, bool* simulation) const
{
    return getSensorData(SENSOR_GYRO_Z, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxEasyCubeSAT::getSensorMagnetometerX(ofxSATTime const& time, double* result, bool* simulation) const
{
    return getSensorData(SENSOR_MAGNETOMETER_X, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxEasyCubeSAT::getSensorMagnetometerY(ofxSATTime const& time, double* result, bool* simulation) const
{
    return getSensorData(SENSOR_MAGNETOMETER_Y, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxEasyCubeSAT::getSensorMagnetometerZ(ofxSATTime const& time, double* result, bool* simulation) const
{
    return getSensorData(SENSOR_MAGNETOMETER_Z, time, result, sizeof(*result), simulation);
}

#endif
