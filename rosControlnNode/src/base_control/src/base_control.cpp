/**
 * File: base_control.h
 * Brief:
 * Created by: zhangping
 * Created at: 2017.05.15
 * Modified by:
 * Modified at:
 **/

#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "kinematics.h"
#include "wheelControl.h"
#include "protocol.h"      // For Instruction
#include "communication.h" // Fro communication


typedef const boost::function<void (const geometry_msgs::Twist::ConstPtr& msg)> Callback;

/**
 * receipt of messages over the ROS system.
 */
void VelCallback(const geometry_msgs::Twist::ConstPtr& msg
                 , Kinematics &ki
                 , WheelControl &wc_l
                 , WheelControl &wc_r
                 , Communication &com)
{
  ROS_INFO("Twist> [T=%f,W=%f]", msg->linear.x, msg->angular.z);
  
  // velocity to left&right wheel velocity
  float64 vel_l;
  float64 vel_r;
  if (!ki.DiffDriveK( msg->linear.x, msg->angular.z, vel_l, vel_r)){
    std::cerr<<"Error:failed to transform."<<std::endl;
    exit(-1);
  }
  ROS_INFO("WheelVel> [vel_l=%f, vel_r=%f]", vel_l, vel_r);
  
  // left&right wheel velocity to pwm ratio.
  float64 pwm_l = wc_l.Transform(vel_l);
  float64 pwm_r = wc_l.Transform(vel_r);
  ROS_INFO("PWM> [pwm_l=%f, pwm_r=%f]", pwm_l, pwm_r);
  
  // Send pwm ratio
  U8 pwm_r_l = pwm_l*100;
  U8 pwm_r_r = pwm_r*100;
  ROS_INFO("PWM_R> [pwm_r_l=%d, pwm_r_r=%d]", pwm_r_l, pwm_r_r);
  com.SendCmdWithArgs(kLeftWheelMoveFoward, pwm_r_l);
  com.SendCmdWithArgs(kRightWheelMoveFoward, pwm_r_r);

}



int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can 
   * perform any ROS arguments and name remapping that were provided at 
   * the command line. For programmatic remappings you can use a 
   * different version of init() which takes remappings directly, but 
   * for most command-line programs, passing argc and argv is the 
   * easiest way to do it.  The third argument to init() is the name of 
   * the node.
   *
   * You must call one of the versions of ros::init() before using any 
   * other part of the ROS system.
   */
  ros::init(argc, argv, "base_control");
   /**
   * NodeHandle is the main access point to communications with the ROS 
   * system. The first NodeHandle constructed will fully initialize this
   *  node, and the last NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;
  
  // Create a kinematic model.
  Kinematics ki(0.05);
  // Create a wheelControl model.
  WheelControl wc_l(0.02);
  WheelControl wc_r(0.02);
  // Create a link
  Communication com("192.168.1.1",2001);
  /**
   * The subscribe() call is how you tell ROS that you want to receive 
   * messages on a given topic.  This invokes a call to the ROS master 
   * node, which keeps a registry of who is publishing and who is 
   * subscribing.  Messages are passed to a callback function. 
   * subscribe() returns a Subscriber object that you must hold on to 
   * until you want to unsubscribe.  When all copies of the Subscriber 
   * object go out of scope, this callback will automatically be 
   * unsubscribed from this topic. The second parameter to the 
   * subscribe() function is the size of the message queue.  If messages
   *  are arriving faster than they are being processed, this is the 
   * number of messages that will be buffered up before beginning to 
   * throw away the oldest ones.
   */
  Callback func = boost::bind(VelCallback, _1, boost::ref(ki)
                                           , boost::ref(wc_l)
                                           , boost::ref(wc_r)
                                           , boost::ref(com));
  ros::Subscriber sub = n.subscribe("cmd_vel", 100, func);

  /**
   * ros::spin() will enter a loop, pumping callbacks.  With this 
   * version, all callbacks will be called from within this thread (the
   * main one).  ros::spin() will exit when Ctrl-C is pressed, or the 
   * node is shutdown by the master.
   */
  ros::spin();
  return 0;
}
