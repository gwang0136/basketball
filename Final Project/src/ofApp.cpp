#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    score = 0;
    level = 1;                      // start on easy
    moving = -1;                    // when reaching hard level, rim will move left first
    scored = false;
    ofSetVerticalSync(true);
    ofBackgroundHex(0xfdefc2);
    ofSetLogLevel(OF_LOG_NOTICE);
    ofDisableAntiAliasing();
    
    box2d.init();
    box2d.setGravity(0, 10);
    box2d.setFPS(60.0);
    box2d.createGround();
        
    createBall();
    
    
    auto hoop = make_shared<ofxBox2dRect>();
    hoop->setPhysics(0.0, 0.53, 0.9);
    hoop->setup(box2d.getWorld(), 2*(ofGetWidth()/6)+105,(ofGetHeight()/4)-60, 10, 150);
    hoop->enableGravity(false);
    
    boxes.push_back(hoop);
}

//--------------------------------------------------------------
void ofApp::update() {
    box2d.update();
    
    checkIfScore();
    
    if(scored) {
        score++;
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
    for(auto &hoop : boxes) {
        ofFill();
        ofSetHexColor(0xffffff);
        hoop->draw();
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
    info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
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
        rims.at(1)->setPosition(2*(ofGetWidth()/6)+rim_size,(ofGetHeight()/2));
    }
    else if(level == 2) { // medium difficulty
        rims.at(0)->setPosition(4*(ofGetWidth()/6), (ofGetHeight()/2));
        rims.at(1)->setPosition(4*(ofGetWidth()/6)+rim_size,(ofGetHeight()/2));
    }
    else if(level == 3) { // hard difficulty
        if(rims.at(0)->getPosition() == ofVec2f(4*(ofGetWidth()/6)+1,(ofGetHeight()/2)) ||
           rims.at(0)->getPosition() == ofVec2f(2*(ofGetWidth()/6),(ofGetHeight()/2)))
        {
            moving *= -1;
        }
        else {
            rims.at(0)->setPosition(rims.at(0)->getPosition().x + moving,                                     rims.at(0)->getPosition().y);
            rims.at(1)->setPosition(rims.at(1)->getPosition().x + moving,                                     rims.at(1)->getPosition().y);
        }
    }
}

//--------------------------------------------------------------
void ofApp::reload() {
    for(auto &ball : balls) {
        if(ball->getVelocity().y == 0 ||
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
            level = 0;
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
         ball->getPosition().y == rims.at(0)->getPosition().y)
     {
         scored = true;
     }
    }
}
