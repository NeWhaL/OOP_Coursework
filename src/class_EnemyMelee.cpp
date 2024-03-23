#include "../include/class_EnemyMelee.h"

EnemyMelee::EnemyMelee(sf::Vector2f coordinates, float speed, float health, float damage):
						Enemy{coordinates, speed, health, damage, 4, 10,
						res_manager->getTMeleeEnemyHead(),
						res_manager->getTHeroLegsUpDown(),
						res_manager->getTHeroLegsLeft(),
						res_manager->getTHeroLegsRight()}
{
  type_object = TypeObject::ENEMY;
  amount_money = 1;
}

void EnemyMelee::Move(float dt) 
{ 
	Enemy::Move(dt); 
	Message::Move(this);
}

void EnemyMelee::Update(float dt) {
  Move(dt);
  MoveSprite();
  GameObject::CollisionWithWall();
}

bool EnemyMelee::CollisionWithObject(const GameObject * const object) 
{
	Enemy::DirectionOnHero();
	return GameObject::CollisionWithObject(object) and 
		object->GetTypeObject() == TypeObject::SHOT;
}

void EnemyMelee::SendMessage(Message *message) 
{
	if (message->who_sent == this) return;
  switch (message->type_message) 
  {
	  case TypeMessage::MOVE:
		{
			auto& damage_object = message->who_sent;
			if(not CollisionWithObject(damage_object)) return;
			health -= damage_object->GetDamage();
			if (health <= 0) DeathObject(damage_object);
		}	break;
	  case TypeMessage::EFFECT:
	  {
	 		switch(message->effect.type)
			{
				case TypeEffect::EXPLOSION:
				{
					if (not (message->effect.creator != TypeObject::ENEMY and GameObject::CollisionWithObject(message->who_sent)))
						return;
					health -= message->effect.damage;
					if (health <= 0) DeathObject(message->who_sent);
				} break;
				default: break;
			}
	  }
	  default: break;
  }
}