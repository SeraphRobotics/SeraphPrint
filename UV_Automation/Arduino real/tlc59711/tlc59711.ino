#include <Adafruit_TLC59711.h>



#include "Adafruit_TLC59711.h"
#include <SPI.h>

// How many boards do you have chained?
#define NUM_TLC59711 1

#define data   11 
#define clock  13

Adafruit_TLC59711 tlc = Adafruit_TLC59711(NUM_TLC59711, clock, data);


void setup() {
  Serial.begin(9600);
  
  Serial.println("TLC59711 test");
  pinMode(10, OUTPUT);
  tlc.begin();
  tlc.write();
}

uint8_t d1=0;
uint8_t d2=0;
uint16_t wd=0;

void loop() {

  if (Serial.available() > 1) {
                // read the incoming byte:
                d1 = Serial.read();
                d2 = Serial.read();
                wd = ((uint16_t)d2 << 8) | d1;
                // say what you got:
                Serial.print("I received: ");
//                Serial.println(d1);
//                Serial.println(d2);
                Serial.println(wd);
                colorWipe(wd, 0, 0, 100);   // "Red" (depending on your LED wiring)
  }

}


// Fill the dots one after the other with a color
void colorWipe(uint16_t r, uint16_t g, uint16_t b, uint8_t wait) {
  for(uint16_t i=0; i<8*NUM_TLC59711; i++) {
      tlc.setLED(i, r, g, b);
      tlc.write();
      delay(wait);
  }
}
