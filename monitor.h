#pragma once

int vitalsOk(float temperature, float pulseRate, float spo2);
bool vitalsInNormalRange(float value, float lowerLimit, float upperLimit);
void alert(const char* vitalName);