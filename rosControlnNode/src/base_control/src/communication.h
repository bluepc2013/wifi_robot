/**
 * File: communication.h
 * Brief:
 * Created by: zhangping
 * Created at: 2017.05.3
 * Modified by:
 * Modified at:
 **/

#ifndef _MY_COMMUNICATION_H_
#define _MY_COMMUNICATION_H_

#include <string>
#include "protocol.h"

/**
 * Class: Communication
 * Brief: communication with the robot.
 **/
class Communication{
  public:
    Communication(std::string ip, int port);
    ~Communication();
    /**
     * Funcion: SendCmd
     * Brief: send a instruction to router.
     * Args:
     * Return: true if success, otherwise false.
     **/
    bool SendCmd(Instruction ins);
    bool SendCmdWithArgs(Instruction ins, char data);
    
    /**
     * Function: ReceiveData
     * Brief: Receive a data from router.
     * Args:
     * Return: tree if success, otherwise false.
     **/
     bool ReceiveData(char &type, char &cmd, char &data);
    
  private:
    int cid_;// communication IDentifier,this is a socket
    std::string ip_;
    int port_;

    bool _SendCmd(const struct CommunicationProtocol &kInsData);

};

#endif

