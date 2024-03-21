#include "../include/class_EnemyRange.h"

EnemyRange::EnemyRange(sf::Vector2f coordinates, float speed, float health, float damage):
            Enemy{coordinates, speed, health, damage, 3, 10,
									res_manager->getTRangeEnemyHead(),
									res_manager->getTHeroLegsUpDown(),
									res_manager->getTHeroLegsLeft(),
									res_manager->getTHeroLegsRight()},
            shot_cooldown_total{1.5},
            shot_cooldown{0},
						distance{500},
						range_fire{400},
						current_type_shot{TypeShot::BASE},
						current_type_effect{TypeEffect::EXPLOSION}
{
  type_object = TypeObject::ENEMY;
  amount_money = 2;
}

void EnemyRange::Move(float dt) 
{
	if(CollisionDistance()) Enemy::Move(dt);
}

bool EnemyRange::CollisionWithObject(const GameObject * const object)
{
	Enemy::DirectionOnHero();
  return GameObject::CollisionWithObject(object) and 
				 (object->GetTypeObject() == TypeObject::SHOT or
				  object->GetTypeObject() == TypeObject::EFFECT);
}

void EnemyRange::SendMessage(Message *message)
{
  if (message->who_sent == this) return;
	auto& damage_object = message->who_sent;
  switch (message->type_message) 
  {
	  case TypeMessage::MOVE:
		{
			if(damage_object->GetCreatorObject() == TypeObject::ENEMY) return;
			if(not CollisionWithObject(damage_object)) return;
			health -= damage_object->GetDamage();
			if (health <= 0) DeathObject(damage_object);
		} break;
	  case TypeMessage::EFFECT:
	  {
			if(not CollisionWithObject(damage_object)) return;
			if(message->effect.creator == TypeObject::ENEMY) return;
	 	  switch(message->effect.type)
			{
				case TypeEffect::EXPLOSION:
				{
					health -= message->effect.damage;
					if (health <= 0) DeathObject(damage_object);
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

bool EnemyRange::CollisionDistance()
{
	float length = LengthBetweenTwoPoints(coordinates, hero->GetPosition());
	if(distance < length) return true;
	else if(distance > length)
	{
		direction.x *= -1;
		direction.y *= -1;
		return true;
	}
	return false;
}

void EnemyRange::CreateShot(float dt)
{
	shot_cooldown += dt;
  if (shot_cooldown < shot_cooldown_total) return;
	shot_cooldown = 0;

	sf::Vector2f cur_pos_head = GetPositionHead();
	cur_pos_head = CurrentCoordinatesOfTheObjectRelativeToAnotherObject(
								 hero->GetPositionHead(), cur_pos_head);
	sf::Vector2f normalized_vector = NormalizationVector(cur_pos_head);
	Shot* shot = new ShotBase(head_sprite->getPosition(), normalized_vector, 550, 400,
										damage, current_type_effect, TypeObject::ENEMY);
	Message::CreateShot(shot, this);
}