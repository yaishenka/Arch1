/**
 * @file OperationHistory.hpp
 * @author yaishenka
 * @date 07.11.2021
 */
#pragma once

#include <stack>
#include <optional>
#include <unordered_set>

#include <banks_lib/operations/Operations.hpp>

namespace banks {
class OperationHistory {
 public:
  void Push(IOperation::Ptr operation);
  std::optional<IOperation::Ptr> Pop();

  [[nodiscard]] size_t GetSize() const {
    return operations_stack_.size();
  }

  [[nodiscard]] bool HasOperation(OperationId operation_id);

 private:
  std::unordered_set<OperationId> stored_operations_;
  std::stack<IOperation::Ptr> operations_stack_;
};
}  // namespace banks