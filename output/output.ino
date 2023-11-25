#include "Communication.h"

int outputData[(int)OutputDataIDs::NUM];
int& fanSpeed   = outputData[(int)OutputDataIDs::FAN_SPEED];
int& heaterTemp = outputData[(int)OutputDataIDs::HEATER_TEMPERATURE];

void setup() {
    SetupCommunication(OUTPUT_ADDRESS);
    Wire.onReceive(onReceive);
    Serial.begin(9600);
}

void onReceive(int) {
    ReceiveData(outputData, (size_t)OutputDataIDs::NUM);
}

void loop() {
    Serial.write("Fan Speed: ");
    Serial.println(fanSpeed);
    Serial.write("Heater Temp: ");
    Serial.println(heaterTemp);
}
