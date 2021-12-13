//
// Created by wasd on 10.12.2021.
//

#include <banks_lib/world/Bot.hpp>

using namespace banks;

Bot::Bot(const UserInfo& user_info) : IUser(std::move(user_info)) {
}

void Bot::Step() {
}

void Bot::CreateAccount(BankId bank_id, eAccountType account_type) {
}

Money Bot::GetBalance(AccountId account_id) {
  return 0;
}

std::vector<AccountId> Bot::ListAccounts() {
  return {};
}
