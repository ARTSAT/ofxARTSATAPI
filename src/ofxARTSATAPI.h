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
**      ofxARTSATAPI.h
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

#ifndef __OFX_ARTSATAPI_H
#define __OFX_ARTSATAPI_H

/*!
    @file
    ARTSAT API を利用するときにはこのファイルを #include します。
    ARTSAT API に関連する必要なファイルが自動的に読み込まれます。
 */

#include "ofxSATType.h"
#include "ofxICCPhysicalSAT.h"
#include "ofxInvaderSAT.h"
#ifdef __USE_NAKASUKALAB
#include "ofxXiIVSAT.h"
#include "ofxXiVSAT.h"
#include "ofxPrismSAT.h"
#endif
#include "ofxEasyCubeSAT.h"

/*!
    @mainpage ARTSAT API / 衛星芸術プロジェクト
    @par ARTSAT API とは？
    ARTSAT API とはさまざまな人工衛星のテレメトリーデータや状態を取得したり衛星を制御するための
    アプリケーションインターフェースを提供するライブラリです。
    @par
    ARTSAT API の現在のバージョンは openFrameworks 用に提供されています。
    現在のバージョンでは衛星のテレメトリーデータを取得することができ、
    INVADER 衛星（シミュレーション）・PRISM 衛星・XI-V 衛星・XI-IV 衛星をサポートします。
    また各種衛星に対応できるように構造化された設計になっており、
    テンプレートクラスを起点に各種関数を実装することで未対応の衛星にも対応することができます。
    @sa http://artsat.jp/
    @sa http://api.artsat.jp/
    @sa http://api.artsat.jp/web/
    @sa http://www.openframeworks.cc/
 
    @par 動作推奨環境
    - OS: MacOS X 10.6.8 以上
    - 開発環境: Xcode 4.2 以上
    - フレームワーク: openFrameworks 0073 osx, openFrameworks 0073 ios
    - その他: SQLite 3 以上
 
    @par ダウンロード
    最新版の ARTSAT API は http://api.artsat.jp/of/download/ofxARTSATAPI.zip からダウンロードすることができます。\n
    古いバージョンの ARTSAT API は http://api.artsat.jp/of/download/archive/ を参照してください。\n
 
    @par 公開リポジトリ
    ARTSAT API の github 公開リポジトリは http://github.com/ARTSAT です。\n
    このリポジトリからは ARTSAT API の開発中の最新バージョンを取得することができます。\n
    また、開発に参加していただくことも可能です。\n
 
    @par ARTSAT API を使う
    ARTSAT API を利用するには始めに ofxARTSATAPI.h ヘッダファイルをインクルードします。
    ofxARTSATAPI.h ファイルは関連する必要なファイルを自動的に全てインクルードしますので詳細を考慮する必要はありません。
    @par
    @code
    #include "ofxARTSATAPI.h"
    @endcode
    @par
    ARTSAT API で最も重要なクラスは ofxSAT クラスです。
    このクラスは衛星のテレメトリーデータを取得したり衛星を制御するために必要な関数の抽象的なインターフェースを提供します。
    各種衛星を扱うクラスは ofxSAT クラスを継承した具象クラスとして実装されます。
    @par
    ofxSAT クラスはインターフェースクラスであるため、実際に具体的な衛星を扱う場合には具象クラスのインスタンスを生成します。
    例えば、INVADER 衛星を制御する場合には ofxInvaderSAT クラスを利用します。
    @par
    方法１: クラスメンバとしてインスタンスを管理する
    @code
    class testApp : public ofBaseApp {
        private:
            ofxInvaderSAT _invader;
            ...
    };

    void testApp::setup(void)
    {
        _invader.setup();
        return;
    }

    void testApp::exit(void)
    {
        _invader.cleanup();
        return;
    }
    @endcode
    @par
    方法２: クラスメンバとしてインスタンスのポインタを管理する
    @code
    class testApp : public ofBaseApp {
        private:
            ofxInvaderSAT* _invader;
            ...
    };

    void testApp::setup(void)
    {
        _invader = new ofxInvaderSAT;
        _invader->setup();
        return;
    }

    void testApp::exit(void)
    {
        _invader->cleanup();
        delete _invader;
        return;
    }
    @endcode
    @par
    方法３: 抽象クラスのポインタ型で管理する
    @code
    class testApp : public ofBaseApp {
        private:
            ofxSAT* _invader;
            ...
    };

    void testApp::setup(void)
    {
        _invader = new ofxInvaderSAT;
        _invader->setup();
        return;
    }

    void testApp::exit(void)
    {
        _invader->cleanup();
        delete _invader;
        return;
    }
    @endcode
    @par
    @note
    上記のようにいくつかの記述方法がありますが、衛星にアクセスしている間は ofxSAT クラスを継承したクラスのインスタンスが連続して有効でなければいけません。
    通常 ofxSAT クラスを継承したクラスのインスタンスはアプリケーションクラスのクラスメンバとします。
    @par
    いくつかの関数は呼び出し後に結果を通知として非同期に返すことがあります。
    ofxSAT::Notifier クラスを継承したクラスを作成し ofxSAT::Notifier クラスが定義する仮想関数を
    オーバーライトし ofxSAT::setNotifier() 関数を呼び出すことで通知を受け取ることができます。
    @par
    @code
    class testApp : public ofBaseApp, private ofxSAT::Notifier {
        ...
        private:
            virtual void onNotifyTLE(ofxSAT::TLERec const& tle, ofxSATTime const& time);
            virtual void onNotifyData(ofxSATTime const& time);
            virtual void onNotifyFinish(ofxSATError const& error);
    };

    void testApp::setup(void)
    {
        _invader.setNotifier(this);
        _invader.setup();
        return;
    }
    @endcode
    @par
    衛星の時刻データは ofxSATTime クラスと ofxSATTimeDiff クラスをもちいて表現されます。
    ofxSATTime クラスは１秒を最小単位とする日付と時間のペアを管理したり時刻の演算を簡単に行うことができます。
    ofxSATTimeDiff クラスは時刻の差を管理するために利用します。
    @par
    @code
    ofxSATTime current;
    ofxSATTime oneDayAfter;
    ofxSATTimeDiff diff;

    current = ofxSATTime::currentTime();
    oneDayAfter = current;
    oneDayAfter.addDay(1);
    cout << current.format("%YYYY/%MM/%DD %hh:%mm:%ss") << endl;
    cout << oneDayAfter.format("%YYYY/%MM/%DD %hh:%mm:%ss") << endl;

    diff = oneDayAfter - current;
    cout << diff.asTime_t() << endl;
    @endcode

    @par サンプルソースコード
    次のサンプルは、現在時刻の１時間前から現在時刻までの +X 面の太陽電池の温度を取得して表示します。
    また、新しい TLE 情報やテレメトリーデータが取得されたときにメッセージを表示します。
    @par
    @code
    #include "ofMain.h"
    #include "ofxARTSATAPI.h"

    class testApp : public ofBaseApp, private ofxSAT::Notifier {
        private:
            ofxInvaderSAT _invader;
            
        public:
            void setup(void);
            void exit(void);
            void draw(void);
        private:
            virtual void onNotifyTLE(ofxSAT::TLERec const& tle, ofxSATTime const& time);
            virtual void onNotifyData(ofxSATTime const& time);
    };

    void testApp::setup(void)
    {
        if (_invader.setNotifier(this) == SATERROR_OK) {
            if (_invader.setup() == SATERROR_OK) {
                cout << "Hello ARTSAT." << endl;
            }
        }
        return;
    }

    void testApp::exit(void)
    {
        _invader.cleanup();
        return;
    }

    void testApp::draw(void)
    {
        ofxSATTime begin;
        ofxSATTime end;
        std::vector<ofxSATTime> available;
        double value;
        int i;
        
        end = ofxSATTime::currentTime();
        begin = ofxSATTime(end).subHour(1);
        
        if (_invader.getAvailableTime(begin, end, &available) == SATERROR_OK) {
            for (i = 0; i < available.size(); ++i) {
                if (_invader.getSensorTemperatureSolarPX(available[i], &value) == SATERROR_OK) {
                    cout << "the temperature of solar panel +X is " << value << " degC." << endl;
                }
            }
        }
        return;
    }

    void testApp::onNotifyTLE(ofxSAT::TLERec const& tle, ofxSATTime const& time)
    {
        ofxSAT::Notifier::onNotifyTLE(tle, time);
        
        cout << "new TLE received." << endl;
        return;
    }

    void testApp::onNotifyData(ofxSATTime const& time)
    {
        ofxSAT::Notifier::onNotifyData(time);
        
        cout << "new telemetry data received." << endl;
        return;
    }
    @endcode
 
    @par ライセンス
    ARTSAT API のソースコードとバイナリは下記に示す MIT ライセンスの元で配布されます。
    ARTSAT API を通して取得できるデータのライセンスに関してはデータの提供元となる各衛星の定めるライセンスに準じます。
    特に INVADER 衛星から得られるデータに関しては商用での利用を禁止します。
    @par
    The MIT License (MIT)
    @par
    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
    associated documentation files (the "Software"), to deal in the Software without restriction,
    including without limitation the rights to use, copy, modify, merge, publish, distribute,
    sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    The above copyright notice and this permission notice shall be included in all copies or
    substantial portions of the Software.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
    BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    @par
    以下に定める条件に従い、本ソフトウェアおよび関連文書のファイル（以下「ソフトウェア」）の複製を
    取得するすべての人に対し、ソフトウェアを無制限に扱うことを無償で許可します。
    これには、ソフトウェアの複製を使用、複写、変更、結合、掲載、頒布、サブライセンス、および、または販売する権利、
    およびソフトウェアを提供する相手に同じことを許可する権利も無制限に含まれます。
    上記の著作権表示および本許諾表示を、ソフトウェアのすべての複製または重要な部分に記載するものとします。
    ソフトウェアは「現状のまま」で、明示であるか暗黙であるかを問わず、何らの保証もなく提供されます。
    ここでいう保証とは、商品性、特定の目的への適合性、および権利非侵害についての保証も含みますが、それに限定されるものではありません。
    作者または著作権者は、契約行為、不法行為、またはそれ以外であろうと、ソフトウェアに起因または関連し、
    あるいはソフトウェアの使用またはその他の扱いによって生じる一切の請求、損害、その他の義務について何らの責任も負わないものとします。
 
    @par 謝辞
    ARTSAT API は SQLite3 をローカルデータベースとして使用しますが、
    SQLite3 を扱うアドオンである Diederick Huijbers 氏作の ofxSQLite を内部で使用しています。
 
    @par バージョン履歴
    - version 2.7.1
        -# ofxAddons の方針に従ってプロジェクトのディレクトリ構成を再構築
        -# ofxSAT クラスの単位定数のうち、RAD, DEG を含む単位名を rad, deg に変更
        -# ofxSAT クラスの単位定数のうち、_S, _SS を含む単位名を _s, _ss に変更
        -# ofxSAT クラスの単位定数に UNIT_UNDEFINED を追加
    - version 2.7.0
        -# 初期公開バージョン
 
    @author HORIGUCHI Junshi (zap00365@nifty.com)
 */

#endif
