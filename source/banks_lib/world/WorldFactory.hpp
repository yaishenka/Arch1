//
// Created by wasd on 13.12.2021.
//

#pragma once

#include <banks_lib/world/IWorld.hpp>

namespace banks {

class WorldFactory {
 public:
  IWorld::Ptr CreateSimulation();
};

}  // namespace banks
