#include "./alertMessages.h"

using std::wstring, std::vector, std::string, std::map;

const LANGUAGE CURRENT_LANGUAGE = LANGUAGE::ENGLISH;
map<VITAL_RANGE_CLASSIFICATION, wstring> TemperaureRangeToMessage = {
    {VITAL_RANGE_CLASSIFICATION::LOW, wstring(L"Patient experiencing hypothermia !!")},
    {VITAL_RANGE_CLASSIFICATION::NEAR_LOW, wstring(L"Patient approching hypothermia !!")},
    {VITAL_RANGE_CLASSIFICATION::NORMAL, wstring(L"Patient temperature is normal !!")},
    {VITAL_RANGE_CLASSIFICATION::NEAR_HIGH, wstring(L"Patient approching hyperthermia !!")},
    {VITAL_RANGE_CLASSIFICATION::HIGH, wstring(L"Patient experiencing hyperthermia !!")}
};
map<VITAL_RANGE_CLASSIFICATION, std::wstring> PulseRateRangeToMessage = {
    {VITAL_RANGE_CLASSIFICATION::LOW, wstring(L"Patient experiencing bradycardia !!")},
    {VITAL_RANGE_CLASSIFICATION::NEAR_LOW, wstring(L"Patient approching bradycardia !!")},
    {VITAL_RANGE_CLASSIFICATION::NORMAL, wstring(L"Patient pulse rate is normal !!")},
    {VITAL_RANGE_CLASSIFICATION::NEAR_HIGH, wstring(L"Patient approching tachycardia !!")},
    {VITAL_RANGE_CLASSIFICATION::HIGH, wstring(L"Patient experiencing tachycardia !!")}
};
map<VITAL_RANGE_CLASSIFICATION, wstring> SPO2RangeToMessage = {
    {VITAL_RANGE_CLASSIFICATION::LOW, wstring(L"Patient experiencing hypoxemia !!")},
    {VITAL_RANGE_CLASSIFICATION::NEAR_LOW, wstring(L"Patient approching hypoxemia !!")},
    {VITAL_RANGE_CLASSIFICATION::NORMAL, wstring(L"Patient oxygen saturation is normal !!")},
    {VITAL_RANGE_CLASSIFICATION::NEAR_HIGH, wstring(L"Patient approching hyperoxemia !!")},
    {VITAL_RANGE_CLASSIFICATION::HIGH, wstring(L"Patient experiencing hyperoxemia !!")}
};

std::map<VitalType, std::map<VITAL_RANGE_CLASSIFICATION, std::wstring>> alertMessagesMap = {
    {VitalType::TEMPERATURE, TemperaureRangeToMessage},
    {VitalType::PULSE_RATE, PulseRateRangeToMessage},
    {VitalType::SPO2, SPO2RangeToMessage}
};

wstring getAlertMessage(VitalType vitalType, VITAL_RANGE_CLASSIFICATION vitalRangeClassification) {
    return alertMessagesMap[vitalType][vitalRangeClassification];
}
