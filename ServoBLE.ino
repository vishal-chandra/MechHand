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

// App auth token. Establishes connection to app.
char auth[] = "7e305e4259c24f6795f3a723d8657e5c";
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

//doesn't do anything - for reference right now.
enum vpins {vPinky = V0, vRing = V2, vMiddle = V4, vIndex = V3, vThumb = V1};

/* 
Potential issue with this: writing a value far from the 
current position to a servo causes it to move very fast due to PID.
This may cause odd behaviours with the fingers! Test! Beware!
*/
class Gesture {
  public:
    int pinkyPos;
    int ringPos;
    int middlePos;
    int indexPos;
    int thumbPos;

    Gesture(int _pinky, int _ring, int _middle, int _index, int _thumb) {
      pinkyPos = 180 - _pinky; //rotates opposite direction
      ringPos = 180 - _ring;   //rotates opposite direction
      middlePos = _middle;
      indexPos = _index;
      thumbPos = _thumb;
    }
};

//gestures
Gesture Gclose = Gesture(180, 180, 180, 180, 180);
Gesture Gopen = Gesture(0, 0, 0, 0, 0);
Gesture Gflip = Gesture(0, 0, 180, 0, 0);

//TODO: test with enum...?
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
//open button clicked
BLYNK_WRITE(V5) {
  int pushed = param.asInt();
  if(pushed) {
    //performGesture(Gopen);
    Serial.write("open requested");
  }
}
//close button pushed
BLYNK_WRITE(V6) {
  int pushed = param.asInt();
  if(pushed) {
    //performGesture(Gclose);
    Serial.write("close requested");
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
  Blynk.setDeviceName("Blynk");
  Blynk.begin(auth);
}

void loop(){
  Blynk.run();
}
