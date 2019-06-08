#include <Gesture.h>
#include <Arduino.h>

Gesture::Gesture(int _pinky, int _ring, int _middle, int _index, int _thumb) {

    pinkyPos = 180 - _pinky; //rotates opposite direction
    ringPos = 180 - _ring;   //rotates opposite direction
    middlePos = _middle;
    indexPos = _index;
    thumbPos = _thumb;

}