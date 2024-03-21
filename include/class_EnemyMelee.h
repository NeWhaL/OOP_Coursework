#ifndef ENMELEE
#define ENMELEE

#include "class_Enemy.h"

class EnemyMelee : public Enemy 
{
private:
	void Move(float dt);
	bool CollisionWithObject(const GameObject * const object);

public:
	EnemyMelee(sf::Vector2f coordinates, float speed, float health, float damage);
	~EnemyMelee() = default;
	void SendMessage(Message *message);
	void Update(float dt);
};
#endif
