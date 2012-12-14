#pragma once

#include "ofMain.h"
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

class testApp : public ofBaseApp {
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
    
    public:
        void setup(void);
        void exit(void);
        void update(void);
        void draw(void);
        
        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y);
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
};
