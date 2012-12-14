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
**      ofxSATError.h
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

#ifndef __OFX_SATERROR_H
#define __OFX_SATERROR_H

/*!
    @file
    ARTSAT API で利用するエラー定数とエラー値を表現するクラスを含みます。
 */

#include <string>

/*!
    ARTSAT API が定義するエラー定数です。
    ofxSATError クラスに代入して利用します。
    ::SATERROR_OK はエラーなしを表します。
    ::SATERROR_LIMIT は具体的なエラーを表す値ではなくエラー定数の最大値を表します。
 */
enum SATErrorEnum {
    //! エラーなし
    SATERROR_OK,
    //! 一般的なエラー
    SATERROR_FAILED,
    //! 関数や機能がサポートされていない
    SATERROR_NO_SUPPORT,
    //! 結果が存在しない
    SATERROR_NO_RESULT,
    //! 空きメモリが確保できない
    SATERROR_NO_MEMORY,
    //! 引数が正しくない
    SATERROR_INVALID_PARAM,
    //! 関数や機能の内部状態が正しくない
    SATERROR_INVALID_STATE,
    //! 書式が正しくない
    SATERROR_INVALID_FORMAT,
    //! 結果を即時に取得できない
    SATERROR_WAIT_RESULT,
    //! ネットワークが接続されていない
    SATERROR_NETWORK_DOWN,
    //! ネットワークレスポンスのステータスコードが正しくない
    SATERROR_NETWORK_CODE,
    //! エラー定数の最大値
    SATERROR_LIMIT
};

//! エラー値を表現するクラス
/*!
    エラー値を扱うには ofxSATError クラスを利用します。
    ofxSATError 型の変数を定義し ::SATErrorEnum 型の定数を代入します。
    ::SATErrorEnum 型以外の int 型の値を扱うこともできます。
 */
class ofxSATError {
    private:
                int                     _error;
    
    public:
        /*!
            コンストラクタです。
            値は初期化されません。
         */
        explicit                        ofxSATError                     (void);
        /*!
            コンストラクタです。
            引数に指定した値が初期値となります。
            @param [in] param 初期値
         */
                                        ofxSATError                     (ofxSATError const& param);
        /*!
            コンストラクタです。
            引数に指定した値が初期値となります。
            int 型から ofxSATError 型へは暗黙の型変換を利用できます。
            @param [in] param 初期値
         */
                                        ofxSATError                     (int param);
        /*!
            デストラクタです。
         */
                                        ~ofxSATError                    (void);
        /*!
            値を代入します。
            @param [in] param 代入する値
            @return 自分への参照
         */
                ofxSATError&            operator=                       (ofxSATError const& param);
        /*!
            値を代入します。
            @param [in] param 代入する値
            @return 自分への参照
         */
                ofxSATError&            operator=                       (int param);
        /*!
            int 型の値を返します。
            ofxSATError 型から int 型へは暗黙の型変換を利用できます。
            @return int 型の現在の値
         */
                                        operator int                    (void) const;
        /*!
            値を設定します。
            @param [in] param 設定する値
            @return 自分への参照
         */
                ofxSATError&            set                             (ofxSATError const& param);
        /*!
            値を設定します。
            @param [in] param 設定する値
            @return 自分への参照
         */
                ofxSATError&            set                             (int param);
        /*!
            値を取得します。
            @return 現在の値
         */
                int                     get                             (void) const;
        /*!
            値を比較します。
            @param [in] param 比較する値
            @return 比較結果
            @retval true 同じ
            @retval false 同じでない
         */
                bool                    equals                          (ofxSATError const& param) const;
        /*!
            値を比較します。
            @param [in] param 比較する値
            @return 比較結果
            @retval true 同じ
            @retval false 同じでない
         */
                bool                    equals                          (int param) const;
        /*!
            エラーの詳細を文字列として取得します。
            @return エラーの詳細を表す文字列
         */
                std::string             print                           (void) const;
};

/*!
    値を比較します。
    @param [in] x 左辺値
    @param [in] y 右辺値
    @return 比較結果
    @retval true 同じ
    @retval false 同じでない
 */
extern  bool                            operator==                      (ofxSATError const& x, ofxSATError const& y);
/*!
    値を比較します。
    @param [in] x 左辺値
    @param [in] y 右辺値
    @return 比較結果
    @retval true 同じ
    @retval false 同じでない
 */
extern  bool                            operator==                      (ofxSATError const& x, int y);
/*!
    値を比較します。
    @param [in] x 左辺値
    @param [in] y 右辺値
    @return 比較結果
    @retval true 同じ
    @retval false 同じでない
 */
extern  bool                            operator==                      (int x, ofxSATError const& y);
/*!
    値を逆比較します。
    @param [in] x 左辺値
    @param [in] y 右辺値
    @return 比較結果
    @retval true 同じでない
    @retval false 同じ
 */
extern  bool                            operator!=                      (ofxSATError const& x, ofxSATError const& y);
/*!
    値を逆比較します。
    @param [in] x 左辺値
    @param [in] y 右辺値
    @return 比較結果
    @retval true 同じでない
    @retval false 同じ
 */
extern  bool                            operator!=                      (ofxSATError const& x, int y);
/*!
    値を逆比較します。
    @param [in] x 左辺値
    @param [in] y 右辺値
    @return 比較結果
    @retval true 同じでない
    @retval false 同じ
 */
extern  bool                            operator!=                      (int x, ofxSATError const& y);

/*public */inline ofxSATError::ofxSATError(void)
{
}

/*public */inline ofxSATError::ofxSATError(ofxSATError const& param)
{
    set(param);
}

/*public */inline ofxSATError::ofxSATError(int param)
{
    set(param);
}

/*public */inline ofxSATError::~ofxSATError(void)
{
}

/*public */inline ofxSATError& ofxSATError::operator=(ofxSATError const& param)
{
    return set(param);
}

/*public */inline ofxSATError& ofxSATError::operator=(int param)
{
    return set(param);
}

/*public */inline ofxSATError::operator int(void) const
{
    return get();
}

/*public */inline ofxSATError& ofxSATError::set(ofxSATError const& param)
{
    _error = param._error;
    return *this;
}

/*public */inline ofxSATError& ofxSATError::set(int param)
{
    _error = param;
    return *this;
}

/*public */inline int ofxSATError::get(void) const
{
    return _error;
}

/*public */inline bool ofxSATError::equals(ofxSATError const& param) const
{
    return (_error == param._error);
}

/*public */inline bool ofxSATError::equals(int param) const
{
    return (_error == param);
}

inline bool operator==(ofxSATError const& x, ofxSATError const& y)
{
    return x.equals(y);
}

inline bool operator==(ofxSATError const& x, int y)
{
    return x.equals(y);
}

inline bool operator==(int x, ofxSATError const& y)
{
    return y.equals(x);
}

inline bool operator!=(ofxSATError const& x, ofxSATError const& y)
{
    return !x.equals(y);
}

inline bool operator!=(ofxSATError const& x, int y)
{
    return !x.equals(y);
}

inline bool operator!=(int x, ofxSATError const& y)
{
    return !y.equals(x);
}

#endif
