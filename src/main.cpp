/**
 * Project: sadakond
 * File:    main.cpp
 * Hardware:Selfmade Arduino Uno x 1
 *          Shift registers 74HC595 x 3
 *          LEDs 10x10
 * Author:  Tauno Erik https://taunoerik.art/
 * Github:  https://github.com/taunoe/sadakond
 * Started: 27.03.2022
 * Edited:  06.04.2022
 **/

#include <Arduino.h>

// My custom 10x10 matrix lib
#include <TaunoMatrix.h>

// Pins
uint8_t LATCH_PIN = 12;  // 12 PB4
uint8_t CLOCK_PIN = 11;  // 11 PB3
uint8_t DATA_PIN = 10;   // 10 PB2

TaunoMatrix Matrix(LATCH_PIN, CLOCK_PIN, DATA_PIN);

int del_time = 1;

uint16_t frame1[10] = {
  0b1000000010,  // 0
  0b1100000100,  // 1
  0b1010001000,  // 2
  0b1001010000,  // 3
  0b1000100000,  // 4
  0b1001010000,  // 5
  0b1010001000,  // 6
  0b1100000100,  // 7
  0b1000000010,  // 8
  0b1000000001,  // 9
};

void print_project_info() {
  Serial.print("Project: ");
  Serial.println("\"Sadakond\"");
  Serial.print("Compiled: ");
  Serial.print(__TIME__);
  Serial.print(" ");
  Serial.println(__DATE__);
  Serial.println("Made by Tauno Erik.");
}

void setup() {
  Serial.begin(115200);
  print_project_info();
  Matrix.begin();
}

void loop() {

  /*
  Displays: \
  */
 /* uint8_t max = 10;

  for (uint8_t i = 0; i < max; i++){
    if (i!=0) {
      Matrix.set_low(i, i);
    }
    Matrix.set_high(i+1, i+1);
    Matrix.send_out();
    delay(del_time);
    Matrix.set_low(i+1, i+1);
  }
*/
  /*
  Display frame
  */
 Matrix.display_frame(frame1);
 //delay(1000);

}
