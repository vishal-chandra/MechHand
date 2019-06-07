#ifndef GESTURE_H
    #define GESTURE_H

    class Gesture {
        public:
            int pinkyPos;
            int ringPos;
            int middlePos;
            int indexPos;
            int thumbPos;

            Gesture(int _pinky, int _ring, int _middle, int _index, int _thumb);
    };
    
#endif