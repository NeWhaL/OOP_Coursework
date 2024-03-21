#include "../include/class_ShotBase.h"

ShotBase::ShotBase(sf::Vector2f coordinates, sf::Vector2f direction, float speed, float range_fire,
						 float damage, TypeEffect effect, TypeObject who_creator):
						 Shot(coordinates, direction, speed, range_fire, damage, effect, who_creator) {}

bool ShotBase::CollisionWithObject(const GameObject * const object) 
{
	if (not GameObject::CollisionWithObject(object))
		return false; 
	bool is_collision = false;
	switch(object->GetTypeObject())
	{
		case TypeObject::PLAYER:
			is_collision = (creator != TypeObject::PLAYER); break;
		case TypeObject::ENEMY:
			is_collision = (creator != TypeObject::ENEMY); break;
		default: break;
	}
	return is_collision;
}

void ShotBase::SendMessage(Message *message) 
{
	if (message->type_message != TypeMessage::MOVE or message->who_sent == this) 
		return;
	if (not CollisionWithObject(message->who_sent)) return;
	DeathObject(message->who_sent);
}