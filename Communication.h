#pragma once

#include <Wire.h>

// The addresses each arduino use when seting up i2c communication.
const int MONITORING_ADDRESS = 0;
const int DISPLAY_ADDRESS    = 1;
const int OUTPUT_ADDRESS     = 2;

// data is transfered in arrays. These constants store the indicies of each piece of data.
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

// Transmit each piece of data to the arduino with a particular address.
inline bool TransmitData(const int& address, int* data, const size_t& numElements) {
    Wire.beginTransmission(address);
    for (int dataID = 0; dataID < numElements; dataID++) {
        // First, a byte is sent which describes which piece of data is being sent.
        Wire.write(dataID);
        // Then the actual data is sent.
        Wire.write(data[dataID]);
    }
    Wire.endTransmission();

    return true;
}

// Updates data. Returns true of false depending on if there was an error (false)
// or success (true)
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
            // Invalid data id.
            error = true;
        }
    }
    return !error;
}