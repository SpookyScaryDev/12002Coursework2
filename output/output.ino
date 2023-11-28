#include <Servo.h>
#include "Communication.h"

int outputData[(int)OutputDataIDs::NUM];
int& fanSpeed   = outputData[(int)OutputDataIDs::FAN_SPEED];
int& heaterTemp = outputData[(int)OutputDataIDs::HEATER_TEMPERATURE];

const int servoPin = 8;
const int motorPin = 9;

Servo servo;

void setup() {
    SetupCommunication(OUTPUT_ADDRESS);
    Wire.onReceive(onReceive);

    Serial.begin(9600);

    servo.attach(servoPin);
    servo.write(0);
}

void onReceive(int) {
    // Update input data.
    ReceiveData(outputData, (size_t)OutputDataIDs::NUM);
}

void loop() {
    // Ensure inputs are in range, and if so output the information.
    if (0 <= fanSpeed <= 255) {
        // Set motor (fan) speed according to input.
        analogWrite(motorPin, fanSpeed);
    }
    if (0 <= heaterTemp <= 180) {
        // Move the servo arm to represent heater temperature.
        // 0 is is, 180 is max temperature.
        servo.write(heaterTemp);
    }
}
