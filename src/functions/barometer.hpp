#ifndef ALTREAD_HPP
#define ALTREAD_HPP

#include <Adafruit_BMP280.h>


Adafruit_BMP280 bmp;

Adafruit_Sensor *bmp_temp;
Adafruit_Sensor *bmp_pressure;

float zero = 0; // zero val

float oldVal = 0;// old value starts 0 for the math
float newVal;// new value variable
//(bmp.readAltitude(1013.25) * 3.28 - zero);

float altRaw(){//pulls raw altitude value from baro and returns it
    float raw = (bmp.readAltitude(1013.25) * 3.28);
    return raw;
}

float altZero(){// pulls raw value and sets var zero to it, then return zero
    zero = altRaw();
    return zero;
}

float altRead(float zero) {// returns the filtered altitude value after accouting for zero and applys a exponential moving average.
    float alt = 0;
    float mult = .25;
    newVal = (bmp.readAltitude(1013.25) * 3.28 - zero);// pulls val and zero
    alt = (newVal * mult) + (oldVal * (1 - mult));// add it to the EMA
    
    oldVal = alt;

    return alt;
}


#endif