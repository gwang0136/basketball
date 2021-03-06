//
//  globals.h
//  Final Project
//
//  Created by Gene Wang on 12/10/19.
//

#ifndef globals_h
#define globals_h

#include "ofMain.h"
#include "ofxBox2d.h"

/*Sizes of Objects*/
const int ball_size = 15;
const int hoop_length = 50;
const int hoop_width = 10;
const int rim_size = 10;
const int backboard_width = 10;
const int backboard_height = 150;
const int backboard_offset_x = 55;
const int backboard_offset_y = -60;
const int stanchion_width = 15;
const int stanchion_height = 400;
const int stanchion_offset_y = 200;
const int support_width = 20;
const int support_height = 10;

/*Score Threshold*/
const int threshold = 10;

/*Level 3 Basket Move Speed*/
const int speed = 5;

/*Level Up Threshold*/
const int to_level_up = 3;

#endif /* globals_h */
