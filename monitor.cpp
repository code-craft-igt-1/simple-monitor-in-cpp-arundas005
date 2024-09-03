#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
#include <string>

using std::cout, std::vector, std::pair, std::string, \
std::flush, std::this_thread::sleep_for, std::chrono::seconds, std::endl;

enum class VitalType {
  TEMPERATURE,
  PULSE_RATE,
  SPO2
};

vector<pair<float, float>> vitalLimits = {
  {95.0f, 102.0f},
  {60.0f, 100.0f},
  {90.0f, 100.0f}
};

auto getErrorMessage(VitalType vitalTypes) {
  vector<string> alertMessages = {"Temperature is critical !!",
                                  "Pulse Rate out of range !!",
                                  "Oxygen Saturation low !!"};
  return alertMessages[static_cast<int>(vitalTypes)];
}

int vitalsOk(float temperature, float pulseRate, float spo2) {
  vector<VitalType> vitals = {VitalType::TEMPERATURE, VitalType::PULSE_RATE, VitalType::SPO2};
  vector<float> vitalValues = {temperature, pulseRate, spo2};
  for (int i = 0; i < vitals.size(); i++) {
    if (!isVitalsInNormalRange(vitalValues[i], vitalLimits[i].first, vitalLimits[i].second)) {
      alert(getErrorMessage(vitals[i]));
      return 0;
    }
  }
  return 1;
}

bool isVitalsInNormalRange(float value, float lowerLimit, float upperLimit) {
  return value >= lowerLimit && value <= upperLimit;
}

void alert(const string& vitalName) {
  const int REPEAT_COUNT = 6;
  const int SLEEP_INTERVAL_SECONDS = 1;
  cout << vitalName << endl;
  for (int i = 0; i < REPEAT_COUNT; i++) {
    cout << "\r* " << flush;
    sleep_for(seconds(SLEEP_INTERVAL_SECONDS));
    cout << "\r *" << flush;
    sleep_for(seconds(SLEEP_INTERVAL_SECONDS));
  }
}
