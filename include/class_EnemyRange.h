#ifndef ENRANGE
#define ENRANGE

#include "class_Enemy.h"

class EnemyRange : public Enemy {
private:
  float cooldown_shot;
  float recharge_time;

  void Move(float dt) override;
	bool CollisionWithObject(GameObject *object) override;
  void CreateShot(float dt);

public:
	EnemyRange(sf::Vector2f coordinates, float speed, float health, float damage);
	~EnemyRange() = default;
	void SendMessage(Message *message) override;
	void Update(float dt) override;
};
#endif
