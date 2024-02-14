#ifndef ENMELEE
#define ENMELEE

#include "class_Enemy.h"

class EnemyMelee : public Enemy 
{
private:
	void Move(float dt) override;
	bool CollisionWithObject(GameObject *object) override;

public:
	EnemyMelee(sf::Vector2f coordinates, float speed, float health, float damage);
	~EnemyMelee() = default;
	void SendMessage(Message *message) override;
	void Update(float dt) override;
};
#endif
