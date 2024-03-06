#pragma once

// These are all GPIO pins on the ESP32
// Recommended pins include 2,4,12-19,21-23,25-27,32-33
// for the ESP32-S2 the GPIO pins are 1-21,26,33-42

#define PIN_MP3_TX 33 // dfplayer(FIXED)
#define PIN_MP3_RX 32 // dfplayer(FIXED)

#define PIN_LIFT_SERVO 27

#define PIN_TABLE_MOTOR_A 26
#define CH_TABLE_MOTOR_A 6

#define PIN_TABLE_MOTOR_B 25
#define CH_TABLE_MOTOR_B 7

#define PIN_WALK_MOTOR 15
#define CH_WALK_MOTOR 8

#define PIN_CANNON_LED 23
#define CH_CANNON_LED 9