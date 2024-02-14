#include "../include/class_EffectBomb.h"
#include "../include/class_Manager.h"

EffectBomb::EffectBomb(sf::Vector2f coordinates, TypeObject creator):
							  Effect(coordinates, ResourceManager::GetInstance()->getTEffectBomb(), 
							  1, 0.5, TypeEffect::EXPLOSION, 50)
{
	this->creator = creator;
	main_sprite->setScale(0.15, 0.15);
	radius_hitbox_head = main_sprite->getGlobalBounds().height / 2;
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
	Message::ActionEffect(this, creator, TypeEffect::EXPLOSION, damage, manager);
	total_time += dt;
}

void EffectBomb::SendMessage(Message* message) 
{

}
