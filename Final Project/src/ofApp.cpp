#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    score = 0;
    level = 2;                      // start on easy
    moving = -1;                    // when reaching hard level, rim will move left first
    scored = false;
    shot = false;
    counted = false;
    shots = 0;
    prev = -1;
    ofSetVerticalSync(true);
    ofBackgroundHex(0xfdefc2);
    ofSetLogLevel(OF_LOG_NOTICE);
    ofDisableAntiAliasing();
    
    box2d.init();
    box2d.setGravity(0, 10);
    box2d.setFPS(60.0);
    box2d.createGround();
        
    createBall();
    setRims();
    setBackboard();
}

//--------------------------------------------------------------
void ofApp::update() {
    box2d.update();
    setRims();
    setBackboard();
    checkIfScore();
    
    if(scored) {
        if(!counted) {
            score++;
            counted = true;
        }
    }
    
    if(shot) {
        reload();
    }

    if(space_held) {
        power+=25;
    }
    
}


//--------------------------------------------------------------
void ofApp::draw() {
    
    for(auto &ball : balls) {
        ofFill();
        ofSetHexColor(0xffa500);
        ball->draw();
    }
    for(auto &backboard : backboards) {
        ofFill();
        ofSetHexColor(0xffffff);
        backboard->draw();
    }
    
    for(auto &rim : rims) {
        ofFill();
        ofSetHexColor(0xff0000);
        rim->draw();
    }
    
    ofDrawRectangle(rims.at(0)->getPosition().x + rim_size/2,
                    rims.at(1)->getPosition().y - rim_size/2, hoop_length, hoop_width);
    
    ofSetHexColor(0xffffff);
    box2d.drawGround();
    
    string info = "";
    info += "Hold [space] to increase power\n";
    info += "Let go of [space] to shoot\n";
    info += "Score: "+ofToString(score)+"\n";
    info += "Level: "+ofToString(level)+"\n";
    ofSetHexColor(0x444342);
    ofDrawBitmapString(info, 30, 30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    
    if(key == 't') ofToggleFullscreen();
    
    if(key == ' ') {
        if(!shot) {
            space_held = true;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    if(key == ' ') {
        if(!shot) {
            space_held = false;
            for(auto &ball : balls) {
                ball->enableGravity(true);
                shot = true;
                shots++;
                ofVec2f direction = ofVec2f(1,-1);
                ball->addForce(direction,power);
            }
            power = 0;
        }
    }
}

//--------------------------------------------------------------
void ofApp::createBall() {
    auto ball = make_shared<ofxBox2dCircle>();
    ball->setPhysics(3.0, 0.53, 0.9);
    ball->setup(box2d.getWorld(), (ofGetWidth()/6), ofGetHeight()/2, ball_size);
    ball->enableGravity(false);
    balls.push_back(ball);
}

void ofApp::setRims() {
    if(rims.empty()) {
        auto front_rim = make_shared<ofxBox2dRect>();
        front_rim->setPhysics(0.0, 0.53, 0.9);
        front_rim->setup(box2d.getWorld(), 2*(ofGetWidth()/6),(ofGetHeight()/2), rim_size, rim_size);
        front_rim->enableGravity(false);
        rims.push_back(front_rim);
        
        auto back_rim = make_shared<ofxBox2dRect>();
        back_rim->setPhysics(0.0, 0.53, 0.9);
        back_rim->setup(box2d.getWorld(), 2*(ofGetWidth()/6)+rim_size + hoop_length,(ofGetHeight()/2), rim_size, rim_size);
        back_rim->enableGravity(false);
        rims.push_back(back_rim);
    }
    else if(level == 1) { // easy difficulty
        rims.at(0)->setPosition(2*(ofGetWidth()/6), (ofGetHeight()/2));
        rims.at(1)->setPosition(2*(ofGetWidth()/6)+hoop_length,(ofGetHeight()/2));
    }
    else if(level == 2) { // medium difficulty
        rims.at(0)->setPosition(4*(ofGetWidth()/6), (ofGetHeight()/2));
        rims.at(1)->setPosition(4*(ofGetWidth()/6)+hoop_length,(ofGetHeight()/2));
    }
    else if(level == 3) { // hard difficulty
        if(rims.at(0)->getPosition().x >= 4*(ofGetWidth()/6) ||
           rims.at(0)->getPosition().x <= 2*(ofGetWidth()/6))
        {
            moving *= -1;
        }
        rims.at(0)->setPosition(rims.at(0)->getPosition().x + moving*threshold,                                     rims.at(0)->getPosition().y);
        rims.at(1)->setPosition(rims.at(1)->getPosition().x + moving*threshold,                                     rims.at(1)->getPosition().y);
    }
}

void ofApp::setBackboard() {
    if(backboards.empty()) {
        auto backboard = make_shared<ofxBox2dRect>();
        backboard->setPhysics(0.0, 0.53, 0.4);
        backboard->setup(box2d.getWorld(),
                         rims.at(0)->getPosition().x + rim_size/2 + backboard_offset_x,
                         rims.at(0)->getPosition().y + rim_size/2 + backboard_offset_y,
                         backboard_width, backboard_height);
        backboard->enableGravity(false);
        backboards.push_back(backboard);
    }
    else {
        for(auto &backboard : backboards)
        {
            backboard->setPosition(rims.at(0)->getPosition().x + rim_size/2 + backboard_offset_x,rims.at(0)->getPosition().y + rim_size/2 + backboard_offset_y);
        }
    }
        
}

//--------------------------------------------------------------
void ofApp::reload() {
    for(auto &ball : balls) {
        if(ball->getPosition().y >= 19*ofGetHeight()/20 ||
           ofxBox2dBaseShape::shouldRemoveOffScreen(ball)) {
            to_destroy.push_back(ball);
            balls.pop_back();
        }
    }

    for(auto &object : to_destroy) {
        object->destroy();
        to_destroy.pop_back();
        shot = false;
        
        if(!scored) {
            score = 0;
            level = 2;
        }
        else {
            scored = !scored;
        }
    }
    
    if(balls.empty()) {
        createBall();
    }
}

void ofApp::checkIfScore() {
    for(auto &ball : balls) {
     if (ball->getPosition().x >= rims.at(0)->getPosition().x &&
         ball->getPosition().x <= rims.at(1)->getPosition().x &&
         ball->getPosition().y >= rims.at(0)->getPosition().y - threshold &&
         ball->getPosition().y <= rims.at(0)->getPosition().y + threshold)
     {
         if(shots != prev){
             scored = true;
             counted = false;
             prev = shots;
         }
     }
    }
}
