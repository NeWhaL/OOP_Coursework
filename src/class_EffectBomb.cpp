#include "../include/class_EffectBomb.h"

EffectBomb::EffectBomb(sf::Vector2f coordinates, TypeObject creator):
							  Effect(coordinates, res_manager->getTEffectBomb(), 
							  1, 0.5, TypeEffect::EXPLOSION, 50)
{
	this->creator = creator;
	type_object = TypeObject::EFFECT;
}

void EffectBomb::Update(float dt) 
{
	MoveSprite();
	Action(dt);
}

void EffectBomb::Action(float dt) 
{
	if (action_time <= total_time) DeathObject(this);
	if (total_time != 0)
	{
		total_time += dt;
		return;
	}
	Message::ActionEffect(this, creator, TypeEffect::EXPLOSION, damage);
	total_time += dt;
}

void EffectBomb::SendMessage(Message* message) 
{

}
