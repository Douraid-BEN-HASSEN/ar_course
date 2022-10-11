#include <Arduino.h>
#include "heltec.h"
#include <Wire.h>
#include <math.h>

#define DATA_BUFFER_SIZE 7
#define pi 3.1415926535897932384626433832795
#define MPU 0x68

#define SCL 15
#define SDA 4

#define BUTTONS 13

void ReadGY521(int *GyAccTempp, int *GATCorrr);
void ComputeAngle(int *GyAccTempp, double *PitchRol);
int getKey(unsigned int input);

int16_t gyRaw[DATA_BUFFER_SIZE];
double PitchRollYaw[3];

int adc_key_val[5] = { 600, 650, 700, 800, 900 };
int NUM_KEYS = 5;
int adc_key_in;
int key = -1;
int oldkey = -1;

void setup() {
    Heltec.begin(true, false, true);
    Wire.begin(SDA_OLED, SCL_OLED);
    Wire.beginTransmission(MPU);
    Wire.write(0X6B);
    Wire.write(0);
    Wire.endTransmission(true);
    Serial.begin(115200);
}

void loop() {
    ReadGY521(gyRaw);
    ComputeAngle(gyRaw, PitchRollYaw);

    Serial.print("Pitch : ");
    Serial.println(PitchRollYaw[0]);
    Serial.print(" Pitch Raw : ");
    Serial.println(gyRaw[0]);

    Serial.print("Rotate : ");
    Serial.println(PitchRollYaw[1]);
    Serial.print("Rotate Raw : ");
    Serial.println(gyRaw[1]);

    Serial.print("Power : ");
    Serial.println(PitchRollYaw[2]);
    Serial.print(" Power Raw : ");
    Serial.println(gyRaw[2]);

    delay(100);

    adc_key_in = analogRead(BUTTONS);

    key = getKey(adc_key_in);

    if (key != oldkey)  // if keypress is detected
    {
        delay(50);
        // wait for debounce time
        adc_key_in = analogRead(BUTTONS);  // read the value from the sensor
        key = getKey(adc_key_in);         // convert into key press
        if (key != oldkey) {
            oldkey = key;
            if (key >= 0) {
                digitalWrite(13, HIGH);
                switch (key) {
                    case 0:
                        Serial.println("S1 OK");
                        break;
                    case 1:
                        Serial.println("S2 OK");
                        break;
                    case 2:
                        Serial.println("S3 OK");
                        break;
                    case 3:
                        Serial.println("S4 OK");
                        break;
                    case 4:
                        Serial.println("S5 OK");
                        break;
                }
            }
        }
    }
}

void ReadGY521(int16_t *gyRaw) {

    // Init du module GY-521
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 14, true);

    for (int i = 0; i < DATA_BUFFER_SIZE; i++) {
        gyRaw[i] = (Wire.read() << 8 | Wire.read());
    }
}

void ComputeAngle(int16_t *gyRaw, double *PitchRollYaw) {
    PitchRollYaw[0] = map(gyRaw[0], -16384, 16384, -100, 100);  // Pitch - *
    PitchRollYaw[1] = map(gyRaw[1], -16384, 16384, -100, 100);  // Roll - Angle
    PitchRollYaw[2] = map(gyRaw[2], -16384, 16384, -100, 100);  // Yaw - Power

    PitchRollYaw[0] = constrain(PitchRollYaw[0], -100, 100);
    PitchRollYaw[1] = constrain(PitchRollYaw[1], -100, 100);
    PitchRollYaw[2] = constrain(PitchRollYaw[2], -100, 100);
}

int getKey(unsigned int input) {

    int k;

    for (k = 0; k < NUM_KEYS; k++) {
        if (input < adc_key_val[k]) {
            return k;
        }
    }

    if (k >= NUM_KEYS) k = -1;  // No valid key pressed
    return k;
}