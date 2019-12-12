//
//  app-tests.cpp
//  Final Project Tests
//
//  Created by Gene Wang on 12/11/19.
//

#include <stdio.h>

#include "catch.hpp"
#include "ofApp.h"

TEST_CASE("Test Setup Score") {
    ofApp *testApp = new ofApp();
    testApp->initializeVariables();
    REQUIRE(testApp->score == 0);
}

TEST_CASE("Test Setup Level") {
    ofApp *testApp = new ofApp();
    testApp->initializeVariables();
    REQUIRE(testApp->level == 1);
}

TEST_CASE("Test Setup Moving") {
    ofApp *testApp = new ofApp();
    testApp->initializeVariables();
    REQUIRE(testApp->moving == -1);
}

TEST_CASE("Test Setup Scored") {
    ofApp *testApp = new ofApp();
    testApp->initializeVariables();
    REQUIRE(!(testApp->scored));
}

TEST_CASE("Test Setup Shot") {
    ofApp *testApp = new ofApp();
    testApp->initializeVariables();
    REQUIRE(!(testApp->shot));
}

TEST_CASE("Test Setup Counted") {
    ofApp *testApp = new ofApp();
    testApp->initializeVariables();
    REQUIRE(!(testApp->counted));
}

TEST_CASE("Test Setup Shots") {
    ofApp *testApp = new ofApp();
    testApp->initializeVariables();
    REQUIRE(testApp->shots == 0);
}

TEST_CASE("Test Setup Previous") {
    ofApp *testApp = new ofApp();
    testApp->initializeVariables();
    REQUIRE(testApp->prev == -1);
}

TEST_CASE("Test Setup HighScore") {
    ofApp *testApp = new ofApp();
    testApp->initializeVariables();
    REQUIRE(testApp->high_score == 0);
}

TEST_CASE("Test Setup Level 1") {
    ofApp *testApp = new ofApp();
    testApp->initializeVariables();
    testApp->setLevel();
    REQUIRE(testApp->level==1);
}

TEST_CASE("Test Setup Level 2") {
    ofApp *testApp = new ofApp();
    testApp->initializeVariables();
    testApp->score = to_level_up;
    testApp->setLevel();
    REQUIRE(testApp->level==2);
}

TEST_CASE("Test Setup Level 3") {
    ofApp *testApp = new ofApp();
    testApp->initializeVariables();
    testApp->score = 2*to_level_up;
    testApp->setLevel();
    REQUIRE(testApp->level==3);
}

