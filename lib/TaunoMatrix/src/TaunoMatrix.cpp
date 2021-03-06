/*
 * File: TaunoMatrix.cpp
 * Started: 03.04.2022
 * Edited:  13.04.2022
 * Copyright 2022 Tauno Erik
 * https://taunoerik.art/
 * https://github.com/taunoe/sadakond
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
  // Set pins as output
  // PB4 latch pin
  DDRB |= (1<<4);  //pinMode(_latch_pin, OUTPUT);
  // PB3 clock pin
  DDRB |= (1<<3);  //pinMode(_clock_pin, OUTPUT);
  // PB2 data pin
  DDRB |= (1<<2);  //pinMode(_data_pin, OUTPUT);
}

/*
Set one LED high.
Param column
Param row
*/
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

/*
Set one LED low.
Param column
Param row
*/
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

/*
Set one LED low or high.
Param column
Param row
Param value
*/
void TaunoMatrix::set(uint8_t column, uint8_t row, uint8_t value) {
  Serial.println(row);
  if (value > 0) {
    set_high(column, row);
  } else {
    set_low(column, row);
  }
}

/*
Set all LEDs on row off.
Param row.
*/
void TaunoMatrix::set_row_off(uint8_t row) {
  for (size_t column = 0; column < 10; column++) {
    set(column+1, row, 0);
  }
}

/*
 * Copy-paste on Arduino function:
 https://github.com/arduino/ArduinoCore-avr/blob/master/cores/arduino/wiring_shift.c
 https://github.com/arduino/ArduinoCore-avr/blob/24e6edd475c287cdafee0a4db2eb98927ce3cf58/cores/arduino/wiring_digital.c
 */
void TaunoMatrix::shift_out(uint8_t data_pin,
                            uint8_t clock_pin,
                            uint8_t bit_order,
                            uint8_t val) {
  for (uint8_t i = 0; i < 8; i++) {
    if (bit_order == LSBFIRST) {
      digitalWrite(data_pin, val & 1);
      val >>= 1;
    } else {
      digitalWrite(data_pin, (val & 128) != 0);
      val <<= 1;
}

  //digitalWrite(clock_pin, HIGH);
  PORTB |= (1<<3); // Set to HIGH
  //digitalWrite(clock_pin, LOW);
  PORTB &= ~(1<<3); // Set to LOW
  }
}


/*
 * Send all data (== array output[]) to shift register.
 */
void TaunoMatrix::send_out() {
  //digitalWrite(_latch_pin, LOW);
  PORTB &= ~(1<<4); // Set to LOW

  for (uint8_t i = 0; i < 3; i++) {
    //shiftOut(_data_pin, _clock_pin, LSBFIRST, output[i]);
    shift_out(_data_pin, _clock_pin, LSBFIRST, output[i]);
    
  }

  //digitalWrite(_latch_pin, HIGH);
  PORTB |= (1<<4); // Set to HIGH
}


/*
 * Print raw data
*/
void TaunoMatrix::print_output() {
  for (uint8_t i = 0; i < 3; i++) {
    Serial.print(i);
    Serial.print("=");
    Serial.print(output[i], BIN);
    Serial.print("\n");
  }
}

/*
Set all LEDs (10x10) at once.
Param array[10]
TODO: time
*/
void TaunoMatrix::display_frame(uint16_t array[]) {
  // Iga massiivi element sisaldab 10-bittist numbrit
  uint8_t size = 10;

  for (uint8_t row = 0; row < size; row++) {
    uint16_t read_column = 0b1000000000;

    for (size_t column = 0; column < 10; column++) {
      uint16_t column_value =  array[row] & read_column;

      if (column_value > 0) {
        set(column+1, row+1, 1);
      } else {
        set(column+1, row+1, 0);
      }

      send_out();

      // Liigutame uut loetavat positsiooni
      read_column = read_column >> 1;
    }
    //send_out();
    set_row_off(row+1);
  }
}

/*
Change LEDs on row high/low.
Param values == columns
*/
void TaunoMatrix::change_row(uint8_t row, uint16_t values) {
  uint16_t read_column = 0b1000000000;

 
  for (size_t column = 0; column < 10; column++) {
    // Read bit value
    uint16_t column_value =  values & read_column;

    if (column_value > 0) {
      set(column+1, row, 1);
    } else {
      set(column+1, row, 0);
    }
    // Select new bit
    read_column = read_column >> 1;
  }
  // Display
  send_out();
}
