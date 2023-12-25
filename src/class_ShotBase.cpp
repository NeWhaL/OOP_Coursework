#include "../include/class_ShotBase.h"

ShotBase::ShotBase(sf::Vector2f coordinates, sf::Vector2f direction,
                   float speed, float range_fire, float damage,
                   TypeEffect effect, TypeObject who_creator)
    : Shot(coordinates, direction, speed, range_fire, damage, effect,
           who_creator) {}

bool ShotBase::CollisionWithObject(GameObject *object) 
{
	if (not GameObject::CollisionWithObject(object))
		return false; 
	switch(object->GetTypeObject())
	{
		case TypeObject::PLAYER:
		{
			if (creator == TypeObject::PLAYER)
				return false;
			DeathObject(object);
		} break;
		case TypeObject::ENEMY:
		{
			if (creator == TypeObject::ENEMY)
				return false;
			DeathObject(object);
		} break;
		default: break;
	}
   return true;
}

void ShotBase::SendMessage(Message *message) 
{
	if (message->type_message != TypeMessage::MOVE or message->who_sent == this) 
		return;
	CollisionWithObject(message->who_sent);
}
