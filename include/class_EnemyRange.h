#ifndef ENRANGE
#define ENRANGE

#include "class_Enemy.h"
#include "class_ShotBase.h"

struct EnemyRangeCharacteristics : public EnemyCharacteristics
{
	float shot_cooldown_total;
	float hero_distance;
	float range_fire_shot;
	float speed_shot;
	TypeShot type_shot;
	TypeEffect type_effect;
};

class EnemyRange : public Enemy 
{
private:
  float shot_cooldown_total;
  float shot_cooldown;
	float hero_distance;
	float range_fire_shot;
	float speed_shot;
	TypeShot type_shot;
	TypeEffect type_effect;

  void Move(float dt);
	bool CollisionWithObject(const GameObject * const object);
	bool ToStopAtADistanceFromTheHero();
  void CreateShot(float dt);
	void ShotSelectionToCreate(sf::Vector2f mouse_pos);

public:
	EnemyRange(sf::Vector2f coordinates, float speed, float health, float damage, int amount_money,
						 float shot_cooldown_total,	float shot_cooldown, float hero_distance, float range_fire_shot,
						 float speed_shot, TypeShot type_shot, TypeEffect type_effect);
	EnemyRange(const EnemyRangeCharacteristics& charact);
	~EnemyRange() = default;
	void SendMessage(Message *message);
	void Update(float dt);
};
#endif
