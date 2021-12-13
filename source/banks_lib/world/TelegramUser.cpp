//
// Created by wasd on 10.12.2021.
//

#include <banks_lib/world/TelegramUser.hpp>

using namespace banks;

TelegramUser::TelegramUser(UserInfo user_info) : IUser(user_info) {
}

void TelegramUser::Step() {
}

void TelegramUser::CreateAccount(BankId bank_id, eAccountType account_type) {
}

Money TelegramUser::GetBalance(AccountId account_id) {
  return 0;
}

std::vector<AccountId> TelegramUser::ListAccounts() {
  return {};
}
