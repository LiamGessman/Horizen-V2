#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <Arduino.h>
#include <Constants.hpp>


class CAMERA{
    private:
        int state=0;
    public:
        void camSetup(){
            pinMode(cam, OUTPUT);
        }
        int enable(){
            digitalWrite(cam, HIGH);
            state=1;
        }
        int disable(){
            digitalWrite(cam, HIGH);
            state=0;
        }

};

#endif //CAMERA_HPP