#ifndef BMB
#define BMB
#include "class_Effect.h"

class EffectBomb : public Effect
{
private:
	void Action(float dt);

public:
	EffectBomb(sf::Vector2f coordinates, TypeObject creator);
	void Update(float dt);
	void SendMessage(Message* message);
	bool CollisionWithObject(GameObject* object) { return false; }
};

#endif
