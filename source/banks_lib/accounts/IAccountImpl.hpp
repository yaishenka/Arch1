/**
 * @file IAccountImpl.hpp
 * @author yaishenka
 * @date 07.11.2021
 */
#pragma once
#include <memory>
#include "../types.hpp"

namespace banks {
class IAccountImpl {
 public:
  using Ptr = std::shared_ptr<IAccountImpl>;

  explicit IAccountImpl(Money balance): balance_(balance) {}
  virtual ~IAccountImpl() = default;

  [[nodiscard]] virtual eStatus IncreaseBalance(Money delta) = 0;
  [[nodiscard]] virtual eStatus DecreaseBalance(Money delta) = 0;

  [[nodiscard]] Money GetBalance() const {return balance_; }
 protected:
  Money balance_;
};
}
