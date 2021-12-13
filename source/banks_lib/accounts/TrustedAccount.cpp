#include <banks_lib/accounts/TrustedAccount.hpp>

using namespace banks;

TrustedAccount::TrustedAccount(Money balance) : IAccountImpl(balance) {
}

eStatus TrustedAccount::IncreaseBalance(Money delta) {
  balance_ += delta;
  return eStatus::eOk;
}

eStatus TrustedAccount::DecreaseBalance(Money delta) {
  balance_ -= delta;
  return eStatus::eOk;
}
