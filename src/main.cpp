#include <Arduino.h>

#include "esp_log.h"

#include "common.h"
#include "controllers/Mp3Controller.h"
#include <ServoEasing.hpp>

#define MAIN_TAG "Main"

ServoEasing servo1;

void setup()
{
#ifdef DEBUG
    ESP_LOGI(MAIN_TAG, "Setup...");
#endif

    setupSound();

    // Init Table Motor
    ledcSetup(CH_TABLE_MOTOR_A, 1000, 8);
    ledcAttachPin(PIN_TABLE_MOTOR_A, CH_TABLE_MOTOR_A);
    ledcSetup(CH_TABLE_MOTOR_B, 1000, 8);
    ledcAttachPin(PIN_TABLE_MOTOR_B, CH_TABLE_MOTOR_B);

    ledcWrite(CH_TABLE_MOTOR_A, 255);
    ledcWrite(CH_TABLE_MOTOR_B, 0);

    // Init Walk Motor
    ledcSetup(CH_WALK_MOTOR, 1000, 8);
    ledcAttachPin(PIN_WALK_MOTOR, CH_WALK_MOTOR);
    ledcWrite(CH_WALK_MOTOR, 0);

    // Init Cannon LED
    ledcSetup(CH_CANNON_LED, 1000, 8);
    ledcAttachPin(PIN_CANNON_LED, CH_CANNON_LED);

    // Init Servo
    servo1.attach(PIN_LIFT_SERVO);
    servo1.setEasingType(EASE_SINE_OUT);
    servo1.easeTo(90);

    // Lift Up
    servo1.easeTo(90 + 65, 10);

    // Start to walk
    ledcWrite(CH_WALK_MOTOR, 159);
}

unsigned long lastChecked = 0;

void loop()
{
    const unsigned long now = millis();
    if (lastChecked == 0)
    {
        lastChecked = now;
        return;
    }
    if (now - lastChecked > 1000 * 10)
    {
        ledcWrite(CH_WALK_MOTOR, 0);
        delay(2000);

        playCannon();
        delay(700);
        ledcWrite(CH_CANNON_LED, 255);
        // delay(500);
        servo1.write(90 + 80);
        delay(500);
        ledcWrite(CH_CANNON_LED, 0);
        servo1.write(90 + 70);
        delay(1000 * 2);

        ledcWrite(CH_WALK_MOTOR, 159);

        lastChecked = millis();
    }
}
