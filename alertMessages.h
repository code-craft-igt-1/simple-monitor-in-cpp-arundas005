#pragma once
#include <string>
#include <vector>
#include <map>
#include "./VitalParameterInfo.h"

enum class LANGUAGE {
  ENGLISH,
  FRENCH,
  SPANISH
};

extern std::map<VITAL_RANGE_CLASSIFICATION, std::wstring> TemperaureRangeToMessage;
extern std::map<VITAL_RANGE_CLASSIFICATION, std::wstring> PulseRateRangeToMessage;
extern std::map<VITAL_RANGE_CLASSIFICATION, std::wstring> SPO2RangeToMessage;
extern const LANGUAGE CURRENT_LANGUAGE;
extern const std::vector<std::vector<std::wstring>> alertMessages;

std::wstring getAlertMessage(VitalType vitalType, VITAL_RANGE_CLASSIFICATION vitalRangeClassification);

