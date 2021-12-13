//
// Created by wasd on 13.12.2021.
//

#pragma once

#include <banks_lib/world/IWorld.hpp>

namespace banks {

class Simulation : public IWorld {
 public:
  explicit Simulation(ITimeService::Ptr time_service, ILogger::Ptr logger);

 protected:
  bool ProcessEvents(size_t step) override;
  void MakeStep() override;

 private:
  void ProcessNew();
  void ProcessNow();
  bool ProcessEnd();
  void ProcessActor();
  void ProcessFinish();

  std::ostream& output_;
  std::istream& input_;
};

}  // namespace banks
