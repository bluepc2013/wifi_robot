/**
 * File: wheelControl.h
 * Brief:
 * Created by: zhangping
 * Created at: 2017.05.14
 * Modified by:
 * Modified at:
 **/

#ifndef _MY_WHEELCONTROL_H_
#define _MY_WHEELCONTROL_H_

typedef float float64;

/*
 * Class: WheelControl
 * Brief: 这里一个开环控速。输入是车轮速度，输出是电机PWM占空比。速度与pwm波形的比
 * 		例可能不是简单的线性映射，但暂时简化成线性映射。
 */
class WheelControl{
  public:
    WheelControl(float64 r);
    ~WheelControl();
    /*
     * Funcion: transform
     * Brief: transform velocity to PWM ratio.
     * Args:
     * 		vel: wheel velocities.
     * Return: PWM ratio.
     */
    float64 Transform(const float64 kVel);
		
  private:
	float64 r_; // radius of the wheel.
	float64 k_; // coefficient.
};

#endif



