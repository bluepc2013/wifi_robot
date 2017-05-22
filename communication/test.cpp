
#include <iostream>
#include <unistd.h>
#include <string>
#include "protocol.h"
#include "communication.h"

int main(){
  struct Communication com("192.168.1.1",2001);

  // test for receive a data from router
  //while(1){
  //  bool ret = false;
  //  char type,cmd,data;
  //  ret = com.ReceiveData( type, cmd, data);
  //  std::cout<<"Data> "<<std::hex<<type
  //           <<" "<<ret
  //           <<" "<<data<<std::endl;
  //}
  
  // test steering engine
  while(1){
    bool ret = false;
    
    ret = com.SendCmdWithArgs(kSteerEngine7, 120); // 120 deg
    std::cout<<"Ins> kSteerEngine7 120 "<<ret<<std::endl;
    sleep(1);
    
    ret = com.SendCmdWithArgs(kSteerEngine7, 80);  // 80 deg
    std::cout<<"Ins> kSteerEngine7 80 "<<ret<<std::endl;
    sleep(1);
  }
  
  // test vehicle wheel
  //while(1){
  //  com.SendCmd(kMoveRight);
  //  sleep(1);
  //  com.SendCmd(kMoveStop);
  //  sleep(2);
  //  }
  return 0;
}
