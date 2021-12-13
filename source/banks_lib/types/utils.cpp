#include <banks_lib/types/utils.hpp>

using namespace banks;

std::istream& operator>>(std::istream& stream, Percentage& percentage) {
  double percent = 0.0;
  stream >> percent;

  percentage.integer = static_cast<uint16_t>(percent);
  percentage.fraction =
      static_cast<uint16_t>((percent - percentage.integer) * 100);

  return stream;
}

std::istream& operator>>(std::istream& stream, AccountConditions& conditions) {
  stream >> conditions.debit_percentage >> conditions.credit_limit >>
      conditions.credit_percentage >> conditions.deposit_percent >>
      conditions.deadline;

  return stream;
}

template <class B, class T>
inline std::shared_ptr<B> As(const std::shared_ptr<T>& pointer) {
  return std::dynamic_pointer_cast<B>(pointer);
}

template <class B, class T>
inline bool Is(const std::shared_ptr<T>& pointer) {
  return std::dynamic_pointer_cast<B>(pointer) != nullptr;
}

template <class B, class T>
inline const B* As(const T* pointer) {
  return dynamic_cast<const B*>(pointer);
}

template <class B, class T>
inline bool Is(const T* pointer) {
  return dynamic_cast<const B*>(pointer) != nullptr;
}
