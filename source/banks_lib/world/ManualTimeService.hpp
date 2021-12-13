//
// Created by wasd on 13.12.2021.
//
#pragma once

#include <banks_lib/world/ITimeService.hpp>

namespace banks {

class ManualTimeService : public ITimeService {
 public:
  using Ptr = std::shared_ptr<ManualTimeService>;

  explicit ManualTimeService() : ITimeService() {
  }

  bool Tick() override {
    ++time_;

    return true;
  }
};

}  // namespace banks
