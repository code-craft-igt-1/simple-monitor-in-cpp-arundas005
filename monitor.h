#pragma once
#include <string>
#include <map>
#include <vector>
#include "./alertMessages.h"
#include "./VitalParameterInfo.h"

struct HealthParameter {
  VitalType vitalType;
  VitalUnit unit;
  float vitalValue;
};

struct HealthParameterLimitsAndTolerence {
  VitalType vitalType;
  float lowerLimit;
  float upperLimit;
  float warningTolerance;
};

struct HealthParameterLimits{
  float lowerLimit;
  float warningLowerLimit;
  float normallimit;
  float warningUpperLimit;
};

extern std::map<VitalType, HealthParameterLimits> healthParameterRanges;

void createHealthParameterRanges(const std::vector<HealthParameterLimitsAndTolerence>&
                                                            healthParamLimitsNTolerence);
void convertCelsiusToFarenheit(HealthParameter* temperaturearameter);
HealthParameterLimits getHealthParamLimits(VitalType vitalType);
int vitalsOk(std::vector<HealthParameter> healthParams);
VITAL_RANGE_CLASSIFICATION getVitalCondition(HealthParameter healthParam,
                                             HealthParameterLimits healthParamLimits);
void alert(const std::wstring& message);

