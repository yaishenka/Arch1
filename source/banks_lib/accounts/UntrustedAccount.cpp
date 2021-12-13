#include <banks_lib/accounts/UntrustedAccount.hpp>

using namespace banks;

UntrustedAccount::UntrustedAccount(Money balance) : IAccountImpl(balance) {
}

eStatus UntrustedAccount::IncreaseBalance(Money delta) {
  balance_ += delta;
  return eStatus::eOk;
}

eStatus UntrustedAccount::DecreaseBalance(Money delta) {
  if (balance_ - delta < 0) {
    return eStatus::eDenied;
  }

  balance_ -= delta;
  return eStatus::eOk;
}