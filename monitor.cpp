#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include "./monitor.h"

using std::wcout, std::vector, std::pair, std::wstring, \
std::flush, std::this_thread::sleep_for, std::chrono::seconds, std::endl;

std::map<VitalType, HealthParameterLimits> healthParameterRanges;

vector<HealthParameter> healthParams = {
  /*  Type                        Unit              Value */
  {VitalType::TEMPERATURE,   VitalUnit::FARENHEIT,   98.0f},
  {VitalType::PULSE_RATE,    VitalUnit::BPM,         80.0f},
  {VitalType::SPO2,          VitalUnit::PERCENT,     95.0f},
};

vector<HealthParameterLimitsAndTolerence> healthParameterLimitsAndTolerence = {
  {VitalType::TEMPERATURE, 95.0f, 102.0f, 1.5f},
  {VitalType::PULSE_RATE, 60.0f, 100.0f, 5.0f},
  {VitalType::SPO2, 90.0f, 100.0f, 1.2f}
};

void convertCelsiusToFarenheit(HealthParameter* temperaturearameter) {
  if (temperaturearameter->vitalType == VitalType::TEMPERATURE &&
      temperaturearameter->unit == VitalUnit::CELSIUS) {
    temperaturearameter->vitalValue = (temperaturearameter->vitalValue * 9.0f / 5.0f) + 32;
    temperaturearameter->unit = VitalUnit::FARENHEIT;
  }
}

void setVitalLimits(HealthParameterLimits* healthParamLimits,
                    const vector<HealthParameterLimitsAndTolerence>&
                                         healthParamLimitsNTolerence,
                                                           int index) {
  healthParamLimits->lowerLimit = healthParamLimitsNTolerence[index].lowerLimit;
  float tolerance = healthParamLimitsNTolerence[index].upperLimit *
  healthParamLimitsNTolerence[index].warningTolerance / 100.0f;
  healthParamLimits->warningLowerLimit = healthParamLimitsNTolerence[index].lowerLimit +
                                                                                  tolerance;
  healthParamLimits->normallimit = healthParamLimitsNTolerence[index].upperLimit -
                                                                            tolerance;
  healthParamLimits->warningUpperLimit = healthParamLimitsNTolerence[index].upperLimit;
}

void createHealthParameterRanges(const vector<HealthParameterLimitsAndTolerence>&
                                                       healthParamLimitsNTolerence) {
  for (int i = 0; i < healthParamLimitsNTolerence.size(); i++) {
    switch (healthParamLimitsNTolerence[i].vitalType) {
      case VitalType::TEMPERATURE: {
        HealthParameterLimits temperatureParamLimits;
        setVitalLimits(&temperatureParamLimits, healthParamLimitsNTolerence, i);
        healthParameterRanges[VitalType::TEMPERATURE] = temperatureParamLimits;
        break;
      }
      case VitalType::PULSE_RATE: {
        HealthParameterLimits pulseRateParamLimits;
        setVitalLimits(&pulseRateParamLimits, healthParamLimitsNTolerence, i);
        healthParameterRanges[VitalType::PULSE_RATE] = pulseRateParamLimits;
        break;
      }
      case VitalType::SPO2: {
        HealthParameterLimits spo2ParamLimits;
        setVitalLimits(&spo2ParamLimits, healthParamLimitsNTolerence, i);
        healthParameterRanges[VitalType::SPO2] = spo2ParamLimits;
        break;
      }
    }
  }
}

HealthParameterLimits getHealthParamLimits(VitalType vitalType) {
  return healthParameterRanges[vitalType];
}

int vitalsOk(vector<HealthParameter> _healthParams) {
  for (int i = 0; i < _healthParams.size(); i++) {
    VITAL_RANGE_CLASSIFICATION vitalCondition = getVitalCondition(_healthParams[i],
                                              getHealthParamLimits(_healthParams[i].vitalType));
    if (VITAL_RANGE_CLASSIFICATION::NORMAL != vitalCondition) {
      alert(getAlertMessage(_healthParams[i].vitalType, vitalCondition));
      return 0;
    }
  }
  return 1;
}

VITAL_RANGE_CLASSIFICATION getVitalCondition(HealthParameter healthParam,
                                      HealthParameterLimits healthParamLimits) {
  convertCelsiusToFarenheit(&healthParam);
  int index = static_cast<int>(healthParam.vitalType);
  healthParamLimits.lowerLimit = healthParameterLimitsAndTolerence[index].lowerLimit;
  float tolerance = healthParameterLimitsAndTolerence[index].upperLimit *
  healthParameterLimitsAndTolerence[index].warningTolerance / 100.0f;
  healthParamLimits.warningLowerLimit = healthParameterLimitsAndTolerence[index].lowerLimit +
                                                                                  tolerance;
  healthParamLimits.normallimit = healthParameterLimitsAndTolerence[index].upperLimit - tolerance;
  healthParamLimits.warningUpperLimit = healthParameterLimitsAndTolerence[index].upperLimit;
  std::map<float, VITAL_RANGE_CLASSIFICATION> ranges = {
    {healthParamLimits.lowerLimit, VITAL_RANGE_CLASSIFICATION::LOW},
    {healthParamLimits.warningLowerLimit, VITAL_RANGE_CLASSIFICATION::NEAR_LOW},
    {healthParamLimits.normallimit, VITAL_RANGE_CLASSIFICATION::NORMAL},
    {healthParamLimits.warningUpperLimit, VITAL_RANGE_CLASSIFICATION::NEAR_HIGH}
  };

  for (const auto& range : ranges) {
    if (healthParam.vitalValue < range.first) {
      return range.second;
    }
  }
  return VITAL_RANGE_CLASSIFICATION::HIGH;
}

void alert(const wstring& message) {
  const int REPEAT_COUNT = 6;
  const int SLEEP_INTERVAL_SECONDS = 1;
  wcout << message << endl;
  for (int i = 0; i < REPEAT_COUNT; i++) {
    wcout << L"\r* " << flush;
    sleep_for(seconds(SLEEP_INTERVAL_SECONDS));
    wcout << L"\r *" << flush;
    sleep_for(seconds(SLEEP_INTERVAL_SECONDS));
  }
}
