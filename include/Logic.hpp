#ifndef LOGIC_HPP
# define LOGIC_HPP

#include <mutex>
#include <thread>
#include <chrono>
#include <vector>

#include "GameState.hpp"
#include "ModVector.hpp"
#include "EntityFactory.hpp"
#include "AudioSource.hpp"
#include "PyBindInstance.hpp"
#include "PyEvaluate.hpp"
#include "Action.hpp"
#include "KeyboardController.hpp"

class LevelScene;

class Entity;
class AnimatedEntity;
class Renderer;

class Logic
{
private:
  using Clock = std::conditional<std::chrono::high_resolution_clock::is_steady,
				 std::chrono::high_resolution_clock,
				 std::chrono::steady_clock>::type;

  std::mutex lock;
  std::chrono::time_point<Clock> lastUpdate;
  unsigned int updatesSinceLastFrame;
  bool stop;

  std::vector<AnimatedEntity> &playerEntities;
  ModVector<decltype(GameState::enemies)::value_type, AnimatedEntity> enemies;
  ModVector<decltype(GameState::projectiles)::value_type, Entity> projectiles;
  ModVector<decltype(GameState::enemyProjectiles)::value_type, Entity> enemyProjectiles;

  void calculateCamera(LevelScene &);
  bool tick();
  void spawnMobGroup(Terrain::Room &room);

public:
  GameState gameState;
  EntityFactory entityFactory;
  PyBindInstance pyBindInstance;
  PyEvaluate pyEvaluate;
  ProjectileList projectileList;
  SpellList spellList;
  Action action;
  Vect<2u, KeyboardController> keyboardControllers;

  /**
   * Parameter isn't stored, only used for setup.
   */
  Logic(LevelScene &levelScene, Renderer &renderer, std::vector<AnimatedEntity> &playerEntities, std::vector<PlayerId> const &);

  void spawnProjectile(Vect<2u, double> pos, Vect<2u, double> speed, unsigned int type, double size = 0.2, unsigned int timeLeft = ~0u);
  void run();
  void exit();
  void updateDisplay(LevelScene &);

  void pause(void);
  void unpause(void);
};

constexpr void Controllable::update(Logic &)
{
  if (isDead())
    {
      ++dePopCounter;
      return ;
    }

  if (!stun)
    {
      speed = speed * 0.9 + input * 0.1;
    }
  else
    {
      --stun;
    }
  if (stun || !locked)
    dir = dir * 0.9 + targetDir * 0.1;
  pos += speed;
}

#endif
