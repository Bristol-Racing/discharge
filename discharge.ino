#include "sensors/ADC_Current.hpp"
#include "sensors/voltage.hpp"
#include "sensors/sensorManager.hpp"

#define VOLTAGE_VIN A2

const int time_per_reading = 100;
const int readings = 10;

int currentReadings = 0;
long reading = 0;

int sensorCount = 2;
Sensor::CurrentSensor currentSensor;
Sensor::VoltageSensor voltageSensor(VOLTAGE_VIN, 68.677);

Sensor::SensorManager manager(sensorCount, time_per_reading * readings);

void setup() {
    Serial.begin(57600);

    currentSensor.setup();
    currentSensor.setTickRate(time_per_reading);
    currentSensor.setReadRate(1000);

    voltageSensor.setReadRate(1000);

    manager.addSensor(&currentSensor);
    manager.addSensor(&voltageSensor);
    manager.setReadCallback(&readCallback);
}

void loop() {
    manager.spin();
}

void readCallback(double * results) {
    for (int i = 0; i < sensorCount; i++) {
        if (i > 0) {
            Serial.print(",");
        }
        Serial.print(results[i]);
    }
    Serial.println();
}
