#pragma once
#include <lanelet2_core/utility/Units.h>
#include "GenericTrafficRules.h"

namespace lanelet {
namespace traffic_rules {

CountrySpeedLimits usSpeedLimits();

class USVehicle : public GenericTrafficRules {
 public:
  using GenericTrafficRules::GenericTrafficRules;

  // using areas is disallowed for vehicles in normal driving mode
  bool canPass(const ConstArea& /*area*/) const override { return false; }

 protected:
  Optional<bool> canPass(const RegulatoryElementConstPtrs& /*regElems*/) const override { return {}; }
  const CountrySpeedLimits& countrySpeedLimits() const override { return speedLimits_; }
  Optional<SpeedLimitInformation> speedLimit(const RegulatoryElementConstPtrs& regelems) const override;

 private:
  CountrySpeedLimits speedLimits_{usSpeedLimits()};
};

class USPedestrian : public GenericTrafficRules {
 public:
  using GenericTrafficRules::GenericTrafficRules;

 protected:
  Optional<bool> canPass(const RegulatoryElementConstPtrs& /*regElems*/) const override { return {}; }
  const CountrySpeedLimits& countrySpeedLimits() const override { return speedLimits_; }
  Optional<SpeedLimitInformation> speedLimit(const RegulatoryElementConstPtrs& /*regelems*/) const override {
    return {};
  }

 private:
  CountrySpeedLimits speedLimits_{usSpeedLimits()};
};

class USBicycle : public GenericTrafficRules {
 public:
  using GenericTrafficRules::GenericTrafficRules;

 protected:
  Optional<bool> canPass(const RegulatoryElementConstPtrs& /*regElems*/) const override { return {}; }
  const CountrySpeedLimits& countrySpeedLimits() const override { return speedLimits_; }
  Optional<SpeedLimitInformation> speedLimit(const RegulatoryElementConstPtrs& /*regelems*/) const override {
    return {};
  }

 private:
  CountrySpeedLimits speedLimits_{usSpeedLimits()};
};
}  // namespace traffic_rules
}  // namespace lanelet
