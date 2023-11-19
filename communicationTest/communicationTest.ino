#include "Communication.h"

int inputData[(int)MonitoringDataIDs::COUNT];
int& temperature = inputData[(int)MonitoringDataIDs::TEMPERATURE];
int& moisture    = inputData[(int)MonitoringDataIDs::MOISTURE];
int& light       = inputData[(int)MonitoringDataIDs::LIGHT];

int outputData[(int)OutputDataIDs::COUNT];
int& fanSpeed   = outputData[(int)OutputDataIDs::FAN_SPEED];
int& heaterTemp = outputData[(int)OutputDataIDs::HEATER_TEMPERATURE];

void setup() {
    SetupCommunication(DISPLAY_ADDRESS);
    temperature = 10;
    moisture = 4;
    light = 6;
}

void loop() {
    ReceiveData(inputData);

    if (temperature > 20) {
        fanSpeed = temperature - 20;
    }
    else {
        heaterTemp = -(temperature - 20);
    }

    TransmitData(OUTPUT_ADDRESS, outputData);
}
