/**
 * @file IOperation.hpp
 * @author yaishenka
 * @date 07.11.2021
 */
#pragma once
#include <memory>
#include "types.hpp"

namespace banks {
struct OperationStatus {
  OperationId operation_id;
  eStatus status;
};

class IOperation {
 public:
  using Ptr = std::shared_ptr<IOperation>;

  IOperation(Money delta, OperationId operation_id) :
      delta_(delta),
      operation_id_(operation_id) {}
  virtual ~IOperation() = default;

  [[nodiscard]] Money GetDelta() const { return delta_; }
  [[nodiscard]] OperationId GetOperationId() const { return operation_id_; }
 private:
  Money delta_;
  OperationId operation_id_;
};

class Withdraw : public IOperation {
 public:
  Withdraw(Money delta, OperationId operation_id) :
      IOperation(delta, operation_id) {}
};

class Refill : public IOperation {
 public:
  Refill(Money delta, OperationId operation_id) :
      IOperation(delta, operation_id) {}
};

class AccruePercentages : public IOperation {
 public:
  AccruePercentages(Money delta, OperationId operation_id, size_t percents) :
      IOperation(delta, operation_id) {
    percents_ = percents;
  }

  [[nodiscard]] size_t GetPercents() const { return percents_; }
 private:
  size_t percents_;
};

}