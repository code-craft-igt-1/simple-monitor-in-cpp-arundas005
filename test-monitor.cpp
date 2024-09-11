#include "./monitor.h"
#include "gtest/gtest.h"

using std::vector;

class MonitorTest : public ::testing::Test {
protected:
  vector<HealthParameter> healthParamsforTest;

  void SetUp() override {
    healthParamsforTest = {
      /*  Type                        Unit              Value   */
      {VitalType::TEMPERATURE,   VitalUnit::FARENHEIT,   98.0f },
      {VitalType::PULSE_RATE,    VitalUnit::BPM,         80.0f },
      {VitalType::SPO2,          VitalUnit::PERCENT,     95.0f }
    };
  }
};

TEST_F(MonitorTest, Hyperthermia) {
  healthParamsforTest[0].vitalValue = 103.0f;
  ASSERT_FALSE(vitalsOk(healthParamsforTest));
}

TEST_F(MonitorTest, ApprochingHyperthermia) {
  healthParamsforTest[0].vitalValue = 101.0f;
  ASSERT_FALSE(vitalsOk(healthParamsforTest));
}

TEST_F(MonitorTest, ApprochingHypothermia) {
  healthParamsforTest[0].vitalValue = 96.0f;
  ASSERT_FALSE(vitalsOk(healthParamsforTest));
}

TEST_F(MonitorTest, Hypothermia) {
  healthParamsforTest[0].vitalValue = 94.5f;
  ASSERT_FALSE(vitalsOk(healthParamsforTest));
}

TEST_F(MonitorTest, HyperthermiaTemperatureInCelsius) {
  healthParamsforTest[0].vitalValue = 40.0f;
  healthParamsforTest[0].unit = VitalUnit::CELSIUS;
  ASSERT_FALSE(vitalsOk(healthParamsforTest));
}

TEST_F(MonitorTest, Tachycardia) {
  healthParamsforTest[1].vitalValue = 101.0f;
  ASSERT_FALSE(vitalsOk(healthParamsforTest));
}

TEST_F(MonitorTest, ApprochingTachycardia) {
  healthParamsforTest[1].vitalValue = 96.0f;
  ASSERT_FALSE(vitalsOk(healthParamsforTest));
}

TEST_F(MonitorTest, ApprochingBradycardia) {
  healthParamsforTest[1].vitalValue = 64.0f;
  ASSERT_FALSE(vitalsOk(healthParamsforTest));
}

TEST_F(MonitorTest, Bradycardia) {
  healthParamsforTest[1].vitalValue = 59.0f;
  ASSERT_FALSE(vitalsOk(healthParamsforTest));
}

TEST_F(MonitorTest, Hypoxemia) {
  healthParamsforTest[2].vitalValue = 89.0f;
  ASSERT_FALSE(vitalsOk(healthParamsforTest));
}

TEST_F(MonitorTest, ApprochingHypoxemia) {
  healthParamsforTest[2].vitalValue = 91.0f;
  ASSERT_FALSE(vitalsOk(healthParamsforTest));
}

TEST_F(MonitorTest, ApprochingHyperoxemia) {
  healthParamsforTest[2].vitalValue = 99.9f;
  ASSERT_FALSE(vitalsOk(healthParamsforTest));
}

TEST_F(MonitorTest, Hyperoxemia) {
  healthParamsforTest[2].vitalValue = 100.1f;
  ASSERT_FALSE(vitalsOk(healthParamsforTest));
}

TEST_F(MonitorTest, VitalsInNormalRange) {
  healthParamsforTest[0].vitalValue = 98.1f;
  healthParamsforTest[1].vitalValue = 70.0f;
  healthParamsforTest[2].vitalValue = 98.0f;
  ASSERT_TRUE(vitalsOk(healthParamsforTest));
}
