#include <banks_lib/world/WorldFactory.hpp>

using namespace banks;

int main() {
  WorldFactory world_factory;

  IWorld::Ptr world = world_factory.CreateSimulation();

  world->Run();

  return 0;
}
