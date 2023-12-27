#include "../include/class_EnemyMelee.h"
#include "../include/class_Manager.h"

EnemyMelee::EnemyMelee(sf::Vector2f coordinates, float speed, float health, float damage)
    : Enemy(coordinates, speed, health, damage, ResourceManager::GetInstance()->getTHeroHead()) {
  type_object = TypeObject::ENEMY;
  amount_sprite = 8;
  amount_money = 1;
}

EnemyMelee::~EnemyMelee() {}

void EnemyMelee::Move(float dt) { Enemy::Move(dt); }

void EnemyMelee::MoveSprite() { main_sprite->setPosition(coordinates.x, coordinates.y); }

void EnemyMelee::Update(float dt) {
  Move(dt);
  MoveSprite();
  GameObject::CollisionWithWall();
}

void EnemyMelee::SendMessage(Message *message) 
{
	if (message->who_sent == this)
		return;
   switch (message->type_message) 
   {
	   case TypeMessage::MOVE:
		 	CollisionWithObject(message->who_sent);	
			break;
	   case TypeMessage::EFFECT:
	   {
	 		switch(message->effect.type)
			{
				case TypeEffect::EXPLOSION:
				{
					if (not (message->effect.creator != TypeObject::ENEMY and GameObject::CollisionWithObject(message->who_sent)))
						 return;
					health -= message->effect.damage;
					if (health <= 0)
						DeathObject(message->who_sent);
				} break;
				default: break;
			}
	  }
	  default: break;
  }
}

bool EnemyMelee::CollisionWithObject(GameObject *object) 
{
	// по умолчанию противник движется на героя, поэтому manager->GetHero() => герой не рассматривается в switch
	Enemy::CollisionWithObject(manager->GetHero());
	if (not GameObject::CollisionWithObject(object))
		return false;
	switch(object->GetTypeObject())
	{
		case TypeObject::SHOT:
		{
			health -= object->GetDamage();
			if (health <= 0)
				DeathObject(object);
		} break;
		case TypeObject::ENEMY:
		{

		} break;
		default: break;
	}
   return true;
}
