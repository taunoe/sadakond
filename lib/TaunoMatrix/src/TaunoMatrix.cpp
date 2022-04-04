/*
 *  File: TaunoMatrix.cpp
 *  Started: 03.04.2022
 *  Edited:  03.04.2022
 *  Copyright 2022 Tauno Erik
 *  https://taunoerik.art/
 */

#include "TaunoMatrix.h"

TaunoMatrix::TaunoMatrix(
  uint8_t latch_pin,
  uint8_t clock_pin,
  uint8_t data_pin)
  : _latch_pin(latch_pin),
    _clock_pin(clock_pin),
    _data_pin(data_pin)
  {}

TaunoMatrix::~TaunoMatrix() {
 // Cleanup
}

void TaunoMatrix::begin() {
  pinMode(_latch_pin, OUTPUT);
  pinMode(_clock_pin, OUTPUT);
  pinMode(_data_pin, OUTPUT);
}

void TaunoMatrix::set_high(uint8_t column, uint8_t row) {
  // To activate column set it low
  switch (column) {
    case 1:
      output[2] &= C1;
      break;
    case 2:
      output[2] &= C2;
      break;
    case 3:
      output[2] &= C3;
      break;
    case 4:
      output[2] &= C4;
      break;
    case 5:
      output[2] &= C5;
      break;
    case 6:
      output[2] &= C6;
      break;
    case 7:
      output[2] &= C7;
      break;
    case 8:
      output[2] &= C8;
      break;
    case 9:
      output[1] &= C9;
      break;
    case 10:
      output[1] &= C10;
      break;
    default:
      break;
  }
  // To activate row set it high
  switch (row) {
    case 1:
      output[1] |= R1;
      break;
    case 2:
      output[1] |= R2;
      break;
    case 3:
      output[1] |= R3;
      break;
    case 4:
      output[1] |= R4;
      break;
    case 5:
      output[1] |= R5;
      break;
    case 6:
      output[1] |= R6;
      break;
    case 7:
      output[0] |= R7;
      break;
    case 8:
      output[0] |= R8;
      break;
    case 9:
      output[0] |= R9;
      break;
    case 10:
      output[0] |= R10;
      break;
  }
}

void TaunoMatrix::set_low(uint8_t column, uint8_t row) {
  // To deactivate column set it HIGH
  switch (column) {
    case 1:
      output[2] |= ~(C1);
      break;
    case 2:
      output[2] |= ~(C2);
      break;
    case 3:
      output[2] |= ~(C3);
      break;
    case 4:
      output[2] |= ~(C4);
      break;
    case 5:
      output[2] |= ~(C5);
      break;
    case 6:
      output[2] |= ~(C6);
      break;
    case 7:
      output[2] |= ~(C7);
      break;
    case 8:
      output[2] |= ~(C8);
      break;
    case 9:
      output[1] |= ~(C9);
      break;
    case 10:
      output[1] |= ~(C10);
      break;
    default:
      break;
  }
  // To deactivate row set it LOW
  switch (row) {
    case 1:
      output[1] &= ~(R1);
      break;
    case 2:
      output[1] &= ~(R2);
      break;
    case 3:
      output[1] &= ~(R3);
      break;
    case 4:
      output[1] &= ~(R4);
      break;
    case 5:
      output[1] &= ~(R5);
      break;
    case 6:
      output[1] &= ~(R6);
      break;
    case 7:
      output[0] &= ~(R7);
      break;
    case 8:
      output[0] &= ~(R8);
      break;
    case 9:
      output[0] &= ~(R9);
      break;
    case 10:
      output[0] &= ~(R10);
      break;
  }
}


void TaunoMatrix::send_out() {
  digitalWrite(_latch_pin, LOW);

  for (uint8_t i = 0; i < 3; i++) {
    shiftOut(_data_pin, _clock_pin, LSBFIRST, output[i]);
  }

  digitalWrite(_latch_pin, HIGH);
}

void TaunoMatrix::print_output() {
  for (uint8_t i = 0; i < 3; i++) {
    Serial.print("_latch_pin: ");
    Serial.print(_latch_pin);
    Serial.print("\n");

    Serial.print("_clock_pin: ");
    Serial.print(_clock_pin);
    Serial.print("\n");

    Serial.print("_data_pin: ");
    Serial.print(_data_pin);
    Serial.print("\n");

    Serial.print(i);
    Serial.print("=");
    Serial.print(output[i], BIN);
    Serial.print("\n");
  }
}
