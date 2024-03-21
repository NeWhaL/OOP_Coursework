#ifndef ENRANGE
#define ENRANGE

#include "class_Enemy.h"
#include "class_ShotBase.h"

class EnemyRange : public Enemy 
{
private:
  float shot_cooldown_total;
  float shot_cooldown;
	float distance;
	float range_fire;
	TypeShot current_type_shot;
	TypeEffect current_type_effect;

  void Move(float dt);
	bool CollisionWithObject(const GameObject * const object);
	bool CollisionDistance();
  void CreateShot(float dt);

public:
	EnemyRange(sf::Vector2f coordinates, float speed, float health, float damage);
	~EnemyRange() = default;
	void SendMessage(Message *message);
	void Update(float dt);
};
#endif
