#ifndef EEPROM_H
#define EEPROM_H

#include <at24c256.h>

AT24C256 eeprom(0x50);

int adr = 4; // eeprom address
int tadr = 8; // time eeprom address

float readFloatFromEEPROM(int address) {// reads from eeprom
    float value;
    byte data[4];
    eeprom.read(address, data, 4); // read 4 bytes from eeprom

    memcpy(&value, data, sizeof(value));
    return value;
  }
  
  void writeFloatToEEPROM(int address, float value) { //writes to eeprom
    byte data[4];
    if (address + 4 > 255000) { //set to real eeprom size
      Serial.println("Error: EEPROM address out of bounds");
      return; //errors out if overfilling eeprom is attempted
    }
    memcpy(data, &value, sizeof(value));
    eeprom.write(address, data, 4); // write 4 bytes to eeprom
  }
  
  void clearEEPROM() { // clears the eeprom
    byte zeros[32] = {0}; // Buffer of 256 zeros
    for (int i = 0; i < 100000; i += 32) { 
      eeprom.write(i, zeros, 32); // Write 255 zeros at a time
       // delay to prevent watchdog timer reset
       delay(10);
       Serial.println(i);
       delay(10);
    }
  }
  #endif // EEPROM_H