#include "testApp.h"

#define TIME_SCALE          (120)
#define SAT_SIZE            (150)
#define EARTH_SIZE          (6378)
#define DISTANCE_DEFAULT    (30000)
#define DISTANCE_MIN        (6500)
#define DISTANCE_MAX        (40000)
#define DISTANCE_STEP       (250)

void testApp::setup(void)
{
    ofSetFrameRate(60);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofEnableNormalizedTexCoords();
    ofBackground(0, 0, 0);
    
    _epoch = ofxSATTime::currentTime();
    _current = _epoch;
    
    _sat.push_back(new InvaderOrbit);
    _lock = false;
    
    _earthPos.set(0, 0, 0);
    _earthTexture.loadImage("earth.jpg");
    
    _distance = DISTANCE_DEFAULT;
    _camera.setPosition(_earthPos.x, _earthPos.y, _distance);
    _camera.lookAt(_earthPos);
    _camera.setFov(45);
    _camera.setNearClip(100);
    _camera.setFarClip(50000);
    _mouse.set(ofGetMouseX(), ofGetMouseY());
    return;
}

void testApp::exit(void)
{
    int i;
    
    for (i = 0; i < _sat.size(); ++i) {
        if (_sat[i] != NULL) {
            delete _sat[i];
        }
    }
    _sat.clear();
    return;
}

void testApp::update(void)
{
    ofVec3f posX;
    ofVec3f posY;
    float minimum;
    float temp;
    int x;
    int y;
    int i;
    int j;
    
    _current = _epoch + ofxSATTimeDiff(ofGetElapsedTimef() * TIME_SCALE);
    for (i = 0; i < _sat.size(); ++i) {
        if (_sat[i] != NULL) {
            _sat[i]->update(_current);
            _sat[i]->setColorSat(ofColor(255, 255, 255));
        }
    }
    _lock = false;
    _camera.setPosition(_earthPos.x, _earthPos.y, _distance);
    _camera.lookAt(_earthPos);
    
    minimum = FLT_MAX;
    x = -1;
    y = -1;
    for (i = 0; i < _sat.size(); ++i) {
        posX = _sat[i]->getPosition();
        for (j = i + 1; j < _sat.size(); ++j) {
            posY = _sat[j]->getPosition();
            if ((temp = posX.distance(posY)) < minimum) {
                minimum = temp;
                x = i;
                y = j;
            }
        }
    }
    if (x >= 0 && y >= 0) {
        if (minimum < 4000) {
            if (static_cast<int>(ofGetElapsedTimef() * 10) / 2 % 2 == 0) {
                _sat[x]->setColorSat(ofColor(255, 0, 0));
                _sat[y]->setColorSat(ofColor(255, 0, 0));
            }
        }
        if (minimum < 3000) {
            _lock = true;
            _camera.setPosition(_sat[x]->getPosition() * 1.5);
            _camera.lookAt(_sat[y]->getPosition());
        }
    }
    return;
}

void testApp::draw(void)
{
    float angle;
    ofVec3f axis;
    int offset;
    int i;
    
    _rotation.getRotate(angle, axis);
    glEnable(GL_DEPTH_TEST);
    _camera.begin();
    ofPushMatrix();
    if (!_lock) {
        ofRotate(angle, axis.x, axis.y, axis.z);
        ofRotateY(_current.getTime(NULL) / 86400.0 * 360.0);
    }
    ofPushMatrix();
    ofRotateX(180);
    ofRotateY(90);
    _earthTexture.bind();
    ofFill();
    ofSetColor(255, 255, 255);
    ofSphere(_earthPos, EARTH_SIZE);
    _earthTexture.unbind();
    ofPopMatrix();
    
    for (i = 0; i < _sat.size(); ++i) {
        if (_sat[i] != NULL) {
            _sat[i]->draw();
        }
    }
    ofPopMatrix();
    _camera.end();
    glDisable(GL_DEPTH_TEST);
    
    ofSetColor(255, 255, 255);
    offset = 15;
    ofDrawBitmapString(_current.format("%YYYY/%MM/%DD %hh:%mm:%ss") + " (*" + ofToString(TIME_SCALE, 1) + ")", 6, offset);
    for (i = 0; i < _sat.size(); ++i) {
        if (_sat[i] != NULL) {
            offset += 30;
            ofSetColor(_sat[i]->getColorOrbit());
            ofDrawBitmapString(_sat[i]->getName(), 6, offset);
            ofSetColor(255, 255, 255);
            offset += 15;
            ofDrawBitmapString("lat: " + ofToString(_sat[i]->getLat(), 4), 6, offset);
            offset += 15;
            ofDrawBitmapString("lon: " + ofToString(_sat[i]->getLon(), 4), 6, offset);
            offset += 15;
            ofDrawBitmapString("alt: " + ofToString(_sat[i]->getAlt(), 4), 6, offset);
        }
    }
    return;
}

void testApp::keyPressed(int key)
{
    switch (key) {
        case OF_KEY_UP:
            if (_distance > DISTANCE_MIN) {
                _distance -= DISTANCE_STEP;
            }
            break;
        case OF_KEY_DOWN:
            if (_distance < DISTANCE_MAX) {
                _distance += DISTANCE_STEP;
            }
            break;
        default:
            break;
    }
    return;
}

void testApp::keyReleased(int key)
{
    return;
}

void testApp::mouseMoved(int x, int y)
{
    return;
}

void testApp::mouseDragged(int x, int y, int button)
{
    ofQuaternion xRot;
    ofQuaternion yRot;
    
    xRot.makeRotate((y - _mouse.y) * 0.4, 1, 0, 0);
    yRot.makeRotate((x - _mouse.x) * 0.4, 0, 1, 0);
    _rotation *= xRot * yRot;
    _mouse.set(x, y);
    return;
}

void testApp::mousePressed(int x, int y, int button)
{
    _mouse.set(x, y);
    return;
}

void testApp::mouseReleased(int x, int y, int button)
{
    return;
}

void testApp::windowResized(int w, int h)
{
    return;
}

void testApp::gotMessage(ofMessage msg)
{
    return;
}

void testApp::dragEvent(ofDragInfo dragInfo)
{
    return;
}

SATOrbit::SATOrbit(ofxSAT* sat, string const& name, ofColor const& color) : _sat(sat)
{
    if (_sat != NULL) {
        _sat->setNotifier(this);
        _sat->setup();
        
        _position.set(0, 0, 0);
        _orbit.clear();
        _orbit.setMode(OF_PRIMITIVE_LINE_STRIP);
        _name = name;
        _colorSat.set(255, 255, 255);
        _colorOrbit = color;
    }
}

SATOrbit::~SATOrbit(void)
{
    if (_sat != NULL) {
        _sat->cleanup();
        delete _sat;
    }
}

float SATOrbit::getLat(void) const
{
    float result(0.0);
    
    if (_sat != NULL) {
        result = _sgp.getSatLatitude();
    }
    return result;
}

float SATOrbit::getLon(void) const
{
    float result(0.0);
    
    if (_sat != NULL) {
        result = _sgp.getSatLongitude();
    }
    return result;
}

float SATOrbit::getAlt(void) const
{
    float result(0.0);
    
    if (_sat != NULL) {
        result = _sgp.getSatAlt();
    }
    return result;
}

ofVec3f const& SATOrbit::getPosition(void) const
{
    return _position;
}

string const& SATOrbit::getName(void) const
{
    return _name;
}

void SATOrbit::setColorSat(ofColor const& color)
{
    _colorSat = color;
    return;
}

ofColor const& SATOrbit::getColorSat(void) const
{
    return _colorSat;
}

ofColor const& SATOrbit::getColorOrbit(void) const
{
    return _colorOrbit;
}

void SATOrbit::update(ofxSATTime const& time)
{
    ofQuaternion latRot;
    ofQuaternion lonRot;
    
    if (_sat != NULL) {
        _sgp.update(&time);
        _position.set(0, 0, _sgp.getSatAlt() + EARTH_SIZE);
        latRot.makeRotate(-_sgp.getSatLatitude(), 1, 0, 0);
        lonRot.makeRotate(_sgp.getSatLongitude(), 0, 1, 0);
        _position = latRot * lonRot * _position;
        _orbit.addVertex(_position);
        _orbit.addColor(_colorOrbit);
    }
    return;
}

void SATOrbit::draw(void)
{
    if (_sat != NULL) {
        ofPushMatrix();
        ofTranslate(_position);
        ofFill();
        ofSetColor(_colorSat);
        ofBox(0, 0, 0, SAT_SIZE);
        ofPopMatrix();
        
        ofSetLineWidth(1);
        _orbit.draw();
    }
    return;
}

ofxSAT* SATOrbit::getSAT(void) const
{
    return _sat;
}

void SATOrbit::onNotifyTLE(ofxSAT::TLERec const& tle, ofxSATTime const& time)
{
    string name;
    string path;
    ofstream file;
    
    name = _sat->getID();
    ofStringReplace(name, "://", "");
#if TARGET_OS_IPHONE
    path = ofToDataPath("");
    path = ofFilePath::join(ofFilePath::getEnclosingDirectory(path), "Library");
    path = ofFilePath::join(path, name + ".txt");
#else
    path = ofToDataPath(name + ".txt");
#endif
    file.open(path.c_str());
    if (file.is_open()) {
        file << name << endl;
        file << tle.line[0] << endl;
        file << tle.line[1] << endl;
        file.close();
        _sgp.setup(path.c_str());
        _orbit.clear();
    }
    return;
}

void SATOrbit::onNotifyData(ofxSATTime const& time)
{
    ofxSAT::Notifier::onNotifyData(time);
    return;
}

void SATOrbit::onNotifyFinish(ofxSATError const& error)
{
    ofxSAT::Notifier::onNotifyFinish(error);
    
    ofxSATTime time = ofxSATTime::currentTime();
    int c;
    vector<ofxSATTime> t;
    
    double r = 0.0;
    bool sim = true;
    
    static_cast<ofxInvaderSAT*>(_sat)->getSensorGyroX(time, &r, &sim);
    cout << "gyroX = " << r << endl;
    
    //_sat->getAvailableCount(ofxSATTime(time).subHour(1), time, &c);
    //_sat->getAvailableTime(ofxSATTime(time).subHour(1), time, &t);
    //cout << "c = " << c << endl;
    //cout << "t = " << t.size() << endl;
    return;
}

InvaderOrbit::InvaderOrbit(void) : SATOrbit(new ofxInvaderSAT, "INVADER", ofColor(255, 255, 255))
{
}

InvaderOrbit::~InvaderOrbit(void)
{
}
