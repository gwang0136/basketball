#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "globals.h"
#include "ofxProgressBar.h"

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
    void setLevel();
    void initializeVariables();
    
    int shots;
    int prev;
    int high_score;
    int score;
    int power;
    int level;
    int moving;
    
    bool shot;
    bool space_held;
    bool scored;
    bool counted;
    
    ofxBox2d box2d;
    vector   <shared_ptr<ofxBox2dCircle>> balls;
    vector   <shared_ptr<ofxBox2dCircle>> to_destroy;
    vector   <shared_ptr<ofxBox2dRect>>   backboards;
    vector   <shared_ptr<ofxBox2dRect>>   rims;
    
    ofxProgressBar progressBar;
    void createProgressBar();
};
