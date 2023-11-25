#pragma once

#include <Wire.h>

const int MONITORING_ADDRESS = 0;
const int DISPLAY_ADDRESS    = 1;
const int OUTPUT_ADDRESS     = 2;

enum class MonitoringDataIDs {
    TEMPERATURE,
    MOISTURE,
    LIGHT,

    NUM
};

enum class OutputDataIDs {
    FAN_SPEED,
    HEATER_TEMPERATURE,

    NUM
};

inline void SetupCommunication(const int& address) {
    Wire.begin(address);
}

inline bool TransmitData(const int& address, int* data, const size_t& numElements) {
    Wire.beginTransmission(address);
    for (int dataID = 0; dataID < numElements; dataID++) {
        Wire.write(dataID);
        Wire.write(data[dataID]);
    }
    Wire.endTransmission();

    return true;
}

inline bool ReceiveData(int* data, const size_t& numElements) {
    if (Wire.available() % 2 != 0) {
        // Error in transmission!
        return false;
    }

    bool error = false;
    while (Wire.available() > 0) {
        int dataID = Wire.read();
        if (0 <= dataID && dataID < numElements) {
            data[dataID] = Wire.read();
        }
        else {
            error = true;
        }
    }
    return !error;
}