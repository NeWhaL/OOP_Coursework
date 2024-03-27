#ifndef WAVE
#define WAVE

#include "main.h"
#include "class_Enemy.h"
#include "class_EnemyMelee.h"
#include "class_EnemyRange.h"

class Wave
{
  int wave_number;
  int amount_enemy;
  int amount_enemy_melee;
  int amount_enemy_range;
  int amount_enemy_help;
  float time_between_waves;
  float time_since_the_last_wave;
  bool is_there_a_battle;
  EnemyCharacteristics enemy_melee_characteristics;
  EnemyRangeCharacteristics enemy_range_characteristics;
  // EnemyCharacteristics enemy_support_characteristics;

  void CreateWave(std::list<GameObject*>& game_objects);
  void CreateTestWave(std::list<GameObject*>& game_objects);
  void UpdateAmountEnemy();
  void UpgradeEnemies();
  sf::Vector2f GetRandCoordinatesForEnemy();

public:
  Wave();
  void Update(std::list<GameObject*>& game_object, float dt);
};

#endif