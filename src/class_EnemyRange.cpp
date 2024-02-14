#include "../include/class_EnemyRange.h"
#include "../include/class_Manager.h"

EnemyRange::EnemyRange(sf::Vector2f coordinates, float speed, float health, float damage):
            Enemy{coordinates, speed, health, damage, ResourceManager::GetInstance()->getTHeroHead()},
            cooldown_shot{1.5},
            recharge_time{0}
{
  type_object = TypeObject::ENEMY;
  amount_sprite = 8;
  amount_money = 2;
}

void EnemyRange::Move(float dt) { Enemy::Move(dt); }

void EnemyRange::SendMessage(Message *message)
{
  if (message->who_sent == this) return;
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

void EnemyRange::Update(float dt)
{
  Move(dt);
  MoveSprite();
  GameObject::CollisionWithWall();
  CreateShot(dt);
}

bool EnemyRange::CollisionWithObject(GameObject *object)
{
  return false;
}

void EnemyRange::CreateShot(float dt)
{
  recharge_time += dt;
  if (recharge_time < cooldown_shot) return;
}