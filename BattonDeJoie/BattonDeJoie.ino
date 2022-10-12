#include <Arduino.h>
#include "heltec.h"
#include <Wire.h>
#include <math.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

#define DATA_BUFFER_SIZE 7
#define MPU 0x68

#define SCL 15
#define SDA 4

#define BUTTONS 36

const char *WIFI_SSID = "IMERIR_IoT";
const char *WIFI_PASSWORD = "kohWoong5oox";

const char *MQTT_ENDPOINT = "omniumcorp.fr";  // Adresse IP du Broker Mqtt
const char *MQTT_PUB_TOPIC = "game/properties";   // Topic
const int MQTT_PORT = 1883;                       // Port utilisé par le Broker
long tps = 0;

void callback(char *topic, byte *message, unsigned int length);

WiFiClient wiFiClient;
PubSubClient pubSubClient(MQTT_ENDPOINT, MQTT_PORT, callback, wiFiClient);

bool connectToWIFI(int tryConnect, bool debug);
bool connectToMqtt();

/* gyroscope value */
void ReadGY521(int *GyAccTempp, int *GATCorrr);
void ComputeAngle(int *GyAccTempp, double *PitchRol);
int getKey(unsigned int input);

int16_t gyRaw[DATA_BUFFER_SIZE];
double PitchRollYaw[3];

/* button value */
int adc_key_val[5] = { 2950, 3100, 3260, 3600, 3930 };
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

    Serial.begin(9600);
    Serial.println("Started!");

    while (!connectToWIFI(20, true)) {}    

    Serial.println("\nConnected to the WiFi network");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    // mqttClient.setServer(mqtt_server, mqtt_port);
    // mqttClient.setCallback(callback);
    // mqttClient.subscribe("suce/pute");
    // mqttClient.publish("suce/pute", "aaaa");
    



    Serial.println("end setup!");    
}

void loop() {

    if (WiFi.status() == WL_CONNECTED){
            connectToMqtt();
    }

    ReadGY521(gyRaw);
    ComputeAngle(gyRaw, PitchRollYaw);

    // Serial.print("Pitch : ");
    // Serial.println(PitchRollYaw[0]);
    // Serial.print(" Pitch Raw : ");
    // Serial.println(gyRaw[0]);

    // Serial.print("Rotate : ");
    // Serial.println(PitchRollYaw[1]);
    // Serial.print("Rotate Raw : ");
    // Serial.println(gyRaw[1]);

    // Serial.print("Power : ");
    // Serial.println(PitchRollYaw[2]);
    // Serial.print(" Power Raw : ");
    // Serial.println(gyRaw[2]);

    delay(100);

    adc_key_in = analogRead(BUTTONS);

    key = getKey(adc_key_in);

    if (key != oldkey)  // if keypress is detected
    {
        delay(50);
        // wait for debounce time
        adc_key_in = analogRead(BUTTONS);  // read the value from the sensor
        key = getKey(adc_key_in);          // convert into key press
        if (key != oldkey) {
            oldkey = key;
            if (key >= 0) {
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

bool connectToWIFI(int tryConnect, bool debug) {

    Serial.print("Waiting for connection to WiFi to : "); Serial.print(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);   //WiFi connection

    if (debug){
        int i = 0;
        while (WiFi.status() != WL_CONNECTED) {
        
            if (i <= tryConnect) {
                delay(500);
                Serial.print('.');
                i++;
            } else {  //delay passed
                Serial.println("Delay passed");
                return false;
            }
        }
        Serial.println("Connected");

    }

    return true;
}

bool connectToMqtt() {
    if (!pubSubClient.connected()) {
        Serial.print("PubSubClient connecting to : "); Serial.println(MQTT_ENDPOINT);
        
        while (!pubSubClient.connected()) {
            Serial.print(pubSubClient.state());
            delay(100);
            Serial.print(".");
            pubSubClient.connect("ladg");
        }

        Serial.println(" connected");
        pubSubClient.subscribe(MQTT_PUB_TOPIC);
    }

    pubSubClient.loop();
    return true;
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

void callback(char *topic, byte *message, unsigned int length) {
    Serial.print("Message arrived on topic: ");
    Serial.print(topic);
    Serial.print(". Message: ");
    String messageTemp;

    for (int i = 0; i < length; i++) {
        Serial.print((char)message[i]);
        messageTemp += (char)message[i];
    }
    Serial.println();

    // Feel free to add more if statements to control more GPIOs with MQTT

    // If a message is received on the topic esp32/output, you check if the message is either "on" or "off".
    // Changes the output state according to the message
    if (String(topic) == "esp32/output") {
        Serial.print("Changing output to ");

    }
}