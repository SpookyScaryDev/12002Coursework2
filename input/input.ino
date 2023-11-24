#include "Communication.h"

int inputData[(int)MonitoringDataIDs::COUNT];
int& temperature = inputData[(int)MonitoringDataIDs::TEMPERATURE];
int& moisture    = inputData[(int)MonitoringDataIDs::MOISTURE];
int& light       = inputData[(int)MonitoringDataIDs::LIGHT];

void setup() {
    SetupCommunication(MONITORING_ADDRESS);
}

void loop() {
  temperature = rand() % 40 - 20;
  moisture = rand() % 40 - 20;
  light = rand() % 10;

  TransmitData(DISPLAY_ADDRESS, inputData);
}
