//
// Created by wasd on 13.12.2021.
//
#pragma once

#include <memory>

#include <banks_lib/types/types.hpp>

namespace banks {

class ITimeService {
 public:
  using Ptr = std::shared_ptr<ITimeService>;

  explicit ITimeService() : time_(0) {
  }

  Time Now() {
    return time_;
  }

  virtual bool Tick() = 0;

 protected:
  Time time_;
};

}  // namespace banks
