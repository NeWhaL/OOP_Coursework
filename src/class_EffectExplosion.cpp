#include "../include/class_EffectExplosion.h"

EffectExplosion::EffectExplosion(sf::Vector2f coordinates,
								 TypeObject creator, GameObject* affected):
								 Effect(TypeEffect::EXPLOSION, creator,
								 ResourceManager::GetInstance()->getTEffectExplosion(),
								 affected, 0.5),
								 coordinates{coordinates},
								 damage{50}
{
	sprite->setScale({0.15, 0.15});
	kill_radius = sprite->getGlobalBounds().height / 2;	
	sprite->setOrigin({sprite->getLocalBounds().height / 2, sprite->getLocalBounds().width / 2});
	sprite->setPosition(coordinates);
}

float EffectExplosion::GetDamage() const
{
	return damage;
}

float EffectExplosion::GetKillRadius() const
{
	return kill_radius;
}

sf::Vector2f EffectExplosion::GetCoordinates() const
{
	return coordinates;
}

void EffectExplosion::Action(float dt) 
{
	if (timer >= effect_time)
	{
		Message::EndEffect(this);
		return;
	}
	else if (timer != 0)
	{
		timer += dt;
		return;
	}
	Message::ActionEffect(this);
	timer += dt;
}