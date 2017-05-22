#include <iostream>
#include <stdlib.h>
#include <string>
#include "kinematics.h"

int main(){
	// Create a kinematic model
	Kinematics ki(0.05);
	
	// Begin transform
	float64 vel_l;
	float64 vel_r;
	if (!ki.DiffDriveK(0.5, 0.3, vel_l, vel_r)){
		std::cerr<<"Error:failed to transform."<<std::endl;
		exit(-1);
	}
    std::cout<<"r=0.02m , l=0.05m > "
			<<"vel_l="<<vel_l
			<<"vel_r="<<vel_r
			<<std::endl;
			
	return 0;
}
