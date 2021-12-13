//
// Created by wasd on 10.12.2021.
//

#pragma once

#include <vector>
#include <memory>

#include <banks_lib/users/IUser.hpp>
#include <banks_lib/bank_system/Bank.hpp>
#include <banks_lib/bank_system/PaymentSystem.hpp>
#include <banks_lib/world/ITimeService.hpp>

namespace banks {

class IWorld {
 public:
  using Ptr = std::shared_ptr<IWorld>;

  explicit IWorld(ITimeService::Ptr time_service, ILogger::Ptr logger)
      : time_service_(std::move(time_service)),
        logger_(std::move(logger)),
        payment_system_(std::make_shared<PaymentSystem>()),
        free_bank_id_(0) {
  }

  void Run();
  void Run(size_t num_steps);

  void AddBank(const AccountConditions& conditions);
  void AddUser(const UserInfo& user_info);
  void AddBot(const UserInfo& user_info);

 protected:
  virtual bool ProcessEvents(size_t step) = 0;
  virtual void MakeStep() = 0;

  ITimeService::Ptr time_service_;

  ILogger::Ptr logger_;

  std::vector<std::shared_ptr<IUser>> users_;
  std::shared_ptr<PaymentSystem> payment_system_;
  std::vector<std::shared_ptr<Bank>> banks_;
  BankId free_bank_id_;
};

}  // namespace banks
