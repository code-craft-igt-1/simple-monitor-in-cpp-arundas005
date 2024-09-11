#include "./alertMessages.h"

using std::wstring, std::vector, std::string, std::map;

const LANGUAGE CURRENT_LANGUAGE = LANGUAGE::SPANISH;
map<VITAL_RANGE_CLASSIFICATION, wstring> TemperaureRangeToMessage_EN = {
    {VITAL_RANGE_CLASSIFICATION::LOW, wstring(L"Patient experiencing hypothermia !!")},
    {VITAL_RANGE_CLASSIFICATION::NEAR_LOW, wstring(L"Patient approaching hypothermia !!")},
    {VITAL_RANGE_CLASSIFICATION::NORMAL, wstring(L"Patient temperature is normal !!")},
    {VITAL_RANGE_CLASSIFICATION::NEAR_HIGH, wstring(L"Patient approaching hyperthermia !!")},
    {VITAL_RANGE_CLASSIFICATION::HIGH, wstring(L"Patient experiencing hyperthermia !!")}
};
map<VITAL_RANGE_CLASSIFICATION, wstring> PulseRateRangeToMessage_EN = {
    {VITAL_RANGE_CLASSIFICATION::LOW, wstring(L"Patient experiencing bradycardia !!")},
    {VITAL_RANGE_CLASSIFICATION::NEAR_LOW, wstring(L"Patient approaching bradycardia !!")},
    {VITAL_RANGE_CLASSIFICATION::NORMAL, wstring(L"Patient pulse rate is normal !!")},
    {VITAL_RANGE_CLASSIFICATION::NEAR_HIGH, wstring(L"Patient approaching tachycardia !!")},
    {VITAL_RANGE_CLASSIFICATION::HIGH, wstring(L"Patient experiencing tachycardia !!")}
};
map<VITAL_RANGE_CLASSIFICATION, wstring> SPO2RangeToMessage_EN = {
    {VITAL_RANGE_CLASSIFICATION::LOW, wstring(L"Patient experiencing hypoxemia !!")},
    {VITAL_RANGE_CLASSIFICATION::NEAR_LOW, wstring(L"Patient approaching hypoxemia !!")},
    {VITAL_RANGE_CLASSIFICATION::NORMAL, wstring(L"Patient oxygen saturation is normal !!")},
    {VITAL_RANGE_CLASSIFICATION::NEAR_HIGH, wstring(L"Patient approaching hyperoxemia !!")},
    {VITAL_RANGE_CLASSIFICATION::HIGH, wstring(L"Patient experiencing hyperoxemia !!")}
};

map<VITAL_RANGE_CLASSIFICATION, wstring> TemperaureRangeToMessage_ES = {
    {VITAL_RANGE_CLASSIFICATION::LOW, wstring(L"¡El paciente experimenta hipotermia!!")},
    {VITAL_RANGE_CLASSIFICATION::NEAR_LOW, wstring(L"¡El paciente se acerca a la hipotermia!!")},
    {VITAL_RANGE_CLASSIFICATION::NORMAL, wstring(L"¡La temperatura del paciente es normal!!")},
    {VITAL_RANGE_CLASSIFICATION::NEAR_HIGH, wstring(L"¡El paciente se acerca a la hipertermia!!")},
    {VITAL_RANGE_CLASSIFICATION::HIGH, wstring(L"¡El paciente experimenta hipertermia!!")}
};
map<VITAL_RANGE_CLASSIFICATION, wstring> PulseRateRangeToMessage_ES = {
    {VITAL_RANGE_CLASSIFICATION::LOW, wstring(L"¡El paciente experimenta bradicardia!!")},
    {VITAL_RANGE_CLASSIFICATION::NEAR_LOW, wstring(L"¡El paciente se acerca a la bradicardia!!")},
    {VITAL_RANGE_CLASSIFICATION::NORMAL, wstring(L"¡La frecuencia del pulso del paciente es normal!!")},
    {VITAL_RANGE_CLASSIFICATION::NEAR_HIGH, wstring(L"¡El paciente se acerca a la taquicardia!!")},
    {VITAL_RANGE_CLASSIFICATION::HIGH, wstring(L"¡El paciente experimenta taquicardia!!")}
};
map<VITAL_RANGE_CLASSIFICATION, wstring> SPO2RangeToMessage_ES = {
    {VITAL_RANGE_CLASSIFICATION::LOW, wstring(L"¡El paciente experimenta hipoxemia!!")},
    {VITAL_RANGE_CLASSIFICATION::NEAR_LOW, wstring(L"¡El paciente se acerca a la hipoxemia!!")},
    {VITAL_RANGE_CLASSIFICATION::NORMAL, wstring(L"¡La saturación de oxígeno del paciente es normal!!")},
    {VITAL_RANGE_CLASSIFICATION::NEAR_HIGH, wstring(L"¡El paciente se acerca a la hiperoxemia!!")},
    {VITAL_RANGE_CLASSIFICATION::HIGH, wstring(L"¡El paciente experimenta hiperoxemia!!")}
};

map<VitalType, map<VITAL_RANGE_CLASSIFICATION, wstring>> alertMessagesMap_EN = {
    {VitalType::TEMPERATURE, TemperaureRangeToMessage_EN},
    {VitalType::PULSE_RATE, PulseRateRangeToMessage_EN},
    {VitalType::SPO2, SPO2RangeToMessage_EN}
};

map<VitalType, map<VITAL_RANGE_CLASSIFICATION, wstring>> alertMessagesMap_ES = {
    {VitalType::TEMPERATURE, TemperaureRangeToMessage_ES},
    {VitalType::PULSE_RATE, PulseRateRangeToMessage_ES},
    {VitalType::SPO2, SPO2RangeToMessage_ES}
};

map<LANGUAGE, map<VitalType, map<VITAL_RANGE_CLASSIFICATION, wstring>>> alertMessagesMap = {
    {LANGUAGE::ENGLISH, alertMessagesMap_EN},
    {LANGUAGE::SPANISH, alertMessagesMap_ES}
};

wstring getAlertMessage(VitalType vitalType, VITAL_RANGE_CLASSIFICATION vitalRangeClassification) {
    return alertMessagesMap[CURRENT_LANGUAGE][vitalType][vitalRangeClassification];
}
