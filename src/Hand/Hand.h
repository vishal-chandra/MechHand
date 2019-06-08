#ifndef HAND_H
    #define HAND_H
    #include <Arduino.h>
    #include <ESP32Servo.h>
    #include "Gesture.h"

    class Hand {
        public:
            //esp32servo objects
            Servo pinky;
            Servo thumb;
            Servo ring;
            Servo findex;
            Servo middle;

            //A hand object can be created by passing 
            //in the pins to which each of its finger 
            //servos are connected.
            Hand(int pinkypin, int ringpin, int middlepin, int indexpin, int thumbpin);

            //A gesture object can be passed
            //in here to be executed. See 
            //Gesture.h for more info.
            void performGesture(Gesture g);

    };

#endif