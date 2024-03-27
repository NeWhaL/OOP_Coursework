#include "../include/class_EnemyMelee.h"

EnemyMelee::EnemyMelee(sf::Vector2f coordinates, float speed, float health, float damage, int amount_money):
						Enemy{coordinates, speed, health, damage, 4, 10,
						res_manager->getTMeleeEnemyHead(),
						res_manager->getTHeroLegsUpDown(),
						res_manager->getTHeroLegsLeft(),
						res_manager->getTHeroLegsRight()}
{
  type_object = TypeObject::ENEMY;
  this->amount_money = amount_money;
}

EnemyMelee::EnemyMelee(const EnemyCharacteristics& c):
						EnemyMelee(c.coordinates, c.speed, 
						c.health, c.damage, c.amount_money) {};

void EnemyMelee::Move(float dt) 
{ 
	Enemy::Move(dt); 
	Message::Move(this);
}

void EnemyMelee::Update(float dt) 
{
  Move(dt);
  MoveSprite();
  GameObject::CollisionWithWall();
}

bool EnemyMelee::CollisionWithObject(const GameObject * const object) 
{
	Enemy::DirectionOnHero();
	return GameObject::CollisionWithObject(object) and 
				(object->GetTypeObject() == TypeObject::SHOT and 
				object->GetCreatorObject() != TypeObject::ENEMY);
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
		}	break;
	  case TypeMessage::EFFECT:
	  {
	 		switch(message->effect.effect->GetTypeEffect())
			{
				case TypeEffect::EXPLOSION:
				{
					EffectExplosion* effect = static_cast<EffectExplosion*>(message->effect.effect);
					if (not Enemy::CollisionWithEffect(effect)) return;
					health -= effect->GetDamage();
				} break;
				default: break;
			}
	  }
	  default: break;
  }
	if (health <= 0) DeathObject(message->who_sent);
}