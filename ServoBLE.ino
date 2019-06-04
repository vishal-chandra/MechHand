/**
 * Vishal Chandra
 * 5/29/19
 * Controlling 5 servos remotely using BLE
 * Notes: Hold boot button until "Connecting....." appears, then let go and program should write to board
 */

#define BLYNK_PRINT Serial
#define BLYNK_USE_DIRECT_CONNECT

#include <BlynkSimpleEsp32_BLE.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <ESP32Servo.h>

//establishes connection to Blynk app
char auth[] = "7e305e4259c24f6795f3a723d8657e5c";
#define servop1 32
#define servop2 33
#define servop3 25
#define servop4 26
#define servop5 27
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

//Pinky
BLYNK_WRITE(V0){
  //get and send slider info
  int angle = param.asInt();
  servo1.write(angle);
}
//Thumb
BLYNK_WRITE(V1){
  //get and send slider info
  int angle = param.asInt();
  servo2.write(angle);
}
//Ring
BLYNK_WRITE(V2){
  //get and send slider info
  int angle = param.asInt();
  servo3.write(angle);
}
//Index
BLYNK_WRITE(V3){
  //get and send slider info
  int angle = param.asInt();
  servo4.write(angle);
}
//Middle
BLYNK_WRITE(V4){
  //get and send slider info
  int angle = param.asInt();
  servo5.write(angle);
}

void setup(){
  //pins
  pinMode(servop1, OUTPUT);
  pinMode(servop2, OUTPUT);
  pinMode(servop3, OUTPUT);
  pinMode(servop4, OUTPUT);
  pinMode(servop5, OUTPUT);

  //servos
  servo1.attach(servop1, 500, 2400);
  servo2.attach(servop2, 500, 2400); 
  servo3.attach(servop3, 500, 2400); 
  servo4.attach(servop4, 500, 2400); 
  servo5.attach(servop5, 500, 2400); 
  
  //misc
  Serial.begin(9600);
  Serial.println("Waiting for connections...");
  Blynk.setDeviceName("Blynk");
  Blynk.begin(auth);
}

void loop(){
  Blynk.run();
}
