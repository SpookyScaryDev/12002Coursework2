#include "Communication.h"

int outputData[(int)OutputDataIDs::COUNT];
int& fanSpeed   = outputData[(int)OutputDataIDs::FAN_SPEED];
int& heaterTemp = outputData[(int)OutputDataIDs::HEATER_TEMPERATURE];

void setup() {
    SetupCommunication(OUTPUT_ADDRESS);
    Serial.begin(9600);
}

void loop() {
    ReceiveData(outputData);
    Serial.write("Fan Speed:");
    Serial.write(fanSpeed);
    Serial.write("Heater Temp:");
    Serial.write(heaterTemp);
}
