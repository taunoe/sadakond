/*
 * File: TaunoMatrix.h
 * Started: 03.04.2022
 * Edited:  13.04.2022
 * Copyright 2022 Tauno Erik
 * https://taunoerik.art/
 * https://github.com/taunoe/sadakond
 */

#include <Arduino.h>

#if !defined(LIB_TAUNOMATRIX_H)
#define LIB_TAUNOMATRIX_H

class TaunoMatrix {
  private:
  // Shift Register Pins
  uint8_t _latch_pin;
  uint8_t _clock_pin;
  uint8_t _data_pin;

  // Output array
  uint8_t output[3] = {
    // C == 0 == ON
    // R == 1 == ON
    0b00000000,  // 0 - R7,R8,R9,R10,nc,nc,nc,nc
    0b11100000,  // 1 - C9,C10,R1,R2,R3,R4,R5,R6
    0b01111111   // 2 - C1,C2,C3,C4,C5,C6,C7,C8
  };

  // LEDs
  const uint8_t  C1 = 0b01111111;  // 2
  const uint8_t  C2 = 0b10111111;  // 2
  const uint8_t  C3 = 0b11011111;  // 2
  const uint8_t  C4 = 0b11101111;  // 2
  const uint8_t  C5 = 0b11110111;  // 2
  const uint8_t  C6 = 0b11111011;  // 2
  const uint8_t  C7 = 0b11111101;  // 2
  const uint8_t  C8 = 0b11111110;  // 2
  const uint8_t  C9 = 0b01111111;  // 1
  const uint8_t C10 = 0b10111111;  // 1

  const uint8_t  R1 = 0b00100000;  // 1
  const uint8_t  R2 = 0b00010000;  // 1
  const uint8_t  R3 = 0b00001000;  // 1
  const uint8_t  R4 = 0b00000100;  // 1
  const uint8_t  R5 = 0b00000010;  // 1
  const uint8_t  R6 = 0b00000001;  // 1
  const uint8_t  R7 = 0b10000000;  // 0
  const uint8_t  R8 = 0b01000000;  // 0
  const uint8_t  R9 = 0b00100000;  // 0
  const uint8_t R10 = 0b00010000;  // 0

  //
  const uint8_t high = 1;
  const uint8_t low = 0;

  public:
  TaunoMatrix(uint8_t latch_pin,uint8_t clock_pin, uint8_t data_pin);
  ~TaunoMatrix();
  // Sets pin modes
  void begin();
  // Set one LED high
  void set_high(uint8_t column, uint8_t row);
  // Set one LED low
  void set_low(uint8_t column, uint8_t row);
  // Set on LED low or high
  void set(uint8_t column, uint8_t row, uint8_t value);
  // 
  void shift_out(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);
  // Send all data out to shift registers
  void send_out();
  // Turn all LEDs on row off
  void set_row_off(uint8_t row);
  //
  void change_row(uint8_t row, uint16_t values);
  void print_output();   // Serial.print data.

  /*
   * Displays matrix dada.
   * Input is 16-bit array[10] (8-bit is too small to hold 10 places!)
   */
  void display_frame(uint16_t array[]);
};

#endif // LIB_TAUNOMATRIX_H
