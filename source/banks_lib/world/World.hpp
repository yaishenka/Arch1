//
// Created by wasd on 10.12.2021.
//

#pragma once

#include <vector>
#include <memory>

#include <banks_lib/world/IUser.hpp>
#include <banks_lib/bank_system/Bank.hpp>
#include <banks_lib/bank_system/PaymentSystem.hpp>

namespace banks {

class World {
 public:
  void Run();
  void Run(size_t num_steps);

  void AddBank(BankId bank_id);
  void AddUser(const UserInfo& user_info);
  void AddBot(const UserInfo& user_info);

 private:
  void Step();

  std::vector<std::shared_ptr<IUser>> users_;
  std::vector<std::shared_ptr<Bank>> banks_;
  PaymentSystem payment_system_;
};

}  // namespace banks
