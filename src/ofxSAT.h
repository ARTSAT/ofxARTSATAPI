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
**      ofxSAT.h
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

#ifndef __OFX_SAT_H
#define __OFX_SAT_H

/*!
    @file
    すべての衛星に共通する基本的な機能を提供するインターフェースクラスを含みます。
    さまざまな具体的な衛星を表すクラスはこのクラスを継承して作成されます。
 */

#include "ofxSATType.h"
#include "ofEvents.h"
#include "ofxSATTime.h"

//! すべての衛星に共通する基本的な機能を提供するクラス
/*!
    ofxSAT クラスはすべての衛星に共通する機能やインターフェースを定義します。
    さまざまな具体的な衛星を表すクラスは ofxSAT クラスを継承します。
    ofxSAT クラスはインターフェースクラスであるので直接インスタンスを生成することはできません。

    いくつかの関数は呼び出し後に結果を通知として非同期に返すことがあります。
    Notifier クラスを継承したクラスを作成し Notifier クラスが定義する仮想関数を
    オーバーライトし setNotifier() 関数を呼び出すことで通知を受け取ることができます。
 */
class ofxSAT {
    public:
        /*!
            自クラスを表す型の別名です。
         */
        typedef ofxSAT                  self;
    
    public:
        /*!
            衛星がサポートしているセンサを表す定数です。
            ofxSAT::SENSOR_LIMIT は具体的なセンサを表す値ではなくセンサ定数の最大値を表します。
         */
        enum SensorEnum {
            // default
            //! センサ定数の最大値
            SENSOR_LIMIT
        };
        /*!
            センサの値の書式を表す定数です。
            ofxSAT::FORMAT_LIMIT は具体的な書式を表す値ではなく書式定数の最大値を表します。
         */
        enum FormatEnum {
            // primitive
            //! bool 型
            FORMAT_BOOL,
            //! int 型
            FORMAT_INT,
            //! double 型
            FORMAT_DOUBLE,
            // class
            //! std::string 型
            FORMAT_STRING,
            //! ofxSATTime 型
            FORMAT_OFXSATTIME,
            // default
            //! 書式定数の最大値
            FORMAT_LIMIT
        };
        /*!
            センサの値の単位を表す定数です。
            ofxSAT::UNIT_LIMIT は具体的な単位を表す値ではなく単位定数の最大値を表します。
         */
        enum UnitEnum {
            // general
            //! 単位なし
            UNIT_NONE,
            //! 定義されていない
            UNIT_UNDEFINED,
            // voltage
            //! ギガボルト
            UNIT_GV,
            //! メガボルト
            UNIT_MV,
            //! キロボルト
            UNIT_kV,
            //! ボルト
            UNIT_V,
            //! ミリボルト
            UNIT_mV,
            //! マイクロボルト
            UNIT_uV,
            //! ナノボルト
            UNIT_nV,
            // current
            //! ギガアンペア
            UNIT_GA,
            //! メガアンペア
            UNIT_MA,
            //! キロアンペア
            UNIT_kA,
            //! アンペア
            UNIT_A,
            //! ミリアンペア
            UNIT_mA,
            //! マイクロアンペア
            UNIT_uA,
            //! ナノアンペア
            UNIT_nA,
            // power
            //! ギガワット
            UNIT_GW,
            //! メガワット
            UNIT_MW,
            //! キロワット
            UNIT_kW,
            //! ワット
            UNIT_W,
            //! ミリワット
            UNIT_mW,
            //! マイクロワット
            UNIT_uW,
            //! ナノワット
            UNIT_nW,
            //! ギガワット時
            UNIT_GWh,
            //! メガワット時
            UNIT_MWh,
            //! キロワット時
            UNIT_kWh,
            //! ワット時
            UNIT_Wh,
            //! ミリワット時
            UNIT_mWh,
            //! マイクロワット時
            UNIT_uWh,
            //! ナノワット時
            UNIT_nWh,
            //! ギガジュール
            UNIT_GJ,
            //! メガジュール
            UNIT_MJ,
            //! キロジュール
            UNIT_kJ,
            //! ジュール
            UNIT_J,
            //! ミリジュール
            UNIT_mJ,
            //! マイクロジュール
            UNIT_uJ,
            //! ナノジュール
            UNIT_nJ,
            // distance
            //! ギガメートル
            UNIT_Gm,
            //! メガメートル
            UNIT_Mm,
            //! キロメートル
            UNIT_km,
            //! メートル
            UNIT_m,
            //! ミリメートル
            UNIT_mm,
            //! マイクロメートル
            UNIT_um,
            //! ナノメートル
            UNIT_nm,
            //! ラジアン
            UNIT_rad,
            //! 角度
            UNIT_deg,
            // velocity
            //! ギガメートル毎秒
            UNIT_Gm_s,
            //! メガメートル毎秒
            UNIT_Mm_s,
            //! キロメートル毎秒
            UNIT_km_s,
            //! メートル毎秒
            UNIT_m_s,
            //! ミリメートル毎秒
            UNIT_mm_s,
            //! マイクロメートル毎秒
            UNIT_um_s,
            //! ナノメートル毎秒
            UNIT_nm_s,
            //! ラジアン毎秒
            UNIT_rad_s,
            //! 角度毎秒
            UNIT_deg_s,
            // acceleration
            //! ギガメートル毎秒毎秒
            UNIT_Gm_ss,
            //! メガメートル毎秒毎秒
            UNIT_Mm_ss,
            //! キロメートル毎秒毎秒
            UNIT_km_ss,
            //! メートル毎秒毎秒
            UNIT_m_ss,
            //! ミリメートル毎秒毎秒
            UNIT_mm_ss,
            //! マイクロメートル毎秒毎秒
            UNIT_um_ss,
            //! ナノメートル毎秒毎秒
            UNIT_nm_ss,
            //! ラジアン毎秒毎秒
            UNIT_rad_ss,
            //! 角度毎秒毎秒
            UNIT_deg_ss,
            // temperature
            //! ギガケルビン
            UNIT_GK,
            //! メガケルビン
            UNIT_MK,
            //! キロケルビン
            UNIT_kK,
            //! ケルビン
            UNIT_K,
            //! ミリケルビン
            UNIT_mK,
            //! マイクロケルビン
            UNIT_uK,
            //! ナノケルビン
            UNIT_nK,
            //! 摂氏度
            UNIT_degC,
            //! 華氏度
            UNIT_degF,
            // magnetism
            //! ギガテスラ
            UNIT_GT,
            //! メガテスラ
            UNIT_MT,
            //! キロテスラ
            UNIT_kT,
            //! テスラ
            UNIT_T,
            //! ミリテスラ
            UNIT_mT,
            //! マイクロテスラ
            UNIT_uT,
            //! ナノテスラ
            UNIT_nT,
            // default
            //! 単位定数の最大値
            UNIT_LIMIT
        };
    
    public:
        /*!
            センサを表す型です。
            ofxSAT::SensorEnum 型は直接使用されることはなくセンサを表すには ofxSAT::SensorType 型を使用します。
            ofxSAT::SensorType 型の変数には ofxSAT::SensorEnum 型の定数を代入します。
         */
        typedef int                     SensorType;
        //! TLE (２行軌道要素形式) を表す構造体
        /*!
            TLE (２行軌道要素形式) を表す構造体です。
         */
        struct TLERec {
            /*!
                line[0] が TLE の１行目を line[1] が２行目を表します。
             */
            char                        line[2][70];
        };
        //! 通知を受け取るための機能を提供するクラス
        /*!
            ofxSAT クラスのいくつかの関数は結果を即時に返さずに通知として非同期に返すことがあります。
            通知を受け取るにはこのクラスを継承した通知先クラスを作成し、定義されている３つの仮想関数を必要に応じてオーバーライトします。
            次に ofxSAT::setup() を呼び出す前に ofxSAT::setNotifier() 関数を使って通知先クラスを登録します。
            通知は ofEvent を使ってスレッドセーフに呼び出されます。
         */
        class Notifier {
            protected:
                /*!
                    TLE 情報が更新されたときに呼び出されます。
                    通知を受け取るにはこの仮想関数をオーバーライトします。
                    オーバーライトしない場合はデフォルトの動作が実行されます。
                
                    デフォルトの動作は
                    @verbatim
                    OF: OF_LOG_NOTICE: ofxSAT::Notifier::onNotifyTLE [TLE :
                        1 00000S 13000A   13213.00000000  .00000000  00000-0  10000-3 0  0012
                        2 00000  65.0000 132.9020 0054720 087.3320 208.8860 15.53419076000004
                        2012/09/24 15:18:16
                    ]
                    @endverbatim
                    などをログに表示します。
                    @param [in] tle TLE 情報
                    @param [in] time TLE を取得した時刻
                    @return なし
                 */
                virtual void            onNotifyTLE                     (TLERec const& tle, ofxSATTime const& time);
                /*!
                    センサデータが更新されたときに呼び出されます。
                    通知を受け取るにはこの仮想関数をオーバーライトします。
                    オーバーライトしない場合はデフォルトの動作が実行されます。
                
                    デフォルトの動作は
                    @verbatim
                    OF: OF_LOG_NOTICE: ofxSAT::Notifier::onNotifyData [time : 2012/09/12 15:17:57]
                    @endverbatim
                    などをログに表示します。
                
                    １回分のデータの更新で複数回の通知を受け取る可能性があります。
                    @param [in] time 更新されたデータの時刻
                    @return なし
                 */
                virtual void            onNotifyData                    (ofxSATTime const& time);
                /*!
                    １回分のデータの更新がすべて終了したときに呼び出されます。
                    通知を受け取るにはこの仮想関数をオーバーライトします。
                    オーバーライトしない場合はデフォルトの動作が実行されます。
                
                    デフォルトの動作は
                    @verbatim
                    OF: OF_LOG_NOTICE: ofxSAT::Notifier::onNotifyFinish [error : 0 (SATERROR_OK)]
                    @endverbatim
                    などをログに表示します。
                
                    データを取得する過程でエラーが発生した場合は error 引数に渡されます。
                    @param [in] error エラー情報
                        @arg ::SATERROR_OK : 正常終了
                        @arg その他 ::SATErrorEnum 型定数
                    @return なし
                 */
                virtual void            onNotifyFinish                  (ofxSATError const& error);
            friend      class           ofxSAT;
        };
    private:
        struct EventTLERec {
            TLERec                      tle;
            ofxSATTime                  time;
        };
        struct EventDataRec {
            ofxSATTime                  time;
        };
        struct EventFinishRec {
            ofxSATError                 error;
        };
    
    private:
                bool                    _state;
                std::string             _id;
                bool                    _tleValid;
                TLERec                  _tleTLE;
                ofxSATTime              _tleTime;
        mutable ofEvent<EventTLERec>    _eventTLE;
        mutable ofEvent<EventDataRec>   _eventData;
        mutable ofEvent<EventFinishRec> _eventFinish;
                Notifier*               _notifier;
    
    public:
        /*!
            デストラクタです。
            管理しているリソースを解放します。
         */
        virtual                         ~ofxSAT                         (void) = 0;
        /*!
            ID を取得します。
            @return 現在の ID
         */
                std::string const&      getID                           (void) const;
        /*!
            TLE 情報と TLE を取得した時刻を取得します。
            tle パラメータは NULL を指定できませんが、time パラメータは NULL を指定してもかまいません。
            @param [out] tle TLE 情報
            @param [out] time TLE を取得した時刻
                @arg NULL : 結果を返さない
                @arg その他
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE TLE 情報が設定されていない
            @retval ::SATERROR_INVALID_PARAM tle パラメータが不正
         */
                ofxSATError             getTLE                          (TLERec* tle, ofxSATTime* time = NULL) const;
        /*!
            センサデータを取得可能な時刻の数を取得します。
            @note
            この関数は ofxSAT クラスを継承した具象クラスを作成するときに必要に応じてオーバーライトし、
            オーバーライトした関数からは内部状態と引数の妥当性の検証に利用することができます。
            @param [out] result 取得結果
            @return エラー情報
            @retval ::SATERROR_NO_SUPPORT 未サポート（正常終了）
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
         */
        virtual ofxSATError             getAvailableCount               (int* result) const;
        /*!
            引数に指定した時間範囲の中でセンサデータを取得可能な時刻の数を取得します。
            時間範囲は [begin, end) で指定します。
            @note
            この関数は ofxSAT クラスを継承した具象クラスを作成するときに必要に応じてオーバーライトし、
            オーバーライトした関数からは内部状態と引数の妥当性の検証に利用することができます。
            @param [in] begin 開始時刻（以上）
            @param [in] end 終了時刻（未満）
            @param [out] result 取得結果
            @return エラー情報
            @retval ::SATERROR_NO_SUPPORT 未サポート（正常終了）
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
         */
        virtual ofxSATError             getAvailableCount               (ofxSATTime const& begin, ofxSATTime const& end, int* result) const;
        /*!
            センサデータを取得可能な時刻のリストを取得します。
            @code
            std::vector<ofxSATTime> result;
            ofxSATError error;
         
            error = _sat->getAvailableTime(&result);
            if (error == SATERROR_OK) {
                for (i = 0; i < result.size(); ++i) {
                    cout << "result = " << result[i].format("%YYYY/%MM/%DD %hh:%mm:%ss") << endl;
                }
            }
            else {
                cout << "error = " << error.print() << endl;
            }
            @endcode
            @note
            この関数は ofxSAT クラスを継承した具象クラスを作成するときに必要に応じてオーバーライトし、
            オーバーライトした関数からは内部状態と引数の妥当性の検証に利用することができます。
            @param [out] result 取得結果
            @return エラー情報
            @retval ::SATERROR_NO_SUPPORT 未サポート（正常終了）
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
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
         
            error = _sat->getAvailableTime(begin, end, &result);
            if (error == SATERROR_OK) {
                for (i = 0; i < result.size(); ++i) {
                    cout << "result = " << result[i].format("%YYYY/%MM/%DD %hh:%mm:%ss") << endl;
                }
            }
            else {
                cout << "error = " << error.print() << endl;
            }
            @endcode
            @note
            この関数は ofxSAT クラスを継承した具象クラスを作成するときに必要に応じてオーバーライトし、
            オーバーライトした関数からは内部状態と引数の妥当性の検証に利用することができます。
            @param [in] begin 開始時刻（以上）
            @param [in] end 終了時刻（未満）
            @param [out] result 取得結果
            @return エラー情報
            @retval ::SATERROR_NO_SUPPORT 未サポート（正常終了）
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
         */
        virtual ofxSATError             getAvailableTime                (ofxSATTime const& begin, ofxSATTime const& end, std::vector<ofxSATTime>* result) const;
        /*!
            センサの種類に応じた書式を取得します。
            @note
            この関数は ofxSAT クラスを継承した具象クラスを作成するときに必要に応じてオーバーライトし、
            オーバーライトした関数からは内部状態と引数の妥当性の検証に利用することができます。
            @param [in] sensor ofxSAT::SensorEnum 型のセンサ定数
            @param [out] result 取得結果
            @return エラー情報
            @retval ::SATERROR_NO_SUPPORT 未サポート（正常終了）
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
         */
        virtual ofxSATError             getSensorFormat                 (SensorType sensor, FormatEnum* result) const;
        /*!
            センサの種類に応じた単位を取得します。
            @note
            この関数は ofxSAT クラスを継承した具象クラスを作成するときに必要に応じてオーバーライトし、
            オーバーライトした関数からは内部状態と引数の妥当性の検証に利用することができます。
            @param [in] sensor ofxSAT::SensorEnum 型のセンサ定数
            @param [out] result 取得結果
            @return エラー情報
            @retval ::SATERROR_NO_SUPPORT 未サポート（正常終了）
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
         */
        virtual ofxSATError             getSensorUnit                   (SensorType sensor, UnitEnum* result) const;
        /*!
            センサの種類に応じた最小値を取得します。
            @note
            この関数は ofxSAT クラスを継承した具象クラスを作成するときに必要に応じてオーバーライトし、
            オーバーライトした関数からは内部状態と引数の妥当性の検証に利用することができます。
            @param [in] sensor ofxSAT::SensorEnum 型のセンサ定数
            @param [out] result 取得結果
            @param [in] size result に指定した変数のバイト数
            @return エラー情報
            @retval ::SATERROR_NO_SUPPORT 未サポート（正常終了）
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
         */
        virtual ofxSATError             getSensorMinimum                (SensorType sensor, void* result, int size) const;
        /*!
            センサの種類に応じた最大値を取得します。
            @note
            この関数は ofxSAT クラスを継承した具象クラスを作成するときに必要に応じてオーバーライトし、
            オーバーライトした関数からは内部状態と引数の妥当性の検証に利用することができます。
            @param [in] sensor ofxSAT::SensorEnum 型のセンサ定数
            @param [out] result 取得結果
            @param [in] size result に指定した変数のバイト数
            @return エラー情報
            @retval ::SATERROR_NO_SUPPORT 未サポート（正常終了）
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
         */
        virtual ofxSATError             getSensorMaximum                (SensorType sensor, void* result, int size) const;
        /*!
            センサの種類に応じた指定された時刻のデータを取得します。
            データ自体を取得する必要がないときは result 引数に NULL を、
            シミュレーションか否かを取得する必要がときには simulation 引数に NULL を指定することができます。
            @note
            この関数は ofxSAT クラスを継承した具象クラスを作成するときに必要に応じてオーバーライトし、
            オーバーライトした関数からは内部状態と引数の妥当性の検証に利用することができます。
         
            使い方１：データとシミュレーション結果を取得するとき
            @code
            ofxSATTime time;
            double value;
            bool simulation;
            ofxSATError error;
         
            time = ofxSATTime::currentTime();
            error = _sat->getSensorData(CONCRETE_SENSOR_ID, time, &value, sizeof(value), &simulation);
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
            error = _sat->getSensorData(CONCRETE_SENSOR_ID, time, &value, sizeof(value), NULL);
            if (error == SATERROR_OK) {
                cout << "value = " << value << endl;
            }
            else {
                cout << "error = " << error.print() << endl;
            }
            @endcode
            @param [in] sensor ofxSAT::SensorEnum 型のセンサ定数
            @param [in] time データを取得する時刻
            @param [out] result 取得結果
                @arg NULL : 結果を返さない
                @arg その他
            @param [in] size result に指定した変数のバイト数
            @param [out] simulation 取得結果はシミュレーション
                @arg NULL : 結果を返さない
                @arg その他
            @return エラー情報
            @retval ::SATERROR_NO_SUPPORT 未サポート（正常終了）
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
         */
        virtual ofxSATError             getSensorData                   (SensorType sensor, ofxSATTime const& time, void* result, int size, bool* simulation = NULL) const;
        /*!
            通知先クラスを設定します。
            setup() 関数を呼び出す前に通知先を設定します。
            引数に NULL を指定すると通知されなくなります。
            @param [in] param 通知先クラスのインスタンスへのポインタ
                @arg NULL : 通知しない
                @arg その他
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
         */
                ofxSATError             setNotifier                     (Notifier* param);
        /*!
            通知先クラスを取得します。
            @return 現在の通知先クラスのインスタンスへのポインタ
            @retval NULL 通知先クラスは設定されていない
            @retval その他
         */
                Notifier*               getNotifier                     (void) const;
        /*!
            setup() が正常におこなわれ、データの取得が可能かどうかを検証します。
            @return 検証結果
            @retval true 可能
            @retval false 不可能
         */
                bool                    isValid                         (void) const;
        /*!
            データの取得やさまざまな機能を利用できるように初期化をおこないます。
            @note
            この関数は ofxSAT クラスを継承した具象クラスを作成するときに必要に応じてオーバーライトし、
            オーバーライトした関数の始めに呼び出します。
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
         */
        virtual ofxSATError             setup                           (void);
        /*!
            データの取得やさまざまな機能を利用するために確保したリソースを解放します。
            @note
            この関数は ofxSAT クラスを継承した具象クラスを作成するときに必要に応じてオーバーライトし、
            オーバーライトした関数の最後に呼び出します。
            @return なし
         */
        virtual void                    cleanup                         (void);
        /*!
            希望する時刻のデータを更新するように要求します。
            @note
            この関数は ofxSAT クラスを継承した具象クラスを作成するときに必要に応じてオーバーライトし、
            オーバーライトした関数からは内部状態と引数の妥当性の検証に利用することができます。
            @param [in] time 希望する時刻
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
         */
        virtual ofxSATError             update                          (ofxSATTime const& time = ofxSATTime::currentTime());
    protected:
        /*!
            コンストラクタです。
            初期化に必要な最低限の処理をおこないます。
         */
        explicit                        ofxSAT                          (void);
        /*!
            ID を設定します。
            @param [in] param 設定する ID
            @return なし
         */
                void                    setID                           (std::string const& param);
        /*!
            TLE 情報と TLE を取得した時刻を設定します。
            通知先クラスが設定されていて TLE 情報もしくは時刻が更新されたときには、
            通知先クラスの Notifier::onNotifyTLE() 関数を ofEvent を利用してスレッドセーフに呼び出します。
            @param [in] tle TLE 情報
            @param [in] time TLE を取得した時刻
            @return なし
         */
                void                    setTLE                          (TLERec const& tle, ofxSATTime const& time);
        /*!
            通知先クラスが設定されているときには、
            通知先クラスの Notifier::onNotifyData() 関数を ofEvent を利用してスレッドセーフに呼び出します。
            @param [in] time 新しいデータの時刻
            @return なし
         */
                void                    notifyData                      (ofxSATTime const& time) const;
        /*!
            通知先クラスが設定されているときには、
            通知先クラスの Notifier::onNotifyFinish() 関数を ofEvent を利用してスレッドセーフに呼び出します。
            @param [in] error エラー情報
            @return なし
         */
                void                    notifyFinish                    (ofxSATError const& error) const;
        /*!
            引数に指定した文字列から半角スペースをすべて削除します。
            @note
            この関数は ofxSAT クラスを継承した具象クラスを作成するときに利用できるユーティリティー関数です。
            @param [in] param 文字列
            @return 新しい文字列
         */
        static  std::string             trimSpace                       (std::string const& param);
        /*!
            引数に指定した文字列から半角数字と '+', '-', '.' 以外の文字をすべて削除します。
            @note
            この関数は ofxSAT クラスを継承した具象クラスを作成するときに利用できるユーティリティー関数です。
            @param [in] param 文字列
            @return 新しい文字列
         */
        static  std::string             trimNonNumeric                  (std::string const& param);
        /*!
            引数に指定した文字列の中の特定の文字列を新しい文字列にすべて置換します。
            @note
            この関数は ofxSAT クラスを継承した具象クラスを作成するときに利用できるユーティリティー関数です。
            @param [in] string 処理対象の文字列
            @param [in] from 置換される文字列
            @param [in] to 置換する文字列
            @return 新しい文字列
         */
        static  std::string             replaceString                   (std::string const& string, std::string const& from, std::string const& to);
        /*!
            format 引数に指定した書式のデータを表現するのに必要なバイト数よりも
            size 引数に指定した値が大きいかどうかを検証します。
            @note
            この関数は ofxSAT クラスを継承した具象クラスを作成するときに利用できるユーティリティー関数です。
            @param [in] format 書式
            @param [in] size バイト数
            @return エラー情報
            @retval ::SATERROR_OK size >= 必要なバイト数
            @retval ::SATERROR_FAILED 書式が不正
            @retval ::SATERROR_INVALID_PARAM size < 必要なバイト数
         */
        static  ofxSATError             checkSize                       (FormatEnum format, int size);
    private:
                void                    handleNotifyTLE                 (EventTLERec& event);
                void                    handleNotifyData                (EventDataRec& event);
                void                    handleNotifyFinish              (EventFinishRec& event);
    private:
                                        ofxSAT                          (ofxSAT const&);
                ofxSAT&                 operator=                       (ofxSAT const&);
};

/*public */inline std::string const& ofxSAT::getID(void) const
{
    return _id;
}

/*public */inline ofxSAT::Notifier* ofxSAT::getNotifier(void) const
{
    return _notifier;
}

/*public */inline bool ofxSAT::isValid(void) const
{
    return _state;
}

/*protected */inline void ofxSAT::setID(std::string const& param)
{
    _id = param;
    return;
}

#endif
