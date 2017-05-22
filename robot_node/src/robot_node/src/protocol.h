/**
 * File: protocol.h
 * Brief:
 * Created by: zhangping
 * Created at: 2017.05.3
 * Modified by:
 * Modified at:
 **/
 
#ifndef _MY_PROTOCOL_H_
#define _MY_PROTOCOL_H_

enum Instruction{
  kMoveStop = 0,
  kMoveFoward,
  kMoveBack,
  kMoveLeft,
  kMoveRight,
  kSteerEngine7=9,
  kSteerEngine8=10
};

typedef char U8;

/** Institution protocol format*/
struct CommunicationProtocol{
  U8 header;
  U8 type;
  U8 cmd;
  U8 data;
  U8 end;
};

/** Instruction data*/
const struct CommunicationProtocol kComProtocol[]={
  { 0xff,0x00,0x00,0x00,0xff}, // move stop
  { 0xff,0x00,0x01,0x00,0xff}, // move foward
  { 0xff,0x00,0x02,0x00,0xff}, // move back
  { 0xff,0x00,0x03,0x00,0xff}, // move left
  { 0xff,0x00,0x04,0x00,0xff}, // move right
  { 0xff,0x00,0x05,0x00,0xff}, // move left-foward
  { 0xff,0x00,0x06,0x00,0xff}, // move left-back
  { 0xff,0x00,0x07,0x00,0xff}, // move right-foward
  { 0xff,0x00,0x08,0x00,0xff}, // move right-back
  { 0xff,0x01,0x07,0x00,0xff}, // 7th steering engine
  { 0xff,0x01,0x08,0x00,0xff}, // 8th steering engine
};


/** Sensor data */
/** Ultrasonic data */
struct UltrasonicData{
  U8 header;
  U8 type;
  U8 range;	 // distance
  U8 angle;  //
  U8 end;
};


/** Position data */
struct PositionData{
  U8 header;
  U8 type;
  U8 sensor_id;
  U8 x;
  U8 y;
  U8 z;
  U8 end;
};

/** union for Sensor data  */
union SensorData{
  UltrasonicData ult;
  PositionData pos;
};



#endif

