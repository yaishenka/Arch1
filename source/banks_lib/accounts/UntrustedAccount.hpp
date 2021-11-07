/**
 * @file UntrustedAccount.hpp
 * @author yaishenka
 * @date 07.11.2021
 */
#pragma once
#include "IAccountImpl.hpp"

namespace banks {
class UntrustedAccount: public IAccountImpl {
 public:
  explicit UntrustedAccount(Money balance);

  [[nodiscard]] eStatus IncreaseBalance(Money delta) override;
  [[nodiscard]] eStatus DecreaseBalance(Money delta) override;
};
}