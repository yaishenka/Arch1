//
// Created by wasd on 12.12.2021.
//
#pragma once

#include <iostream>

#include <banks_lib/logger/ILogger.hpp>

namespace banks {

class ConsoleLogger : public ILogger {
 public:
  void LogWithdraw(Money delta, ExtraInfo extra_info = std::nullopt) override {
    PrintSeparator();

    std::cerr << "withdraw: " << delta << std::endl;
    if (extra_info) {
      std::cerr << "[extra] " << *extra_info << std::endl;
    }
  }

  void LogRefill(Money delta, ExtraInfo extra_info = std::nullopt) override {
    PrintSeparator();

    std::cerr << "refill: " << delta << std::endl;
    if (extra_info) {
      std::cerr << "[extra] " << *extra_info << std::endl;
    }
  }

  void LogError(std::string_view reason,
                ExtraInfo extra_info = std::nullopt) override {
    PrintSeparator();

    std::cerr << "ERROR: " << reason << std::endl;
    if (extra_info) {
      std::cerr << "[extra] " << *extra_info << std::endl;
    }
  }

 private:
  void PrintSeparator() {
    std::cerr << '\n';

    static size_t num_separators = 80;
    for (size_t i = 0; i < num_separators; ++i) {
      std::cerr << kSeparator;
    }

    std::cerr << '\n';
    std::cerr << std::endl;
  }

  static const char kSeparator = '-';
};

}  // namespace banks
