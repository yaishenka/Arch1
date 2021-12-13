//
// Created by wasd on 10.12.2021.
//

#include <banks_lib/world/IWorld.hpp>
#include <banks_lib/users/TelegramUser.hpp>
#include <banks_lib/users/Bot.hpp>
#include <banks_lib/world/ManualTimeService.hpp>

using namespace banks;

void IWorld::Run() {
  size_t step = 0;
  while (true) {
    if (ProcessEvents(step)) {
      ++step;
    }
  }
}

void IWorld::Run(size_t num_steps) {
  for (size_t step = 0; step < num_steps;) {
    if (ProcessEvents(step)) {
      ++step;
    }
  }
}

void IWorld::AddBank(const AccountConditions& conditions) {
  banks_.emplace_back(std::make_shared<Bank>(free_bank_id_++));
  banks_.back()->SetLogger(logger_);
  banks_.back()->SetAccountConditions(conditions);
  banks_.back()->ConnectToPaymentSystem(payment_system_);
}

void IWorld::AddUser(const UserInfo& user_info) {
  users_.emplace_back(std::make_shared<TelegramUser>(user_info));
}

void IWorld::AddBot(const UserInfo& user_info) {
  users_.emplace_back(std::make_shared<Bot>(user_info, banks_));
}
