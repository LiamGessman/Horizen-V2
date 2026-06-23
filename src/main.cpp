#include <Wire.h>

//declarations!!!!!!!

#include <Arduino.h>

#include "Constants.hpp"
#include "functions/barometer.hpp"
#include "functions/blink.hpp"
#include "functions/eeprom.hpp"


// Use classes or structs to group related parameters together

// instead of top declaring everything as global functions
// use header files.


// try to declare less global variables. Scope your variables
// to your main looping function or in the function where they are
// needed. This ensures better readibility and maintainability



int butt = 0; // Button state

bool logLock = false;

float starttime; // General Time variable

bool logging = false; // Logging detection

void print();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(serialBaud);//serup serial
  pinMode(LED, OUTPUT);//set led pin to output
  delay(1000);//wait? idk why tbh
  while (!Serial) delay(100);//if serial is not working, wait

  led(100, 3);// 3 blinks to show serial is working

  bmp_temp = bmp.getTemperatureSensor();//idk what this is for
  bmp_pressure = bmp.getPressureSensor();
  
  
  unsigned status = bmp.begin();//enables the baro and checks if its working
  if (!status) {//if not led gets very angry
    digitalWrite(LED, HIGH);
    while (1){
      delay(20);
    }
  } else {
    led(200, 2);// yay its working! blink twice in joy!
  }
bmp.setSampling(// set sampling rate i dont understand ts
      Adafruit_BMP280::MODE_NORMAL,
      Adafruit_BMP280::SAMPLING_X2,
      Adafruit_BMP280::SAMPLING_X4,
      Adafruit_BMP280::FILTER_X4,
      Adafruit_BMP280::STANDBY_MS_1);

  altZero();// zero altitude

  starttime = millis(); // Initialize gtime with millis()

  adr = 4; // Initialize adr with 4

  float flightCheck = readFloatFromEEPROM(0);// checks to see if previous flight is loaded? idk ts doesnt work tho

  if (flightCheck != 0) {//lmao i realized i dont even have anything in this FIX THIS!!!!

  }     
  float dZone = millis(); //start deadzone var
  while(1){
      dZone = millis();
      if(analogRead(but)>500){
        //clearEEPROM();
        print();
        logLock = true;
        break;
      }
      else if(dZone > 60000){//get rid of this
        //now
        //stop procastinating

            break;
            //just stop
            //please
      }
      delay(10);
      
  }

}
void print() {
    delay(5000);//why?
    adr = 4;//start off sets ig
    tadr = 8;//src trust me bro
      while(analogRead(but) < 500) {//read button value ig?
          tadr = adr + 4;//ohhh see if its NOT pressed and if so
  
          Serial.print(readFloatFromEEPROM(tadr));// do this
          Serial.print(", ");//comma
          Serial.print(readFloatFromEEPROM(adr));//read eeprom shtuff
          Serial.print(", ");//comma
          Serial.println(adr);//until YOU press button
          delay(25);//delay STOP USING DELAY FIX UR CODE MY GOD
          adr += 8;   //add ocho
          led(20, 1); //ANOTHER DELAY FUNCTION STOOPPPPP
     }
}
void loop() { //main 
  // if your main loop function has its own delay, in a sub-function this 
  // wrecks your iteration rate. Fix this

  float curtime = millis();// finds current time stamp from power on in ms
  float elapsed = (curtime - starttime) / 1000.0; //subtract current time from start time in ms and convert to s
  tadr = adr + 4;// ensure timestamp address is offset
  float filtAlt = altRead(zero);
  if (!logLock) {
    writeFloatToEEPROM(adr, filtAlt); // write
    delay(10); //delay for eeprom r/w cycle
    writeFloatToEEPROM(tadr, elapsed);// write again
  }


  Serial.print(readFloatFromEEPROM(tadr));// now we are reading?
  Serial.print(", ");//comma
  Serial.print(adr);//current eeprom address
  delay(10);// DELAY STOPPPPP
  Serial.print(", ");//comma
  Serial.println(readFloatFromEEPROM(adr));//now read 
  // Serial.print(", ");//why is this commented? yes im commenting on a commnet
  // Serial.println(filtAlt);

  if (analogRead(but) > 500) {//read button value 
    //clearEEPROM();//if presses clear eeprom
  }

  adr += 8; //add 8 bytes to compensate for timestamp
  led(20, 1); // flash LED STOP 
}