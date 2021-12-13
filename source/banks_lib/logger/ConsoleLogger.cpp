//
// Created by wasd on 13.12.2021.
//

#include <banks_lib/logger/ConsoleLogger.hpp>

using namespace banks;

void ConsoleLogger::LogWithdraw(Money delta, ExtraInfo extra_info) {
  PrintSeparator();

  stream_ << "withdraw: " << delta << std::endl;
  if (extra_info) {
    stream_ << "[extra] " << *extra_info << std::endl;
  }
}

void ConsoleLogger::LogRefill(Money delta, ExtraInfo extra_info) {
  PrintSeparator();

  stream_ << "refill: " << delta << std::endl;
  if (extra_info) {
    stream_ << "[extra] " << *extra_info << std::endl;
  }
}

void ConsoleLogger::LogError(std::string_view reason, ExtraInfo extra_info) {
  PrintSeparator();

  stream_ << "ERROR: " << reason << std::endl;
  if (extra_info) {
    stream_ << "[extra] " << *extra_info << std::endl;
  }
}

void ConsoleLogger::PrintSeparator() {
  stream_ << '\n';

  static size_t num_separators = 80;
  for (size_t i = 0; i < num_separators; ++i) {
    stream_ << kSeparator;
  }

  stream_ << '\n';
  stream_ << std::endl;
}
