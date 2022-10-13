#include <Arduino.h>
#include "heltec.h"
#include <Wire.h>
#include <math.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <esp_wifi.h>

#include <PubSubClient.h>
#include "UUID.h"
#include <ArduinoJson.h>

#define DATA_BUFFER_SIZE 7
#define MPU 0x68

#define SCL 15
#define SDA 4

#define GPIO_BUTTONS 36

#define YELLOW_BUTTON 0
#define GREEN_BUTTON 1
#define BLUE_BUTTON 2
#define RED_BUTTON 3
#define WHITE_BUTTON 4

uint8_t newMACAddress[] = {0x32, 0xAE, 0xA4, 0x07, 0x0D, 0x66};

UUID uuid;

/** credantial setup */
// const char *WIFI_SSID = "valentin";
// const char *WIFI_PASSWORD = "valentin";
// const char *WIFI_SSID = "IMERIR_enculer";
// const char *WIFI_PASSWORD = "12345678";
const char *WIFI_SSID = "IMERIR_IoT";
const char *WIFI_PASSWORD = "kohWoong5oox";

const char *MQTT_ENDPOINT = "omniumcorp.fr";     // Adresse IP du Broker Mqtt
// const char *MQTT_ENDPOINT = "77.159.224.21";     // Adresse IP du Broker Mqtt
// const char *MQTT_ENDPOINT = "gerald.imerir.org";     // Adresse IP du Broker Mqtt

const char *MQTT_SUB_TOPIC = "game/properties";  // Topic
const char *MQTT_REGISTER_TOPIC = "player/register";
const char *MQTT_CONTROL_TOPIC = "player/control";


const int MQTT_PORT = 1883;  // Port utilisé par le Broker
long tps = 0;

StaticJsonDocument<1024> properties_doc;
StaticJsonDocument<1024> register_doc;
StaticJsonDocument<1024> control_doc;

/** wifi and mqtt setup */
void callback(char *topic, byte *message, unsigned int length);

WiFiClient wiFiClient;
PubSubClient pubSubClient(MQTT_ENDPOINT, MQTT_PORT, callback, wiFiClient);

bool connectToWIFI(int tryConnect, bool debug);
bool connectToMqtt();


/** gyroscope value setup */
void ReadGY521(int *GyAccTempp, int *GATCorrr);
void ComputeAngle(int *GyAccTempp, double *PitchRol);

int16_t gyRaw[DATA_BUFFER_SIZE];
double PitchRollYaw[3];

/** button setup */
int adc_key_val[5] = { 3000, 3200, 3350, 3600, 3900 };
int NUM_KEYS = 5;
int adc_key_in;
int key = -1;
int oldkey = -1;

int get_key(unsigned int input);

int catchButton();

/** gameStatus */
int gameStatus = 0;


class Vehicle {

public:
    const char *name = "";
    int maxSpeed = 0;
    float acceleration = 0.;
    int weight = 0;
    float steeringAngle = -1;
    int width = 0;
    int height = 0;

    String toString() {
        return String(name) + " | " +  String(maxSpeed) + " | " + String(acceleration) + "\n | " + String(weight) + " | " + String(steeringAngle) + " | " + String(width) + " | " + String(height);
    };

};

int vehicles_size = 0;
Vehicle *vehicles[10];
int vehicle_index = 0;

void setup() {

    /** i2c init */
    Heltec.begin(true, false, true);
    Wire.begin(SDA_OLED, SCL_OLED);
    Wire.beginTransmission(MPU);
    Wire.write(0X6B);
    Wire.write(0);
    byte error = Wire.endTransmission(true);
    WiFi.mode(WIFI_STA);
    esp_wifi_set_mac(WIFI_IF_STA, &newMACAddress[0]);


    Heltec.display->init();
    Heltec.display->clear();
    Heltec.display->drawString(0, 28, "Vroum Vroum started!");
    Heltec.display->display();

    delay(5000);

    Serial.begin(9600);
    Serial.println("Started!");

    /* wifi connexion */
    while (!connectToWIFI(20, true)) {}

    Heltec.display->clear();
    Heltec.display->drawString(0, 28, "Wifi connected");
    Heltec.display->drawString(0, 35, String(WiFi.localIP()));
    Heltec.display->display();

    Serial.println("\nConnected to the WiFi network");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    Serial.println("end setup!");

    pubSubClient.setBufferSize(1024);
}

void loop() {

    /* mqtt connexion */
    if (WiFi.status() != WL_CONNECTED) {

        Heltec.display->clear();
        Heltec.display->drawString(0, 28, "Wifi disconnected!");
        Heltec.display->display();

        while (!connectToWIFI(20, true)) {}
    }

    connectToMqtt();

    if (gameStatus == 0) {

        Heltec.display->clear();
        Heltec.display->drawString(0, 28, "Wait Properties !");
        Heltec.display->display();    
        
        if (properties_doc["vehicleOptions"].size() > 0) {

            for (JsonPair kv : properties_doc["vehicleOptions"].as<JsonObject>()) {
                JsonObject vehJson = kv.value().as<JsonObject>();
                
                static int i = 0;

                Vehicle *vehicle = new Vehicle();

                vehicle->name = kv.key().c_str();
                vehicle->maxSpeed = vehJson["maxSpeed"].as<int>();
                vehicle->acceleration = vehJson["acceleration"].as<float>();
                vehicle->weight = vehJson["weight"].as<int>();
                vehicle->steeringAngle = vehJson["steeringAngle"].as<float>();
                vehicle->width = vehJson["width"].as<int>();
                vehicle->height = vehJson["height"].as<int>();

                vehicles[i] = vehicle;
                
                i++;

                vehicles_size = i;

                Serial.println(vehicle->toString());
            }

            pubSubClient.unsubscribe(MQTT_SUB_TOPIC);
            gameStatus = 1;
        }
        
        delay(1000);

    } else if (gameStatus == 1) {

        int button = catchButton();        

        // Serial.print("Vhe : "); Serial.println(vehicle_index);

        if (button != -1) {
             Serial.print("button : "); Serial.println(button);
        }

        if (button == BLUE_BUTTON) {
            Serial.print("select Previous : "); Serial.println(button);

            vehicle_index--;
            if (vehicle_index < 0) {
                vehicle_index = vehicles_size - 1;
            }

            Serial.print("vehicle Index : ");  Serial.println(vehicle_index);
            
        } else if (button == GREEN_BUTTON) {

            vehicle_index++;
            if (vehicle_index >= vehicles_size) {
                vehicle_index = 0;
            }

            Serial.print("vehicle Index : ");  Serial.println(vehicle_index);
        }

        Heltec.display->clear();
        Heltec.display->drawString(20, 0, "Choice Vehicle");
        Heltec.display->drawString(0, 20, String(vehicle_index));
        Heltec.display->drawString(10, 20, vehicles[vehicle_index]->toString());
        Heltec.display->display();


        if (button == RED_BUTTON) {

            Heltec.display->clear();
            Heltec.display->drawString(0, 28, "Game started !");
            Heltec.display->display();

            Serial.println("register player");

            register_doc["uuid"] = uuid;
            register_doc["pseudo"] = "ladg";
            register_doc["controller"] = "controller";
            register_doc["vehicle"] = 1;
            register_doc["team"] = 1;

            String data;
            serializeJson(register_doc, data);

            if (!pubSubClient.publish(MQTT_REGISTER_TOPIC, data.c_str(), false)) {  // send json data to dynamoDbB topic
                Serial.println("ERROR??? :");
                Serial.println(pubSubClient.state());  //Connected '0'
            } else {
                Serial.println("player register upload");
                gameStatus = 2;
            }

            register_doc.clear();
        }

    } else {

        ReadGY521(gyRaw);
        ComputeAngle(gyRaw, PitchRollYaw);

        int power = PitchRollYaw[2];

        uint8_t button = catchButton();


        if (get_key(analogRead(GPIO_BUTTONS)) == RED_BUTTON) {
            power = 100;
        }

        if (get_key(analogRead(GPIO_BUTTONS)) == BLUE_BUTTON) {
            power = -100;
        }

        Vehicle *v = vehicles[vehicle_index];

        float _angle = 0;

        if (v->steeringAngle != -1) {
            _angle = map(PitchRollYaw[1], -100, 100,  -v->steeringAngle * RAD_TO_DEG, v->steeringAngle * RAD_TO_DEG);
        } else {
            _angle = PitchRollYaw[1];
        }

        register_doc["uuid"] = uuid;
        register_doc["angle"] = _angle * DEG_TO_RAD;
        register_doc["power"] = power;
        register_doc["buttons"]["banana"] = button == GREEN_BUTTON;
        register_doc["buttons"]["bomb"] = button == WHITE_BUTTON;
        register_doc["buttons"]["rocket"] = button == YELLOW_BUTTON;

        Heltec.display->clear();

        Heltec.display->drawString(0, 0, "angle");
        Heltec.display->drawString(50, 0, String(_angle));

        if (power >= 0) {
            Heltec.display->drawString(20, 15, "front");
        } else {
            Heltec.display->drawString(20, 15, "back");
        }

        Heltec.display->drawProgressBar(10, 30, 100, 20, abs(power));

        Heltec.display->display();



        String data;
        serializeJson(register_doc, data);

        if (!pubSubClient.publish(MQTT_CONTROL_TOPIC, data.c_str(), false)) {
            Serial.println("ERROR??? :");
            Serial.println(pubSubClient.state());  //Connected '0'
        }



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

        // Serial.println(catchButton());

        delay(100);
    }
}

bool connectToWIFI(int tryConnect, bool debug) {

    Serial.print("Waiting for connection to WiFi to : ");
    Serial.print(WIFI_SSID);

    Heltec.display->clear();
    Heltec.display->drawString(0, 28, "Try to connect wifi!");
    Heltec.display->display();


    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  //WiFi connection

    if (debug) {
        int i = 0;
        while (WiFi.status() != WL_CONNECTED) {

            if (i <= tryConnect) {
                delay(500);
                Serial.print('.');
                i++;
            } else {  //delay passed
                Serial.println("Delay passed");
                    Heltec.display->clear();
                    Heltec.display->drawString(0, 28, "Wifi disconnected!");
                    Heltec.display->display();

                return false;
            }
        }
        Serial.println("Connected");
    }

    Heltec.display->clear();
    Heltec.display->drawString(0, 28, "Wifi connected!");
    Heltec.display->display();

    return true;
}

bool connectToMqtt() {
    if (!pubSubClient.connected()) {
        Serial.print("PubSubClient connecting to : ");
        Serial.println(MQTT_ENDPOINT);

        Heltec.display->clear();
        Heltec.display->drawString(0, 28, "Mqtt Disconected");
        Heltec.display->display();

        while (!pubSubClient.connected()) {

            int error = pubSubClient.state();
            Serial.print(error);

            Heltec.display->clear();
            Heltec.display->drawString(0, 28, "Mqtt Disconected");
            Heltec.display->drawString(90, 28, String(error));
            Heltec.display->display();
            
            delay(100);
            Serial.print(".");



            pubSubClient.connect("ladg");
        }

        Serial.println(" connected");
        pubSubClient.subscribe(MQTT_SUB_TOPIC);

        Heltec.display->clear();
        Heltec.display->drawString(0, 28, "Mqtt connected!");
        Heltec.display->display();
    }


    pubSubClient.loop();
    return true;
}

void initGame() {
    if (WiFi.status() == WL_CONNECTED) {}
}

int catchButton() {

    adc_key_in = analogRead(GPIO_BUTTONS);  // read the value from the sensor

    key = get_key(adc_key_in);  // convert into key press

    if (key != oldkey)  // if keypress is detected
    {
        delay(50);                              // wait for debounce time
        adc_key_in = analogRead(GPIO_BUTTONS);  // read the value from the sensor
        key = get_key(adc_key_in);              // convert into key press
        if (key != oldkey) {
            oldkey = key;
            if (key >= 0) {
                return key;
            }
        }
    }
    return -1;
}

void ReadGY521(int16_t *gyRaw) {

    // Init du module GY-521
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    byte error = Wire.requestFrom(MPU, 14, true);

    if (error != 14) {
        do {
            Wire.beginTransmission(MPU);
            Wire.write(0X6B);
            Wire.write(0);
            byte error = Wire.endTransmission(true);

            delay(100);
            Serial.print("error : ");
            Serial.println(error);
        } while (error != 0);
    }

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

int get_key(unsigned int input) {
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

    String messageTemp;

    for (int i = 0; i < length; i++) {
        // Serial.print((char)message[i]);
        messageTemp += (char)message[i];
    }

    if (String(topic) == MQTT_SUB_TOPIC) {
        deserializeJson(properties_doc, messageTemp.c_str());
    }
}