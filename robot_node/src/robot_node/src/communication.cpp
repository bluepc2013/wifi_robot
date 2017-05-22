/**
 * File: communication.cpp
 * Brief:
 * Created by: zhangping
 * Created at: 2017.05.3
 * Modified by:
 * Modified at:
 **/
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <sys/types.h> 
#include <sys/socket.h> // socket
#include <arpa/inet.h>  // inet_addr
#include "protocol.h"
#include "communication.h"
#include <string.h>

Communication::Communication(std::string ip, int port):
  ip_(ip),port_(port){

  struct sockaddr_in server;
  
  // Create socket
  this->cid_ = socket(AF_INET , SOCK_STREAM , 0);
  if (this->cid_ == -1)
  {
    std::cerr<<"Error:Could not create socket"<<std::endl;
    exit(-1);
  }
  std::cout<<"Socket created"<<std::endl;

  server.sin_addr.s_addr = inet_addr(this->ip_.c_str());
  server.sin_family = AF_INET;
  server.sin_port = htons(this->port_);

  //Connect to remote server
  if (connect(this->cid_ , (struct sockaddr *)&server , sizeof(server)) < 0)
  {
    std::cerr<<"Error:connect failed with "
             <<ip<<":"
             <<port<<std::endl;
    exit(-1);
  }
	
  std::cout<<"Connected with "
           <<ip<<":"
           <<port<<std::endl;

}


Communication::~Communication(){
  if(this->cid_>0){
	close(this->cid_);
	this->cid_=-1;
  }
}

bool Communication::_SendCmd(const struct CommunicationProtocol &kInsData){
	
  if( send(this->cid_ ,&kInsData.header ,sizeof(kInsData.header) , 0) < 0
    || send(this->cid_ ,&kInsData.type ,sizeof(kInsData.type) , 0) < 0
    || send(this->cid_ ,&kInsData.cmd ,sizeof(kInsData.cmd) , 0) < 0
    || send(this->cid_ ,&kInsData.data ,sizeof(kInsData.data) , 0) < 0
    || send(this->cid_ ,&kInsData.end ,sizeof(kInsData.end) , 0) < 0)
  {
    std::cerr<<"Error:Send failed"<<std::endl;
    return false;
  }
  
  return true;
}

bool Communication::SendCmd(Instruction ins){

  const struct CommunicationProtocol &kInsData=kComProtocol[ins];

  return _SendCmd(kInsData);
}


bool Communication::SendCmdWithArgs(Instruction ins, char data){
  /* 安全检查 */
  if(ins==kSteerEngine7 
    || ins==kSteerEngine8){
		if(data >180){
            std::cerr<<"Error:Error instruction to Steer Engine, angle="
                     <<data<<std::endl;
			return false;
		}
  }

  struct CommunicationProtocol kInsData=kComProtocol[ins];
  kInsData.data = data;
  return _SendCmd(kInsData);
}


/*
bool Communication::ReceiveData(char &type, char &data){

  struct CommunicationProtocol ins_data;
  
  if( recv(this->cid_, &ins_data , sizeof(ins_data), 0) < 0){
    std::cerr<<"Error:Receive failed"<<std::endl;
    return false;
  }
  type = ins_data.type;
  cmd = ins_data.cmd;
  data = ins_data.data;
  
  return true;
}*/



bool Communication::ReceiveData(char &type, char data[], int data_length)
{
	const int kHeaderLength = 2; // Contain package header and type.
	union SensorData uSensorData;

	/** receive a header, first 2 byte. */
    if(recv(this->cid_, &uSensorData, kHeaderLength, 0)<kHeaderLength){
      std::cerr<<"Error:Receive header data failed"<<std::endl;
      return false;
	}

	/** receive body */
	if(uSensorData.ult.type==0x03){ /** Ultrasonic Data*/
		
		if(recv(this->cid_, &uSensorData + kHeaderLength
			, sizeof(uSensorData.ult)- kHeaderLength, 0))
		{
			std::cerr<<"Error:Receive body data failed"<<std::endl;
			return false;
		}
		
		int copy_length = data_length<sizeof(uSensorData.ult)-kHeaderLength-1
				?data_length:sizeof(uSensorData.ult)-kHeaderLength-1;

		memcpy( data, &uSensorData.ult+kHeaderLength, copy_length);
		
	}else if(uSensorData.pos.type==0x88){ // Position Data
		
		if(recv(this->cid_, &uSensorData + kHeaderLength
			, sizeof(uSensorData.pos)-kHeaderLength, 0))
		{
			std::cerr<<"Error:Receive body data failed"<<std::endl;
			return false;
		}

		int copy_length = data_length<sizeof(uSensorData.pos)-kHeaderLength-1
				?data_length:sizeof(uSensorData.pos)-kHeaderLength-1;

		memcpy( data, &uSensorData.pos+kHeaderLength, copy_length);

	}else{ /** Unidentified Data*/
      std::cerr<<"Error:Unidentified header data"<<std::endl;
      return false;
	}
	
	type = uSensorData.ult.type;
	
	return true;
}

