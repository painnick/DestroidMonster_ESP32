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

    servo1.attach(PIN_LIFT_SERVO);
    servo1.setEasingType(EASE_SINE_OUT);
    servo1.easeTo(90);
    servo1.easeTo(90 + 70, 10);

    ledcSetup(CH_TABLE_MOTOR, 1000, 8);
    ledcAttachPin(PIN_TABLE_MOTOR, CH_TABLE_MOTOR);

    ledcWrite(CH_TABLE_MOTOR, 255);

    ledcSetup(CH_WALK_MOTOR, 1000, 8);
    ledcAttachPin(PIN_WALK_MOTOR, CH_WALK_MOTOR);

    ledcWrite(CH_WALK_MOTOR, 159);
}

unsigned long lastChecked = 0;

void loop()
{
    const unsigned long now = millis();
    if(lastChecked == 0)
    {
        lastChecked = now;
        return;
    }
    if (now - lastChecked > 1000 * 10)
    {
        ledcWrite(CH_WALK_MOTOR, 0);
        delay(2000);

        playCannon();
        delay(1000);
        servo1.write(90 + 80);
        delay(500);
        servo1.write(90 + 70);
        delay(1000 * 2);

        ledcWrite(CH_WALK_MOTOR, 159);

        lastChecked = millis();
    }
}
