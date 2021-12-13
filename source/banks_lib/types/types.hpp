/**
 * @file types.hpp
 * @author yaishenka
 * @date 10.10.2021
 */
#pragma once

#include <cctype>
#include <cstdint>

namespace banks {

using Money = int64_t;

// ...123,45
struct Percentage {
  uint16_t integer; // ...123,
  uint16_t fraction; // 45
};

using AccountId = size_t;

using OperationId = size_t;
using BankId = size_t;
using TransactionId = size_t;

using UserId = size_t;

using Time = size_t;

enum class eStatus { eOk, eDenied };

enum class eAccountType { eDebit, eCredit, eDeposit };

}  // namespace banks
