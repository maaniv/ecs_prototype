#include <iostream>
#include "ecs.hpp"
using namespace ecs;

struct Position
{
  double x;
  double y;
};
struct Mass
{
  double m;
};

struct SomeEvent
{
  int value = 0;
};
void handleSomeEvent(SomeEvent event)
{
  std::cout << "HANDLING EVENT !!: " << event.value << std::endl;
}

void outputSystem()
{
  for(auto currentEntity : Iterator<void>())
  {
    std::cout << "-----------------------" << std::endl;
    std::cout << "ID: \t" << currentEntity.getID() << std::endl;
    if(currentEntity.hasComponents<Position>())
    {
      std::cout << "Position:" << std::endl;
      std::cout << " x: \t" << currentEntity.getComponent<Position>().x << std::endl;
      std::cout << " y: \t" << currentEntity.getComponent<Position>().y << std::endl;
    }
    if(currentEntity.hasComponents<Mass>())
    {
      std::cout << "Mass: \t" << currentEntity.getComponent<Mass>().m << std::endl;
    }
    std::cout << "-----------------------" << std::endl;
  }
}
void gravitySystem()
{
  for(auto currentEntity : Iterator<Mass, Position>())
  {
    for(auto currentEntity2_iter = ++Iterator<Mass, Position>(currentEntity); currentEntity2_iter != Iterator<Mass, Position>().end(); ++currentEntity2_iter)
    {
      auto currentEntity2 = *currentEntity2_iter;
      double dx = currentEntity2.getComponent<Position>().x - currentEntity.getComponent<Position>().x;
      double dy = currentEntity2.getComponent<Position>().y - currentEntity.getComponent<Position>().y;
      double distanceSquared = dx*dx + dy*dy;
      if(distanceSquared<0)
      {
        distanceSquared*=-1;
      }
      double F = 6.67259e-11 * ((currentEntity2.getComponent<Mass>().m * currentEntity.getComponent<Mass>().m) / (distanceSquared));
      std::cout<<"Force between " << currentEntity.getID() <<" and "<< currentEntity2.getID() << ": "<< F<<"\n";
    }
  }
}


int main()
{
  std::cout << "Hello\n" << std::endl;

  SystemManager::addSystem(&outputSystem, std::chrono::milliseconds(0));
  SystemManager::addSystem(&gravitySystem, std::chrono::milliseconds(0));
  SystemManager::addSystem(&handleSomeEvent);

  Entity a = Entity::createEntity();
  Entity b = Entity::createEntity();
  Entity c = Entity::createEntity();
  Entity d = Entity::createEntity();
  Entity e = Entity::createEntity();

  a.createComponent<Position>(Position{ 0.2, 0.3 });
  b.createComponent<Position>(Position{ 500.0, 600.0 });
  c.createComponent<Position>(Position{ 42.0, 7890.3 });
  d.createComponent<Position>(Position{ 6.0, 6.3 });
  a.createComponent<Mass>(Mass{ 0.7 });
  b.createComponent<Mass>(Mass{ 7.3  });
  c.createComponent<Mass>(Mass{ 1200000.0 });

  SystemManager::throwEvent(SomeEvent{12504});
  SystemManager::throwEvent(SomeEvent{12505});
  SystemManager::throwEvent(SomeEvent{12506});
  SystemManager::throwEvent(SomeEvent{12507});
  SystemManager::throwEvent(SomeEvent{12508});
  SystemManager::throwEvent(SomeEvent{12509});

  SystemManager::runSystems();

  std::cout << std::endl;

  d.removeEntity();
  a.removeEntity();
  c.removeComponent<Position>();

  e.createComponent<Position>(Position{2000.0, 3000.0});
  e.createComponent<Mass>(Mass{1000.0});
  a = Entity::createEntity();
  a.createComponent<Position>(Position{1000.0, 1000.0});

  SystemManager::runSystems();

  std::cout << "\nGood Bye" << std::endl;
  return 0;
}
