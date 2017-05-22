/**
 * File: kinematics.h
 * Brief:
 * Created by: zhangping
 * Created at: 2017.05.14
 * Modified by:
 * Modified at:
 **/

#ifndef _MY_KINEMATICS_H_
#define _MY_KINEMATICS_H_

typedef float float64;

/*
 * Class: Kinematics
 * Brief: this is a Differential Drive Kinematics model.
 */
class Kinematics{
  public:
    Kinematics(float64 l);
    ~Kinematics();
    /*
     * Funcion: DiffDriveK
     * Brief: compute left and right wheel velocity.
     * Args:
     * 		kT: the foward velocity.
     * 		kW: the velocity of rotation.
     * 		vel_l&vel_r: left and right wheel velocities, unit is "m/s". 
     * Return: true if success, otherwise false.
     */
    bool DiffDriveK(const float64 kT, const float64 kW, 
		float64 &vel_l, float64 &vel_r);
		
  private:
	float64 l_; // 轮子与中心点距离。

};

#endif


