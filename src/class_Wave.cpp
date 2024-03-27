#include "../include/class_Wave.h"

Wave::Wave(): 
      wave_number{0},
      amount_enemy{0},
      amount_enemy_melee{0},
      amount_enemy_range{0},
      amount_enemy_help{0},
      time_between_waves{3},
      time_since_the_last_wave{0},
      is_there_a_battle{true} 
{
  EnemyCharacteristics& emc = enemy_melee_characteristics;
  emc.amount_money = 1;
  emc.coordinates = { 0.f, 0.f };
  emc.damage = 1;
  emc.health = 100;
  emc.speed = 200;
  
  EnemyRangeCharacteristics& erc = enemy_range_characteristics;
  erc.hero_distance = 300;
  erc.amount_money = 1;
  erc.coordinates = { 0.f, 0.f };
  erc.damage = 2;
  erc.health = 4;
  erc.speed = 150;
  erc.range_fire_shot = 500;
  erc.shot_cooldown_total = 1.5;
  erc.speed_shot = 300;
  erc.type_shot = TypeShot::BASE;
  erc.type_effect = TypeEffect::NONE;
}

void Wave::Update(std::list<GameObject*>& game_objects, float dt)
{
  time_since_the_last_wave += dt;
	if (time_between_waves > time_since_the_last_wave)
		return;
	time_since_the_last_wave = 0;
  CreateTestWave(game_objects);
  // CreateWave(game_objects);
}

void Wave::CreateTestWave(std::list<GameObject*>& game_objects)
{
  static bool tmp = true;
  if(not tmp) return;
  enemy_melee_characteristics.coordinates = { 800, 500 };
  enemy_melee_characteristics.speed = 0;
  game_objects.push_back(new EnemyMelee(enemy_melee_characteristics));
  enemy_range_characteristics.coordinates = { 400, 500 };
  enemy_range_characteristics.speed = 0;
  game_objects.push_back(new EnemyRange(enemy_range_characteristics));
  tmp = false;
}

void Wave::CreateWave(std::list<GameObject*>& game_objects)
{
	for (int i = 0; i < amount_enemy_melee; i++)
  {
    enemy_melee_characteristics.coordinates = GetRandCoordinatesForEnemy();
	  game_objects.push_back(new EnemyMelee(enemy_melee_characteristics));
  }
  for (int i = 0; i < amount_enemy_range; i++)
  {
    enemy_range_characteristics.coordinates = GetRandCoordinatesForEnemy();
    game_objects.push_back(new EnemyRange(enemy_range_characteristics));
  }
  // for (int i = 0; i < amount_enemy_help; i++)

  UpdateAmountEnemy();
  UpgradeEnemies();
}

sf::Vector2f Wave::GetRandCoordinatesForEnemy()
{
  return { static_cast<float>(rand() % (size_arena.down_right.x - size_arena.up_left.x) + size_arena.up_left.x),
           static_cast<float>(rand() % (size_arena.down_right.y - size_arena.up_left.y) + size_arena.up_left.y)};
}

void Wave::UpdateAmountEnemy()
{
  ++wave_number;
  if(not (wave_number % 2)) return;
  int type_created_enemy = rand() % 3 + 1;
  switch (type_created_enemy)
  {
    case 1: ++amount_enemy_melee; break;
    case 2: ++amount_enemy_range; break;
    case 3:
    {
      if(amount_enemy_melee > 0 or amount_enemy_range > 0)   
        ++amount_enemy_help;
    } break;
  }
}

void Wave::UpgradeEnemies()
{
  if (not (wave_number % 4)) return;
} 