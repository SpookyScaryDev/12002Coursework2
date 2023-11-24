#pragma once

#include <Wire.h>

const int MONITORING_ADDRESS = 0;
const int DISPLAY_ADDRESS    = 1;
const int OUTPUT_ADDRESS     = 2;

enum class MonitoringDataIDs {
    TEMPERATURE,
    MOISTURE,
    LIGHT,

    COUNT
};

enum class OutputDataIDs {
    FAN_SPEED,
    HEATER_TEMPERATURE,

    COUNT
};

inline void SetupCommunication(int address) {
    Wire.begin(address);
}

inline bool TransmitData(int address, int* data) {
    Wire.beginTransmission(address);
    for (int dataID = 0; dataID <= sizeof(data) / sizeof(data[0]); dataID++) {
        Wire.write(dataID);
        Wire.write(data[dataID]);
    }
    Wire.endTransmission();
}

inline bool ReceiveData(int* data) {
    if (Wire.available() % 2 != 0) {
        // Error in transmission!
        return false;
    }

    bool error = false;
    while (Wire.available() > 0) {
        int dataID = Wire.read();
        if (0 <= dataID && dataID < sizeof(data) / sizeof(data[0])) {
            data[dataID] = Wire.read();
        }
        else {
            error = true;
        }
    }
    return !error;
}