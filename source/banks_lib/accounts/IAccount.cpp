#include <banks_lib/accounts/IAccount.hpp>
#include <banks_lib/accounts/TrustedAccount.hpp>

using namespace banks;

IAccount::IAccount(AccountId account_id) : account_id_(account_id), next_free_op_id_(0) {
}

void IAccount::Upgrade() {
  auto trusted_account =
      std::dynamic_pointer_cast<TrustedAccount>(account_impl_);

  if (trusted_account != nullptr) {
    return;
  }

  account_impl_ = std::make_shared<TrustedAccount>(account_impl_->GetBalance());
}

std::vector<IOperation::Ptr> IAccount::AbortOperation(
    OperationId operation_id) {
  std::vector<IOperation::Ptr> history_suffix;

  if (!operation_history_.HasOperation(operation_id)) {
    return history_suffix;
  }

  while (operation_history_.GetSize() > 0) {
    auto next_operation = operation_history_.Pop().value();

    if (next_operation->GetOperationId() == operation_id) {
      return history_suffix;
    }

    history_suffix.push_back(next_operation);
    AbortOperation(next_operation);
  }

  return history_suffix;
}