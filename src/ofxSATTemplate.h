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
**      ofxSATTemplate.h
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

#ifndef __OFX_SATTEMPLATE_H
#define __OFX_SATTEMPLATE_H

/*!
    @file
    各種さまざまな衛星を表すクラスを実装する起点となるテンプレートクラスを含みます。
    具体的な衛星を表すクラスはこのクラスの実装を参考にして作成することができます。
 */

#include "ofxSATType.h"
#include "ofxSATLocalDB.h"

//! 各種さまざまな衛星を表すクラスを実装する起点となるテンプレートクラス
/*!
    ofxSATTemplate クラスは各種さまざまな衛星を表すクラスを実装するときの起点となる実装を定義します。
    具体的な衛星を表すクラスはこのクラスの実装を参考にして作成することができます。
    このクラスはテンプレートとして実装を参考にするためのクラスなので、このクラスのインスタンスを作成しても有意義では有りません。
 */
class ofxSATTemplate : public ofxSATLocalDB {
    public:
        /*!
            自クラスを表す型の別名です。
         */
        typedef ofxSATTemplate          self;
        /*!
            親クラスを表す型の別名です。
         */
        typedef ofxSATLocalDB           super;
    
    public:
        /*!
            衛星がサポートしているセンサを表す定数です。
            ofxSATTemplate::SENSOR_LIMIT は具体的なセンサを表す値ではなくセンサ定数の最大値を表します。
         */
        enum SensorEnum {
            //! サンプルセンサ
            SENSOR_NONE                 = super::SENSOR_LIMIT,
            // default
            //! センサ定数の最大値
            SENSOR_LIMIT
        };
    
    public:
        /*!
            コンストラクタです。
            初期化に必要な最低限の処理をおこないます。
         */
        explicit                        ofxSATTemplate                  (void);
        /*!
            デストラクタです。
            管理しているリソースを解放します。
         */
        virtual                         ~ofxSATTemplate                 (void);
        /*!
            センサデータを取得可能な時刻の数を取得します。
            @param [out] result 取得結果
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
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
         */
        virtual ofxSATError             getAvailableCount               (ofxSATTime const& begin, ofxSATTime const& end, int* result) const;
        /*!
            センサデータを取得可能な時刻のリストを取得します。
            @param [out] result 取得結果
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
         */
        virtual ofxSATError             getAvailableTime                (std::vector<ofxSATTime>* result) const;
        /*!
            引数に指定した時間範囲の中でセンサデータを取得可能な時刻のリストを取得します。
            時間範囲は [begin, end) で指定します。
            @param [in] begin 開始時刻（以上）
            @param [in] end 終了時刻（未満）
            @param [out] result 取得結果
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
         */
        virtual ofxSATError             getAvailableTime                (ofxSATTime const& begin, ofxSATTime const& end, std::vector<ofxSATTime>* result) const;
        /*!
            センサの種類に応じた書式を取得します。
            @param [in] sensor ofxSATTemplate::SensorEnum 型のセンサ定数
            @param [out] result 取得結果
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
         */
        virtual ofxSATError             getSensorFormat                 (SensorType sensor, FormatEnum* result) const;
        /*!
            センサの種類に応じた単位を取得します。
            @param [in] sensor ofxSATTemplate::SensorEnum 型のセンサ定数
            @param [out] result 取得結果
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
         */
        virtual ofxSATError             getSensorUnit                   (SensorType sensor, UnitEnum* result) const;
        /*!
            センサの種類に応じた最小値を取得します。
            @param [in] sensor ofxSATTemplate::SensorEnum 型のセンサ定数
            @param [out] result 取得結果
            @param [in] size result に指定した変数のバイト数
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
         */
        virtual ofxSATError             getSensorMinimum                (SensorType sensor, void* result, int size) const;
        /*!
            センサの種類に応じた最大値を取得します。
            @param [in] sensor ofxSATTemplate::SensorEnum 型のセンサ定数
            @param [out] result 取得結果
            @param [in] size result に指定した変数のバイト数
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
            @retval ::SATERROR_INVALID_PARAM パラメータが不正
         */
        virtual ofxSATError             getSensorMaximum                (SensorType sensor, void* result, int size) const;
        /*!
            センサの種類に応じた指定された時刻のデータを取得します。
            データ自体を取得する必要がないときは result 引数に NULL を、
            シミュレーションか否かを取得する必要がときには simulation 引数に NULL を指定することができます。
            @param [in] sensor ofxSATTemplate::SensorEnum 型のセンサ定数
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
         */
        virtual ofxSATError             getSensorData                   (SensorType sensor, ofxSATTime const& time, void* result, int size, bool* simulation = NULL) const;
        /*!
            データの取得やさまざまな機能を利用できるように初期化をおこないます。
            @return エラー情報
            @retval ::SATERROR_OK 正常終了
            @retval ::SATERROR_INVALID_STATE 呼び出すタイミングが不正
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
                                        ofxSATTemplate                  (ofxSATTemplate const&);
                ofxSATTemplate&         operator=                       (ofxSATTemplate const&);
};

#endif
