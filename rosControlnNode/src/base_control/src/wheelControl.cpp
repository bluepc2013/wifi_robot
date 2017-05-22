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

#define MAX_VELOCITY 2   // unit is "m/s"
#define MIN_VELOCITY 0
#define VELOCITY_K   1   // coefficient

#define ABS(x) (x)>0?(x):(-(x));

WheelControl::WheelControl(float64 r):r_(r){
	this->k_ = VELOCITY_K;
}

WheelControl::~WheelControl(){

}

float64 WheelControl::Transform(const float64 kVel){
	// Input investigation
	//assert(kVel>MIN_VELOCITY);
	//assert(kVel<MAX_VELOCITY);
	
	// Do work
	float kVel_abs = ABS(kVel);
	float PWM_ratio = k_*((kVel_abs-MIN_VELOCITY)/(MAX_VELOCITY-MIN_VELOCITY));

	return kVel>0?PWM_ratio:-PWM_ratio;
}
