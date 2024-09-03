#include "./monitor.h"

#include "gtest/gtest.h"

TEST(Monitor, TemperatureCritical) {
  ASSERT_FALSE(vitalsOk(103, 70, 98));
}

TEST(Monitor, PulseRateOutOfRange) {
  ASSERT_FALSE(vitalsOk(102, 101, 98));
}

TEST(Monitor, OxygenSaturationLow) {
  ASSERT_FALSE(vitalsOk(98, 99, 89));
}

TEST(Monitor, VitalsInNormalRange) {
  ASSERT_TRUE(vitalsOk(98.1, 70, 98));
}

