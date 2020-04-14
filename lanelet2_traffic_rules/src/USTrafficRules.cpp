#include "USTrafficRules.h"
#include <lanelet2_core/Forward.h>
#include <lanelet2_core/primitives/BasicRegulatoryElements.h>
#include <lanelet2_core/utility/Units.h>
#include "Exceptions.h"
#include "TrafficRulesFactory.h"

using namespace std::string_literals;

namespace lanelet {
namespace traffic_rules {

namespace {
RegisterTrafficRules<USVehicle> gvRules(Locations::UnitedStates, Participants::Vehicle);
RegisterTrafficRules<USPedestrian> gpRules(Locations::UnitedStates, Participants::Pedestrian);
RegisterTrafficRules<USBicycle> gbRules(Locations::UnitedStates, Participants::Bicycle);

Velocity trafficSignToVelocity(const std::string& typeString) {
  using namespace lanelet::units::literals;
  const static std::map<std::string, Velocity> StrToVelocity{
      {"us-r2", 45_mph},      {"us-r2-5", 5_mph},     {"us-r2-10", 10_mph},   {"us-r2-15", 15_mph},
      {"us-r2-20", 20_mph},   {"us-r2-26", 25_mph},   {"us-r2-30", 30_mph},   {"us-r2-35", 35_mph},
      {"us-r2-40", 40_mph},   {"us-r2-45", 45_mph},   {"us-r2-50", 50_mph},   {"us-r2-55", 55_mph},
      {"us-r2-60", 60_mph},   {"us-r2-65", 65_mph},   {"us-r2-70", 70_mph},   {"us-r2-75", 75_mph},
      {"us-r2-80", 80_mph}};
  try {
    return StrToVelocity.at(typeString);
  } catch (std::out_of_range&) {
    // try to interpret typeString directly as velocity
    Attribute asAttribute(typeString);
    auto velocity = asAttribute.asVelocity();
    if (!!velocity) {
      return *velocity;
    }
    throw lanelet::InterpretationError("Unable to interpret the velocity information from " + typeString);
  }
}
}  // namespace

Optional<SpeedLimitInformation> USVehicle::speedLimit(const RegulatoryElementConstPtrs& regelems) const {
  for (auto& regelem : regelems) {
    auto speedLimit = std::dynamic_pointer_cast<const SpeedLimit>(regelem);
    if (!!speedLimit) {
      return SpeedLimitInformation{trafficSignToVelocity(speedLimit->type()), true};
    }
  }
  return {};
}

CountrySpeedLimits usSpeedLimits() {
  using namespace units::literals;
  return {{25_mph}, {55_mph}, {55_mph, false}, {70_mph, false}, {4_mph}, {3_mph}, {12_mph}};
}

}  // namespace traffic_rules
}  // namespace lanelet
