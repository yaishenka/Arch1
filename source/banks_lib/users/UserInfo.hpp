//
// Created by wasd on 10.12.2021.
//
#pragma once

#include <string>
#include <optional>

namespace banks {

struct UserInfo {
  explicit UserInfo(std::string name, std::string surname,
                    std::optional<std::string> address,
                    std::optional<std::string> passport)
      : name_(std::move(name)),
        surname_(std::move(surname)),
        address_(std::move(address)),
        passport_(std::move(passport)) {
  }

  std::string name_;
  std::string surname_;
  std::optional<std::string> address_;
  std::optional<std::string> passport_;
};

}  // namespace banks
