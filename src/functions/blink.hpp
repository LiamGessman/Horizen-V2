#ifndef BLINK_HPP
#define BLINK_HPP

#include <Arduino.h>


void led(int del, int amt) { //blinks "amt" amount of times with delay of "del"  between each blink (really bad for cycle rate fix it to use time based later)
    int j = 0; //int
    while (j != amt) {//PLEASE PUT A FOR HERE MY GOD WHILE IS GONNA COOK YOU
      digitalWrite(LED, HIGH);// led on
      delay(del);//wait
      digitalWrite(LED, LOW);// led off
      delay(del);// wait once more
      j += 1;// iterate var j
    }
}

#endif