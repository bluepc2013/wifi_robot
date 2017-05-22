#include "ros/ros.h"
#include "protocol.h"
#include "communication.h"
#include "sensor_msgs/LaserScan.h"
#include "robot_msgs/RobotIns.h"
#include "robot_msgs/RobotPosition.h"
#include <boost/bind.hpp>
#include <boost/ref.hpp>


typedef const boost::function<void (const robot_msgs::RobotIns::ConstPtr& msg)> InsCallback;


/**
 * do work.
 */
void do_pos(ros::Publisher &pub, U8 x, U8 y, U8 z){
	std::cout<<"Position=["
			 <<x<<","
			 <<y<<","
			 <<z<<"]"<<std::endl;
}

void do_ultrasonic(ros::Publisher &pub, U8 range, U8 angle){
	std::cout<<"ultrasonic : range="
			 <<range<<",angle="
			 <<angle<<std::endl;
}


/**
 * This callback function will forward Institution message to our Robot.
 */
void InsForward(const robot_msgs::RobotIns::ConstPtr& msg, Communication &com)
{
	com.SendCmdWithArgs( msg->cmd, msg->data);
}


int main(int argc, char **argv)
{
    /**
     * Init Node.
     */
    ros::init(argc, argv, "robot_node");
    ros::NodeHandle n;

    /**
     * deal with Institution message.
     */
    Communication com("192.168.1.1",2001);
    InsCallback ins_callback = boost::bind(InsForward, _1, boost::ref(com));
    ros::Subscriber sub = n.subscribe("/robot_ins", 100, ins_callback);

    /**
     * deal with Sensors message.
     */
    ros::Publisher laser_pub = n.advertise<sensor_msgs::LaserScan>("scan", 50);
    ros::Publisher pos1_pub = n.advertise<robot_msgs::RobotPosition>("robot_pos1", 50);;
    ros::Publisher pos2_pub = n.advertise<robot_msgs::RobotPosition>("robot_pos2", 50);
    //ros::Publisher imu_pub = ;
    while(ros::ok()){
        /** Receive data from robot */
        U8 type;
        U8 sensor_data[10];
        if(!com.ReceiveData(type, sensor_data, 10)){
			std::cerr<<"Error:Receive sensor data failed"<<std::endl;
			continue;
		}
		
		/** Valid data */
        if(false){
            continue;
        }
        
        /** Foward to the topic */
	    if( type==0x03){ /** Ultrasonic data */
			do_ultrasonic(laser_pub, sensor_data[0], sensor_data[1]);
			
		}else if(type==0x88){ /** Position data */
			U8 sensor_id = sensor_data[0];
			if(sensor_id==0x01){
				do_pos(pos1_pub, sensor_data[1], sensor_data[2]
					, sensor_data[3]);
			}
			if(sensor_id==0x02){
				do_pos(pos2_pub, sensor_data[1], sensor_data[2]
					, sensor_data[3]);
			}
		}
    }
 
   return 0;
}
