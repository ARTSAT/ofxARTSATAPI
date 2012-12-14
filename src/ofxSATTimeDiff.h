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
**      ofxSATTimeDiff.h
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

#ifndef __OFX_SATTIMEDIFF_H
#define __OFX_SATTIMEDIFF_H

/*!
    @file
    ARTSAT API で利用する時刻差を表現するクラスを含みます。
 */

#include "ofxSATType.h"
#include <time.h>

//! 時刻差を表現するクラス
/*!
 ２つの時刻の差を扱うには ofxSATTimeDiff クラスを利用します。
 時刻を扱うには ofxSATTime クラスを利用します。
 */
class ofxSATTimeDiff {
    private:
                time_t                  _second;
    
    public:
        /*!
            コンストラクタです。
            値は初期化されません。
         */
        explicit                        ofxSATTimeDiff                  (void);
        /*!
            コンストラクタです。
            引数に指定した値が初期値となります。
            @param [in] param 初期値
         */
                                        ofxSATTimeDiff                  (ofxSATTimeDiff const& param);
        /*!
            コンストラクタです。
            引数に指定した日差・時差・分差・秒差をもとにして初期値を設定します。
            各桁で繰り上げや繰り下げが発生したときにも正しく設定されます。
            @param [in] day 日差
            @param [in] hour 時差
            @param [in] minute 分差
            @param [in] second 秒差
         */
        explicit                        ofxSATTimeDiff                  (int day, int hour, int minute, int second);
        /*!
            コンストラクタです。
            引数に指定した時差・分差・秒差をもとにして初期値を設定します。
            各桁で繰り上げや繰り下げが発生したときにも正しく設定されます。
            @param [in] hour 時差
            @param [in] minute 分差
            @param [in] second 秒差
         */
        explicit                        ofxSATTimeDiff                  (int hour, int minute, int second);
        /*!
            コンストラクタです。
            引数に指定した分差・秒差をもとにして初期値を設定します。
            各桁で繰り上げや繰り下げが発生したときにも正しく設定されます。
            @param [in] minute 分差
            @param [in] second 秒差
         */
        explicit                        ofxSATTimeDiff                  (int minute, int second);
        /*!
            コンストラクタです。
            引数に指定した POSIX 時刻としての秒差をもとにして初期値を設定します。
            @param [in] second POSIX 時刻としての秒差
         */
        explicit                        ofxSATTimeDiff                  (time_t second);
        /*!
            デストラクタです。
         */
                                        ~ofxSATTimeDiff                 (void);
        /*!
            値を代入します。
            @param [in] param 代入する値
            @return 自分への参照
         */
                ofxSATTimeDiff&         operator=                       (ofxSATTimeDiff const& param);
        /*!
            値を加算します。
            @param [in] param 加算する値
            @return 自分への参照
         */
                ofxSATTimeDiff&         operator+=                      (ofxSATTimeDiff const& param);
        /*!
            値を減算します。
            @param [in] param 減算する値
            @return 自分への参照
         */
                ofxSATTimeDiff&         operator-=                      (ofxSATTimeDiff const& param);
        /*!
            値を乗算します。
            @param [in] param 乗算する値
            @return 自分への参照
         */
                ofxSATTimeDiff&         operator*=                      (int param);
        /*!
            値を除算します。
            @param [in] param 除算する値
            @return 自分への参照
         */
                ofxSATTimeDiff&         operator/=                      (int param);
        /*!
            値の剰余を計算します。
            @param [in] param 除算する値
            @return 自分への参照
         */
                ofxSATTimeDiff&         operator%=                      (int param);
        /*!
            正の値を計算します。
            @return 計算結果
         */
                ofxSATTimeDiff          operator+                       (void) const;
        /*!
            負の値を計算します。
            @return 計算結果
         */
                ofxSATTimeDiff          operator-                       (void) const;
        /*!
            値を設定します。
            @param [in] param 設定する値
            @return 自分への参照
         */
                ofxSATTimeDiff&         set                             (ofxSATTimeDiff const& param);
        /*!
            引数に指定した日差・時差・分差・秒差をもとにして値を設定します。
            各桁で繰り上げや繰り下げが発生したときにも正しく設定されます。
            @param [in] day 日差
            @param [in] hour 時差
            @param [in] minute 分差
            @param [in] second 秒差
            @return 自分への参照
         */
                ofxSATTimeDiff&         set                             (int day, int hour, int minute, int second);
        /*!
            値を日差・時差・分差・秒差に分解して取得します。
            各桁を取得する必要がない場合にはそれぞれの引数に NULL を指定することができます。
            @param [out] day 現在の日差
                @arg NULL : 日差を返さない
                @arg その他
            @param [out] hour 現在の時差
                @arg NULL : 時差を返さない
                @arg その他
            @param [out] minute 現在の分差
                @arg NULL : 分差を返さない
                @arg その他
            @param [out] second 現在の秒差
                @arg NULL : 秒差を返さない
                @arg その他
            @return なし
         */
                void                    get                             (int* day, int* hour, int* minute, int* second) const;
        /*!
            引数に指定した時差・分差・秒差をもとにして値を設定します。
            各桁で繰り上げや繰り下げが発生したときにも正しく設定されます。
            @param [in] hour 時差
            @param [in] minute 分差
            @param [in] second 秒差
            @return 自分への参照
         */
                ofxSATTimeDiff&         set                             (int hour, int minute, int second);
        /*!
            値を時差・分差・秒差に分解して取得します。
            各桁を取得する必要がない場合にはそれぞれの引数に NULL を指定することができます。
            @param [out] hour 現在の時差
                @arg NULL : 時差を返さない
                @arg その他
            @param [out] minute 現在の分差
                @arg NULL : 分差を返さない
                @arg その他
            @param [out] second 現在の秒差
                @arg NULL : 秒差を返さない
                @arg その他
            @return なし
         */
                void                    get                             (int* hour, int* minute, int* second) const;
        /*!
            引数に指定した分差・秒差をもとにして値を設定します。
            各桁で繰り上げや繰り下げが発生したときにも正しく設定されます。
            @param [in] minute 分差
            @param [in] second 秒差
            @return 自分への参照
         */
                ofxSATTimeDiff&         set                             (int minute, int second);
        /*!
            値を分差・秒差に分解して取得します。
            各桁を取得する必要がない場合にはそれぞれの引数に NULL を指定することができます。
            @param [out] minute 現在の分差
                @arg NULL : 分差を返さない
                @arg その他
            @param [out] second 現在の秒差
                @arg NULL : 秒差を返さない
                @arg その他
            @return なし
         */
                void                    get                             (int* minute, int* second) const;
        /*!
            引数に指定した POSIX 時刻としての秒差をもとにして値を設定します。
            @param [in] second POSIX 時刻としての秒差
            @return 自分への参照
         */
                ofxSATTimeDiff&         set                             (time_t second);
        /*!
            値を加算します。
            @param [in] param 加算する値
            @return 自分への参照
         */
                ofxSATTimeDiff&         add                             (ofxSATTimeDiff const& param);
        /*!
            値を減算します。
            @param [in] param 減算する値
            @return 自分への参照
         */
                ofxSATTimeDiff&         sub                             (ofxSATTimeDiff const& param);
        /*!
            値を乗算します。
            @param [in] param 乗算する値
            @return 自分への参照
         */
                ofxSATTimeDiff&         mul                             (int param);
        /*!
            値を除算します。
            @param [in] param 除算する値
            @return 自分への参照
         */
                ofxSATTimeDiff&         div                             (int param);
        /*!
            値の剰余を計算します。
            @param [in] param 除算する値
            @return 自分への参照
         */
                ofxSATTimeDiff&         mod                             (int param);
        /*!
            負の値を計算します。
            @return 自分への参照
         */
                ofxSATTimeDiff&         neg                             (void);
        /*!
            値を比較します。
            @param [in] param 比較する値
            @return 比較結果
            @retval true 同じ
            @retval false 同じでない
         */
                bool                    equals                          (ofxSATTimeDiff const& param) const;
        /*!
            値の大小を比較します。
            @param [in] param 比較する値
            @return 比較結果
            @retval 0 同じ (this == param)
            @retval +1 大きい (this > param)
            @retval -1 小さい (this < param)
         */
                int                     compare                         (ofxSATTimeDiff const& param) const;
        /*!
            POSIX 時刻としての秒差を取得します。
            @return POSIX 時刻としての秒差
         */
                time_t                  asTime_t                        (void) const;
        /*!
            UTC 時刻からのオフセットを取得します。
            @return 取得結果
         */
        static  ofxSATTimeDiff          localTimeOffset                 (void);
};

/*!
    値を加算します。
    @param [in] x 左辺値
    @param [in] y 右辺値
    @return 時刻差
 */
extern  ofxSATTimeDiff                  operator+                       (ofxSATTimeDiff const& x, ofxSATTimeDiff const& y);
/*!
    値を減算します。
    @param [in] x 左辺値
    @param [in] y 右辺値
    @return 時刻差
 */
extern  ofxSATTimeDiff                  operator-                       (ofxSATTimeDiff const& x, ofxSATTimeDiff const& y);
/*!
    値を乗算します。
    @param [in] x 左辺値
    @param [in] y 右辺値
    @return 時刻差
 */
extern  ofxSATTimeDiff                  operator*                       (ofxSATTimeDiff const& x, int y);
/*!
    値を除算します。
    @param [in] x 左辺値
    @param [in] y 右辺値
    @return 時刻差
 */
extern  ofxSATTimeDiff                  operator/                       (ofxSATTimeDiff const& x, int y);
/*!
    値の剰余を計算します。
    @param [in] x 左辺値
    @param [in] y 右辺値
    @return 時刻差
 */
extern  ofxSATTimeDiff                  operator%                       (ofxSATTimeDiff const& x, int y);
/*!
    値を比較します。
    @param [in] x 左辺値
    @param [in] y 右辺値
    @return 比較結果
    @retval true 同じ
    @retval false 同じでない
 */
extern  bool                            operator==                      (ofxSATTimeDiff const& x, ofxSATTimeDiff const& y);
/*!
    値を逆比較します。
    @param [in] x 左辺値
    @param [in] y 右辺値
    @return 比較結果
    @retval true 同じでない
    @retval false 同じ
 */
extern  bool                            operator!=                      (ofxSATTimeDiff const& x, ofxSATTimeDiff const& y);
/*!
    値の大小（未満）を比較します。
    @param [in] x 左辺値
    @param [in] y 右辺値
    @return 比較結果
    @retval true 真 (this < param)
    @retval false 偽 (this >= param)
 */
extern  bool                            operator<                       (ofxSATTimeDiff const& x, ofxSATTimeDiff const& y);
/*!
    値の大小（以下）を比較します。
    @param [in] x 左辺値
    @param [in] y 右辺値
    @return 比較結果
    @retval true 真 (this <= param)
    @retval false 偽 (this > param)
 */
extern  bool                            operator<=                      (ofxSATTimeDiff const& x, ofxSATTimeDiff const& y);
/*!
    値の大小（より大きい）を比較します。
    @param [in] x 左辺値
    @param [in] y 右辺値
    @return 比較結果
    @retval true 真 (this > param)
    @retval false 偽 (this <= param)
 */
extern  bool                            operator>                       (ofxSATTimeDiff const& x, ofxSATTimeDiff const& y);
/*!
    値の大小（以上）を比較します。
    @param [in] x 左辺値
    @param [in] y 右辺値
    @return 比較結果
    @retval true 真 (this >= param)
    @retval false 偽 (this < param)
 */
extern  bool                            operator>=                      (ofxSATTimeDiff const& x, ofxSATTimeDiff const& y);

/*public */inline ofxSATTimeDiff::ofxSATTimeDiff(void)
{
}

/*public */inline ofxSATTimeDiff::ofxSATTimeDiff(ofxSATTimeDiff const& param)
{
    set(param);
}

/*public */inline ofxSATTimeDiff::ofxSATTimeDiff(int day, int hour, int minute, int second)
{
    set(day, hour, minute, second);
}

/*public */inline ofxSATTimeDiff::ofxSATTimeDiff(int hour, int minute, int second)
{
    set(hour, minute, second);
}

/*public */inline ofxSATTimeDiff::ofxSATTimeDiff(int minute, int second)
{
    set(minute, second);
}

/*public */inline ofxSATTimeDiff::ofxSATTimeDiff(time_t second)
{
    set(second);
}

/*public */inline ofxSATTimeDiff::~ofxSATTimeDiff(void)
{
}

/*public */inline ofxSATTimeDiff& ofxSATTimeDiff::operator=(ofxSATTimeDiff const& param)
{
    return set(param);
}

/*public */inline ofxSATTimeDiff& ofxSATTimeDiff::operator+=(ofxSATTimeDiff const& param)
{
    return add(param);
}

/*public */inline ofxSATTimeDiff& ofxSATTimeDiff::operator-=(ofxSATTimeDiff const& param)
{
    return sub(param);
}

/*public */inline ofxSATTimeDiff& ofxSATTimeDiff::operator*=(int param)
{
    return mul(param);
}

/*public */inline ofxSATTimeDiff& ofxSATTimeDiff::operator/=(int param)
{
    return div(param);
}

/*public */inline ofxSATTimeDiff& ofxSATTimeDiff::operator%=(int param)
{
    return mod(param);
}

/*public */inline ofxSATTimeDiff ofxSATTimeDiff::operator+(void) const
{
    return ofxSATTimeDiff(+_second);
}

/*public */inline ofxSATTimeDiff ofxSATTimeDiff::operator-(void) const
{
    return ofxSATTimeDiff(-_second);
}

/*public */inline ofxSATTimeDiff& ofxSATTimeDiff::set(ofxSATTimeDiff const& param)
{
    _second = param._second;
    return *this;
}

/*public */inline ofxSATTimeDiff& ofxSATTimeDiff::set(time_t second)
{
    _second = second;
    return *this;
}

/*public */inline ofxSATTimeDiff& ofxSATTimeDiff::add(ofxSATTimeDiff const& param)
{
    _second += param._second;
    return *this;
}

/*public */inline ofxSATTimeDiff& ofxSATTimeDiff::sub(ofxSATTimeDiff const& param)
{
    _second -= param._second;
    return *this;
}

/*public */inline ofxSATTimeDiff& ofxSATTimeDiff::mul(int param)
{
    _second *= param;
    return *this;
}

/*public */inline ofxSATTimeDiff& ofxSATTimeDiff::div(int param)
{
    _second /= param;
    return *this;
}

/*public */inline ofxSATTimeDiff& ofxSATTimeDiff::mod(int param)
{
    _second %= param;
    return *this;
}

/*public */inline ofxSATTimeDiff& ofxSATTimeDiff::neg(void)
{
    _second = -_second;
    return *this;
}

/*public */inline bool ofxSATTimeDiff::equals(ofxSATTimeDiff const& param) const
{
    return (_second == param._second);
}

/*public */inline time_t ofxSATTimeDiff::asTime_t(void) const
{
    return _second;
}

inline ofxSATTimeDiff operator+(ofxSATTimeDiff const& x, ofxSATTimeDiff const& y)
{
    return ofxSATTimeDiff(x).operator+=(y);
}

inline ofxSATTimeDiff operator-(ofxSATTimeDiff const& x, ofxSATTimeDiff const& y)
{
    return ofxSATTimeDiff(x).operator-=(y);
}

inline ofxSATTimeDiff operator*(ofxSATTimeDiff const& x, int y)
{
    return ofxSATTimeDiff(x).operator*=(y);
}

inline ofxSATTimeDiff operator/(ofxSATTimeDiff const& x, int y)
{
    return ofxSATTimeDiff(x).operator/=(y);
}

inline ofxSATTimeDiff operator%(ofxSATTimeDiff const& x, int y)
{
    return ofxSATTimeDiff(x).operator%=(y);
}

inline bool operator==(ofxSATTimeDiff const& x, ofxSATTimeDiff const& y)
{
    return x.equals(y);
}

inline bool operator!=(ofxSATTimeDiff const& x, ofxSATTimeDiff const& y)
{
    return !x.equals(y);
}

inline bool operator<(ofxSATTimeDiff const& x, ofxSATTimeDiff const& y)
{
    return (x.compare(y) < 0);
}

inline bool operator<=(ofxSATTimeDiff const& x, ofxSATTimeDiff const& y)
{
    return (x.compare(y) <= 0);
}

inline bool operator>(ofxSATTimeDiff const& x, ofxSATTimeDiff const& y)
{
    return (x.compare(y) > 0);
}

inline bool operator>=(ofxSATTimeDiff const& x, ofxSATTimeDiff const& y)
{
    return (x.compare(y) >= 0);
}

#endif
