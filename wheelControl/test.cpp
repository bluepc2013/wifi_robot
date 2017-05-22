#include <iostream>
#include <stdlib.h>
#include <string>
#include "wheelControl.h"

int main(){
	// Create a wheelControl model
	WheelControl wc_l(0.02);
	WheelControl wc_r(0.02);

	// Begin transform
	float64 pwm_l = wc_l.Transform(0.4);
	float64 pwm_r = wc_l.Transform(0.3);
	//float64 pwm_r = wc_l.Transform(0.03); // Error Test
    std::cout<<"left wheel: vel=0.4 --> pwm_l="<<pwm_l
			<<"\nright wheel: vel=0.3 --> pwm_r="<<pwm_r
			<<std::endl;

	return 0;
}
