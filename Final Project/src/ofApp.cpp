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
    ball->isFixed();
    ball->setup(box2d.getWorld(), (ofGetWidth()/6), ofGetHeight()/2, r);
    ball->enableGravity(false);
    shot = false;
    balls.push_back(ball);

}

//--------------------------------------------------------------
void ofApp::update() {
    box2d.update();
    
    if(shot) {
        for(auto &ball : balls) {
            if(ball->getVelocity().y == 0) {
                to_destroy.push_back(ball);
                balls.pop_back();
            }
        }

        for(auto &object : to_destroy) {
            object->destroy();
            to_destroy.pop_back();
            shot = false;
        }
    }
    
}


//--------------------------------------------------------------
void ofApp::draw() {
    
    
    for(auto &ball : balls) {
        ofFill();
        ofSetHexColor(0xffa500);
        ball->draw();
    }
    
    // draw the ground
    box2d.drawGround();
    
    string info = "";
    info += "Hold [space] to increase power\n";
    info += "Let go of [space] to shoot\n";
    info += "Score: "+ofToString(score)+"\n";
    info += "Total Joints: "+ofToString(box2d.getJointCount())+"\n\n";
    info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
    ofSetHexColor(0x444342);
    ofDrawBitmapString(info, 30, 30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    
    if(key == 'c') {
        float r = ofRandom(14, 20);
        auto ball = make_shared<ofxBox2dCircle>();
        ball->setPhysics(3.0, 0.53, 0.9);
        ball->setup(box2d.getWorld(), mouseX, mouseY, r);
        balls.push_back(ball);
        
        shapes.push_back(ball);
    }
    
    if(key == 'b') {
        float w = ofRandom(14, 20);
        float h = ofRandom(14, 20);
        auto rect = make_shared<ofxBox2dRect>();
        rect->setPhysics(3.0, 0.53, 0.9);
        rect->setup(box2d.getWorld(), mouseX, mouseY, w, h);
        boxes.push_back(rect);
        
        shapes.push_back(rect);
    }
    
    if(key == 't') ofToggleFullscreen();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    if(key == ' ') {
        for(auto &ball : balls) {
            ball->enableGravity(true);
            shot = true;
            ofVec2f direction = ofVec2f(1,-1);
            ball->addForce(direction,1000);
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
