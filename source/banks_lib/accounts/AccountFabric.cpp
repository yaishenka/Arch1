//
// Created by wasd on 10.12.2021.
//

#include <banks_lib/accounts/AccountFabric.hpp>
#include <banks_lib/accounts/DebitAccount.hpp>
#include <banks_lib/accounts/CreditAccount.hpp>
#include <banks_lib/accounts/DepositAccount.hpp>

using namespace banks;

AccountFabric::AccountFabric() : next_account_id_(0) {
}

std::shared_ptr<IAccount> AccountFabric::CreateDebitAccount(
    const Percentage& debit_percentage) {
  return std::make_shared<DebitAccount>(next_account_id_++, debit_percentage);
}

std::shared_ptr<IAccount> AccountFabric::CreateCreditAccount(
    Money credit_limit, const Percentage& credit_percentage) {
  return std::make_shared<CreditAccount>(next_account_id_++, credit_limit,
                                         credit_percentage);
}

std::shared_ptr<IAccount> AccountFabric::CreateDepositAccount(
    const Percentage& deposit_percent, Time deadline) {
  return std::make_shared<DepositAccount>(next_account_id_++, deposit_percent,
                                          deadline);
}
