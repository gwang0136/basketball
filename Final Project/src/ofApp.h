#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "globals.h"

class ofApp : public ofBaseApp {
    
public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    
    void createBall();
    void reload();
    void checkIfScore();
    void setRims();
    void setBackboard();
    
    ofxBox2d box2d;
    vector   <shared_ptr<ofxBox2dCircle>> balls;
    vector   <shared_ptr<ofxBox2dCircle>> to_destroy;
    vector   <shared_ptr<ofxBox2dRect>>   backboards;
    vector   <shared_ptr<ofxBox2dRect>>   rims;
    
    int score;
    bool shot;
    bool space_held;
    int power;
    bool scored;
    int level;
    int moving;
    bool counted;
    int shots;
    int prev;
};
