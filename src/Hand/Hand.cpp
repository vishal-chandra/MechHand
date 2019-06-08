/**
 * Vishal chandra
 * 6/7/19
 * 
 * A class representing the mechanical hand
 * itself. Contains servo objects and associated methods.
 */
#include <Hand.h>
#include <Arduino.h>
#include <BlynkSimpleEsp32_BLE.h>
#include <BLEDevice.h>
#include <BLEServer.h>

//Constructor. Sets each pin to output and attaches a servo to each.
Hand::Hand(int pinkypin, int ringpin, int middlepin, int indexpin, int thumbpin){

    //set pins
    pinMode(pinkypin, OUTPUT);
    pinMode(thumbpin, OUTPUT);
    pinMode(ringpin, OUTPUT);
    pinMode(indexpin, OUTPUT);
    pinMode(middlepin, OUTPUT);
    
    //attach servos
    pinky.attach(pinkypin, 500, 2400);
    thumb.attach(thumbpin, 500, 2400); 
    ring.attach(ringpin, 500, 2400); 
    findex.attach(indexpin, 500, 2400); 
    middle.attach(middlepin, 500, 2400); 
}

//writes each position value from a gesture object
//to the respective finger. Then updates gui sliders
//associated with each servo.
void Hand::performGesture(Gesture g) { 
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