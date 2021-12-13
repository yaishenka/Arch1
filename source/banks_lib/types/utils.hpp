//
// Created by wasd on 10.12.2021.
//

#pragma once

#include <memory>

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
