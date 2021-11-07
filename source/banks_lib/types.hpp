/**
 * @file types.hpp
 * @author yaishenka
 * @date 10.10.2021
 */
#include <cctype>
#include <cstdint>

namespace banks {
  using Money = int64_t;
  using AccountId = size_t;
  using OperationId = size_t;

  enum class eStatus {eOk, eDenied};
}