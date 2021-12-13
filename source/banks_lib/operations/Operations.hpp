/**
 * @file IOperation.hpp
 * @author yaishenka
 * @date 07.11.2021
 */
#pragma once

#include <memory>

#include <banks_lib/types/types.hpp>

namespace banks {
struct OperationStatus {
  OperationId operation_id;
  eStatus status;
};

class IOperation {
 public:
  using Ptr = std::shared_ptr<IOperation>;

  IOperation(Money delta, OperationId operation_id)
      : delta_(delta), operation_id_(operation_id) {
  }
  virtual ~IOperation() = default;

  [[nodiscard]] Money GetDelta() const {
    return delta_;
  }
  [[nodiscard]] OperationId GetOperationId() const {
    return operation_id_;
  }

 private:
  Money delta_;
  OperationId operation_id_;
};

class WithdrawOperation : public IOperation {
 public:
  WithdrawOperation(Money delta, OperationId operation_id)
      : IOperation(delta, operation_id) {
  }
};

class RefillOperation : public IOperation {
 public:
  RefillOperation(Money delta, OperationId operation_id)
      : IOperation(delta, operation_id) {
  }
};

class AccruePercentagesOperation : public IOperation {
 public:
  AccruePercentagesOperation(Money delta, OperationId operation_id, Percentage percents)
      : IOperation(delta, operation_id), percents_(std::move(percents)) {
  }

  [[nodiscard]] Percentage GetPercents() const {
    return percents_;
  }

 private:
  Percentage percents_;
};

}  // namespace banks