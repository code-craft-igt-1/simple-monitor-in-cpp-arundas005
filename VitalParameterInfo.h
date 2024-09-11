#pragma once

enum class VitalType {
  TEMPERATURE,
  PULSE_RATE,
  SPO2
};

enum class VitalUnit {
  CELSIUS,
  FARENHEIT,
  BPM,
  PERCENT
};

enum class VITAL_RANGE_CLASSIFICATION {
    LOW,
    NEAR_LOW,
    NORMAL,
    NEAR_HIGH,
    HIGH,
    NUM_OF_CLASSIFICATIONS
};