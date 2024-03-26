#include "../include/class_EnemyRange.h"

EnemyRange::EnemyRange(sf::Vector2f coordinates, float speed, float health, float damage):
            Enemy{coordinates, speed, health, damage, 3, 10,
									res_manager->getTRangeEnemyHead(),
									res_manager->getTHeroLegsUpDown(),
									res_manager->getTHeroLegsLeft(),
									res_manager->getTHeroLegsRight()},
            shot_cooldown_total{1.5},
            shot_cooldown{0},
						distance{200},
						range_fire_shot{400},
						speed_shot{400},
						current_type_shot{TypeShot::BASE},
						current_type_effect{TypeEffect::EXPLOSION}
{
  type_object = TypeObject::ENEMY;
  amount_money = 2;
}

void EnemyRange::Move(float dt) 
{
	if(CollisionDistance()) Enemy::Move(dt);
	Message::Move(this);
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

  switch (message->type_message) 
  {
	  case TypeMessage::MOVE:
		{
			auto& damage_object = message->who_sent;
			if(damage_object->GetCreatorObject() == TypeObject::ENEMY) return;
			if(not CollisionWithObject(damage_object)) return;
			health -= damage_object->GetDamage();
			if (health <= 0) DeathObject(damage_object);
		} break;
	  case TypeMessage::EFFECT:
	  {
			switch(message->effect.effect->GetTypeEffect())
			{
				case TypeEffect::EXPLOSION:
				{
					EffectExplosion* effect = static_cast<EffectExplosion*>(message->effect.effect);
					if (not Enemy::CollisionWithEffect(effect)) return;
					health -= effect->GetDamage();
					if (health <= 0) DeathObject(message->who_sent);
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

	ShotSelectionToCreate(normalized_vector);
}

void EnemyRange::ShotSelectionToCreate(sf::Vector2f mouse_pos) 
{
	Shot* shot = nullptr;
	switch(current_type_shot)
	{
		case TypeShot::BASE:
		{
			shot = new ShotBase(head_sprite->getPosition(), mouse_pos, speed_shot,
														range_fire_shot, damage, current_type_effect, TypeObject::ENEMY);
		} break;
		case TypeShot::RICOCHET:
		{
			shot = new ShotRicochet(head_sprite->getPosition(), mouse_pos, speed_shot,
														range_fire_shot, damage, current_type_effect, TypeObject::ENEMY);
		} break;
		default: break;
	}
	if(shot)
		Message::CreateShot(shot, this);
}