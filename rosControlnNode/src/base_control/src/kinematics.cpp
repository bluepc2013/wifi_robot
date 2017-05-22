/**
 * File: kinematics.cpp
 * Brief:
 * Created by: zhangping
 * Created at: 2017.05.14
 * Modified by:
 * Modified at:
 **/

#include "kinematics.h"

Kinematics::Kinematics(float64 l):l_(l){
}

Kinematics::~Kinematics(){
}

bool Kinematics::DiffDriveK(const float64 kT, const float64 kW, 
		float64 &vel_l, float64 &vel_r)
{
	// Input investigation
	// ...

	// Do work
	vel_l = (kT + kW*l_);
	vel_r = (kT - kW*l_);
	
	return true;
}


