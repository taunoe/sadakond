/**
 * Project: 10x10 LEDs
 * File:    main.cpp
 * Hardware:Selfmade Arduino Uno x 1
 *          Shift registers 74HC595 x 3
 *          LEDs 10x10
 * Author:  Tauno Erik https://taunoerik.art/
 * Started: 27.03.2022
 * Edited:  02.04.2022
 **/

#include <Arduino.h>

// My custom matrix lib
#include <TaunoMatrix.h>

// Pins
uint8_t LATCH_PIN = 12;  // PB4
uint8_t CLOCK_PIN = 11;  // PB3
uint8_t DATA_PIN = 10;   // PB2

TaunoMatrix Matrix(LATCH_PIN, CLOCK_PIN, DATA_PIN);

int del_time = 1;

void setup() {
  Serial.begin(115200);
  Matrix.begin();
}

void loop() {
  /*
  Matrix.set_high(1, 1);
  Matrix.send_out();
  delay(del_time);*/

  Matrix.set_low(1, 1);
  Matrix.set_high(2, 2);
  Matrix.send_out();
  delay(del_time);

  Matrix.set_low(2, 2);
  Matrix.set_high(3, 3);
  Matrix.send_out();
  delay(del_time);

  Matrix.set_low(3, 3);
  Matrix.set_high(4, 4);
  Matrix.send_out();
  delay(del_time);

  Matrix.set_low(4, 4);
  Matrix.set_high(5, 5);
  Matrix.send_out();
  delay(del_time);

  Matrix.set_low(5, 5);
 
  /*
  uint8_t max = 10;

  for (uint8_t i = 0; i < max; i++){
    if (i!=0) {
      Matrix.set_low(i, i);
    }
    Matrix.set_high(i+1, i+1);
    Matrix.send_out();
    delay(del_time);
  }
  */
}
