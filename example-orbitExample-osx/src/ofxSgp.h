//
//  ofxSgp.h
//
//
//  Created by mori koichiro on 11/10/13.
//

#include "ofMain.h"
#include "ofxSATTime.h"

extern "C" {
#include "sgp4sdp4.h"
}

class ofxSgp {
    
public:
    ofxSgp();
    ~ofxSgp();
    
    void setup(const char * tleFilePath);
    void update(ofxSATTime const* time);
    
    ofVec3f getPos() const;
    ofVec3f getVelocity() const;
    
    double getSatLatitude() const;
    double getSatLongitude() const;
    double getSatAlt() const;
    
private:
    const char *tle_file;
    geodetic_t obs_geodetic;
    tle_t tle;
    vector_t zero_vector;
    vector_t vel;
    vector_t pos;
    vector_t obs_set;
    vector_t solar_vector;
    vector_t solar_set;
    struct tm utc;
    geodetic_t sat_geodetic;
    double
    tsince,            /* Time since epoch (in minutes) */
    jul_epoch,         /* Julian date of epoch          */
    jul_utc,           /* Julian UTC date               */
    eclipse_depth,     /* Depth of satellite eclipse    */
    /* Satellite's observed position, range, range rate */
    sat_azi, sat_ele, sat_range, sat_range_rate,
    /* Satellites geodetic position and velocity */
    sat_lat, sat_lon, sat_alt, sat_vel,
    /* Solar azimuth and elevation */
    sun_azi, sun_ele;
    
    int flg;
    char
    ephem[5],       /* Ephemeris in use string  */
    sat_status[12]; /* Satellite eclipse status */
};
