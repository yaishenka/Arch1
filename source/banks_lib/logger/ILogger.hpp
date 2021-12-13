//
// Created by wasd on 12.12.2021.
//
#pragma once

#include <optional>
#include <string_view>
#include <memory>

#include <banks_lib/types/types.hpp>

namespace banks {

class ILogger {
public:
  using Ptr = std::shared_ptr<ILogger>;

  using ExtraInfo = std::optional<std::string_view>;

  virtual void LogWithdraw(Money delta, ExtraInfo extra_info = std::nullopt) = 0;
  virtual void LogRefill(Money delta, ExtraInfo extra_info = std::nullopt) = 0;

  virtual void LogError(std::string_view reason, ExtraInfo extra_info = std::nullopt) = 0;
};

}
