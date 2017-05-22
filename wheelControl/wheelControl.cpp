/**
 * File: wheelControl.cpp
 * Brief:
 * Created by: zhangping
 * Created at: 2017.05.14
 * Modified by:
 * Modified at:
 **/

#include "wheelControl.h"
#include "assert.h"

#define MAX_VELOCITY 0.6 // unit is "m/s"
#define MIN_VELOCITY 0.1
#define VELOCITY_K   1   // coefficient

WheelControl::WheelControl(float64 r):r_(r){
	this->k_ = VELOCITY_K;
}

WheelControl::~WheelControl(){

}

float64 WheelControl::Transform(const float64 kVel){
	// Input investigation
	assert(kVel>MIN_VELOCITY);
	assert(kVel<MAX_VELOCITY);
	
	// Do work
	return k_*((kVel-MIN_VELOCITY)/(MAX_VELOCITY-MIN_VELOCITY));
}



