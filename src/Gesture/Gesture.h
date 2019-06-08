#ifndef GESTURE_H
    #define GESTURE_H

    //A simple class to contain information
    //about a gesture.
    class Gesture {
        public:
            //position of each finger in when the Gesture
            //has been performed. 180 is fully contracted
            //while 0 is fully extended.
            int pinkyPos;
            int ringPos;
            int middlePos;
            int indexPos;
            int thumbPos;

            //pass in the desired position of each finger
            Gesture(int _pinky, int _ring, int _middle, int _index, int _thumb);
    };

#endif