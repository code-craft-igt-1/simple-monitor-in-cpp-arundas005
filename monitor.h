#pragma once
#include <string>

int vitalsOk(float temperature, float pulseRate, float spo2);
bool isVitalsInNormalRange(float value, float lowerLimit, float upperLimit);
void alert(const std::string& alertMessage);
