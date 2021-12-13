//
// Created by wasd on 10.12.2021.
//

#include <banks_lib/world/World.hpp>
#include <banks_lib/world/TelegramUser.hpp>
#include <banks_lib/world/Bot.hpp>

using namespace banks;

void World::Run() {
  while (true) {
    Step();
  }
}

void World::Run(size_t num_steps) {
  for (size_t step = 0; step < num_steps; ++step) {
    Step();
  }
}

void World::Step() {
}

void World::AddBank(BankId bank_id) {
  banks_.emplace_back(std::make_shared<Bank>(bank_id));
}

void World::AddUser(const UserInfo& user_info) {
  users_.emplace_back(std::make_shared<TelegramUser>(user_info));
}

void World::AddBot(const UserInfo& user_info) {
  users_.emplace_back(std::make_shared<Bot>(user_info));
}
