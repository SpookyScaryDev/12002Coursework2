#include "Communication.h"

int inputData[(int)MonitoringDataIDs::NUM];
int& temperature = inputData[(int)MonitoringDataIDs::TEMPERATURE];
int& moisture    = inputData[(int)MonitoringDataIDs::MOISTURE];
int& light       = inputData[(int)MonitoringDataIDs::LIGHT];

int outputData[(int)OutputDataIDs::NUM];
int& fanSpeed   = outputData[(int)OutputDataIDs::FAN_SPEED];
int& heaterTemp = outputData[(int)OutputDataIDs::HEATER_TEMPERATURE];

void setup() {
    SetupCommunication(DISPLAY_ADDRESS);
    Wire.onReceive(onReceive);
}

void onReceive(int) {
    ReceiveData(inputData, (size_t)MonitoringDataIDs::NUM);
}

void loop() {
    if (temperature > 20) {
        fanSpeed = temperature - 20;
    }
    else {
        heaterTemp = -(temperature - 20);
    }

    TransmitData(OUTPUT_ADDRESS, outputData, (size_t)OutputDataIDs::NUM);
}
