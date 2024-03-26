#ifndef EFFECT_EXPLOSION 
#define EFFECT_EXPLOSION 
#include "class_Effect.h"
#include "struct_Message.h"

class EffectExplosion : public Effect
{
	float damage;
	float kill_radius;
	sf::Vector2f coordinates;

public:
	EffectExplosion(sf::Vector2f coordinates, TypeObject creator, GameObject* affected);
	~EffectExplosion() {}
	float GetDamage() const;
	float GetKillRadius() const;
	sf::Vector2f GetCoordinates() const;
	void Action(float dt);
};

#endif