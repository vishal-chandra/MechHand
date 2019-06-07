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
#include <Gestures.h>

// App auth token. Establishes connection to app.
char auth[] = "7e305e4259c24f6795f3a723d8657e5c"; //personal
//char auth[] = "ee9e940474f246bc95265ab9c8b0975e"; //pennucci

#define pinkypin 32
#define thumbpin 33
#define ringpin 25
#define indexpin 26
#define middlepin 27
Servo pinky;
Servo thumb;
Servo ring;
Servo findex;
Servo middle;


//gestures
Gesture Gopen = Gesture(0, 0, 0, 0, 0); //on pin V5
Gesture Gclose = Gesture(180, 180, 180, 180, 180); //on pin V6
Gesture Gtrump = Gesture(0, 0, 0, 180, 100); //on pin V7
Gesture Gflip = Gesture(180, 180, 0, 180, 180); //on pin V8
//not implemented
Gesture Gpeace = Gesture(180, 180, 0, 0, 180);
Gesture Gthumbsup = Gesture(180, 180, 180, 180, 0);

void performGesture(Gesture g) { 
  pinky.write(g.pinkyPos);
  Blynk.virtualWrite(V0, pinky.read());

  ring.write(g.ringPos);
  Blynk.virtualWrite(V2, ring.read());

  middle.write(g.middlePos);
  Blynk.virtualWrite(V4, middle.read());

  findex.write(g.indexPos);
  Blynk.virtualWrite(V3, findex.read());

  thumb.write(g.thumbPos);
  Blynk.virtualWrite(V1, thumb.read());
}

//pinky (block left side)
BLYNK_WRITE(V0){
  //get and send slider info
  int angle = param.asInt();
  pinky.write(angle);
}
//thumb
BLYNK_WRITE(V1){
  //get and send slider info
  int angle = param.asInt();
  thumb.write(angle);
}
//ring (block left side)
BLYNK_WRITE(V2){
  //get and send slider info
  int angle = param.asInt();
  ring.write(angle);
}
//index
BLYNK_WRITE(V3){
  //get and send slider info
  int angle = param.asInt();
  findex.write(angle);
}
//middle
BLYNK_WRITE(V4){
  //get and send slider info
  int angle = param.asInt();
  middle.write(angle);
}
//open button tapped
BLYNK_WRITE(V5) {
  int pushed = param.asInt();
  if(pushed) {
    performGesture(Gopen);
    Serial.write("open requested\n");
  }
}
//close button tapped
BLYNK_WRITE(V6) {
  int pushed = param.asInt();
  if(pushed) {
    performGesture(Gclose);
    Serial.write("close requested\n");
  }
}
//trump button tapped
BLYNK_WRITE(V7) {
  int pushed = param.asInt();
  if(pushed) {
    performGesture(Gtrump);
    Serial.write("trump requested\n");
  }
}
//flip off button tapped
BLYNK_WRITE(V8) {
  int pushed = param.asInt();
  if(pushed) {
    performGesture(Gflip);
    Serial.write("flip off requested\n");
  }
}

void setup(){
  //pins
  pinMode(pinkypin, OUTPUT);
  pinMode(thumbpin, OUTPUT);
  pinMode(ringpin, OUTPUT);
  pinMode(indexpin, OUTPUT);
  pinMode(middlepin, OUTPUT);
  
  //servos
  pinky.attach(pinkypin, 500, 2400);
  thumb.attach(thumbpin, 500, 2400); 
  ring.attach(ringpin, 500, 2400); 
  findex.attach(indexpin, 500, 2400); 
  middle.attach(middlepin, 500, 2400); 
  
  //misc 
  Serial.begin(9600);
  Serial.println("Waiting for connections...");
  Blynk.setDeviceName("Vishal & Sophia");
  Blynk.begin(auth);
  
}

void loop(){
  Blynk.run();
}
