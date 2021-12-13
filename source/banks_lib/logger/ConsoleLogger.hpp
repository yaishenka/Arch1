//
// Created by wasd on 12.12.2021.
//
#pragma once

#include <iostream>

#include <banks_lib/logger/ILogger.hpp>

namespace banks {

class ConsoleLogger : public ILogger {
 public:
  void LogWithdraw(Money delta, ExtraInfo extra_info = std::nullopt) override;
  void LogRefill(Money delta, ExtraInfo extra_info = std::nullopt) override;
  void LogError(std::string_view reason,
                ExtraInfo extra_info = std::nullopt) override;

 private:
  void PrintSeparator();

  static const char kSeparator = '-';
  std::ostream& stream_ = std::cout;
};

}  // namespace banks
