#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxARTSATAPI.h"
#include "ofxSgp.h"

class SATOrbit : private ofxSAT::Notifier {
    private:
        ofxSAT* _sat;
        ofxSgp _sgp;
        ofVec3f _position;
        ofMesh _orbit;
        string _name;
        ofColor _colorSat;
        ofColor _colorOrbit;
    
    public:
        virtual ~SATOrbit(void);
        float getLat(void) const;
        float getLon(void) const;
        float getAlt(void) const;
        ofVec3f const& getPosition(void) const;
        string const& getName(void) const;
        void setColorSat(ofColor const& color);
        ofColor const& getColorSat(void) const;
        ofColor const& getColorOrbit(void) const;
        void update(ofxSATTime const& time);
        void draw(void);
    protected:
        explicit SATOrbit(ofxSAT* sat, string const& name, ofColor const& color);
        ofxSAT* getSAT(void) const;
    private:
        virtual void onNotifyTLE(ofxSAT::TLERec const& tle, ofxSATTime const& time);
        virtual void onNotifyData(ofxSATTime const& time);
        virtual void onNotifyFinish(ofxSATError const& error);
};

class InvaderOrbit : public SATOrbit {
    public:
        explicit InvaderOrbit(void);
        virtual ~InvaderOrbit(void);
};

class testApp : public ofxiPhoneApp {
    private:
        ofxSATTime _epoch;
        ofxSATTime _current;
        vector<SATOrbit*> _sat;
        bool _lock;
        ofVec3f _earthPos;
        ofImage _earthTexture;
        ofCamera _camera;
        float _distance;
        ofQuaternion _rotation;
        ofVec2f _mouse;
        bool _double;
    
    public:
        void setup(void);
        void exit(void);
        void update(void);
        void draw(void);
    
        void touchDown(ofTouchEventArgs& touch);
        void touchMoved(ofTouchEventArgs& touch);
        void touchUp(ofTouchEventArgs& touch);
        void touchDoubleTap(ofTouchEventArgs& touch);
        void touchCancelled(ofTouchEventArgs& touch);
        void lostFocus(void);
        void gotFocus(void);
        void gotMemoryWarning(void);
        void deviceOrientationChanged(int newOrientation);
};
