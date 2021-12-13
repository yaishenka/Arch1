//
// Created by wasd on 10.12.2021.
//

#pragma once

#include <memory>

#include <banks_lib/types/types.hpp>
#include <banks_lib/bank_system/AccountConditions.hpp>

std::istream& operator>>(std::istream& stream, banks::Percentage& percentage);

std::istream& operator>>(std::istream& stream,
                         banks::AccountConditions& conditions);

namespace banks {

template <class B, class T>
inline std::shared_ptr<B> As(const std::shared_ptr<T>& pointer);

template <class B, class T>
inline bool Is(const std::shared_ptr<T>& pointer);

template <class B, class T>
inline const B* As(const T* pointer);

template <class B, class T>
inline bool Is(const T* pointer);

}  // namespace banks
