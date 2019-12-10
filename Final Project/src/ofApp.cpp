#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup() {
    score = 0;
    ofSetVerticalSync(true);
    ofBackgroundHex(0xfdefc2);
    ofSetLogLevel(OF_LOG_NOTICE);
    ofDisableAntiAliasing();
    
    box2d.init();
    box2d.setGravity(0, 10);
    box2d.setFPS(60.0);
    box2d.createGround();
        
        
    float r = 15;
    auto ball = make_shared<ofxBox2dCircle>();
    ball->setPhysics(3.0, 0.53, 0.9);
    ball->setup(box2d.getWorld(), (ofGetWidth()/6), ofGetHeight()/2, r);
    ball->enableGravity(false);
    shot = false;
    power = 0;
    balls.push_back(ball);
    
    
    auto hoop = make_shared<ofxBox2dRect>();
    hoop->setPhysics(0.0, 0.53, 0.9);
    hoop->setup(box2d.getWorld(), 2*(ofGetWidth()/6)+105,(ofGetHeight()/4)-60, 10, 150);
    hoop->enableGravity(false);
    
    boxes.push_back(hoop);
}

//--------------------------------------------------------------
void ofApp::update() {
    box2d.update();
    
    if(shot) {
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
            
        }
        
        if(balls.empty()) {
            auto new_ball = make_shared<ofxBox2dCircle>();
            new_ball->setPhysics(3.0, 0.53, 0.9);
            new_ball->isFixed();
            new_ball->setup(box2d.getWorld(), (ofGetWidth()/6), ofGetHeight()/2, 15);
            new_ball->enableGravity(false);
            balls.push_back(new_ball);
        }
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
    ofSetHexColor(0xff0000);
    ofDrawRectangle(2*(ofGetWidth()/6),ofGetHeight()/4, 100, 5);
    ofSetHexColor(0xffffff);
    //ofDrawRectangle(2*(ofGetWidth()/6)+100,(ofGetHeight()/4)-120, 10, 150);
    // draw the ground
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
void ofApp::mouseMoved(int x, int y ) {
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::resized(int w, int h){
}
