#include <banks_lib/operations/OperationHistory.hpp>

using namespace banks;

void OperationHistory::Push(IOperation::Ptr operation) {
  stored_operations_.insert(operation->GetOperationId());

  operations_stack_.push(std::move(operation));
}

std::optional<IOperation::Ptr> OperationHistory::Pop() {
  if (stored_operations_.empty()) {
    return std::nullopt;
  }

  stored_operations_.erase(
      stored_operations_.find(operations_stack_.top()->GetOperationId()));

  IOperation::Ptr operation = operations_stack_.top();
  operations_stack_.pop();

  return operation;
}

bool OperationHistory::HasOperation(OperationId operation_id) {
  return stored_operations_.contains(operation_id);
}
