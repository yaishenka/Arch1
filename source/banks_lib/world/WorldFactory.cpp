//
// Created by wasd on 13.12.2021.
//

#include <banks_lib/world/WorldFactory.hpp>
#include <banks_lib/world/ManualTimeService.hpp>
#include <banks_lib/logger/ConsoleLogger.hpp>
#include <banks_lib/world/Simulation.hpp>

using namespace banks;

IWorld::Ptr WorldFactory::CreateSimulation() {
  ManualTimeService::Ptr time_service = std::make_shared<ManualTimeService>();
  ILogger::Ptr logger = std::make_shared<ConsoleLogger>();

  return std::make_shared<Simulation>(time_service, logger);
}
