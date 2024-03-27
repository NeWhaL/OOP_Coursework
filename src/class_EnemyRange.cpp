#include "../include/class_EnemyRange.h"

EnemyRange::EnemyRange(sf::Vector2f coordinates, float speed, float health, float damage, int amount_money, 
						float shot_cooldown_total, float shot_cooldown, float hero_distance, float range_fire_shot,
						float speed_shot, TypeShot type_shot, TypeEffect type_effect):
            Enemy{coordinates, speed, health, damage, 3, 10,
									res_manager->getTRangeEnemyHead(),
									res_manager->getTHeroLegsUpDown(),
									res_manager->getTHeroLegsLeft(),
									res_manager->getTHeroLegsRight()},
            shot_cooldown_total{shot_cooldown_total},
            shot_cooldown{shot_cooldown},
						hero_distance{hero_distance},
						range_fire_shot{range_fire_shot},
						speed_shot{speed_shot},
						type_shot{type_shot},
						type_effect{type_effect}
{
  type_object = TypeObject::ENEMY;
  this->amount_money = amount_money;
}

EnemyRange::EnemyRange(const EnemyRangeCharacteristics& c):
						EnemyRange(c.coordinates, c.speed, c.health, c.damage, 
											c.amount_money, c.shot_cooldown_total,
											0, c.hero_distance, 
											c.range_fire_shot, c.speed_shot, c.type_shot,
											c.type_effect) {}

void EnemyRange::Move(float dt) 
{
	if(not ToStopAtADistanceFromTheHero()) Enemy::Move(dt);
	Message::Move(this);
}

bool EnemyRange::CollisionWithObject(const GameObject * const object)
{
	Enemy::DirectionOnHero();
  return GameObject::CollisionWithObject(object) and 
				 (object->GetTypeObject() == TypeObject::SHOT);
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
				} break;
				default: break;
			}
	  }
	  default: break;
  }
	if (health <= 0) DeathObject(message->who_sent);
}

void EnemyRange::Update(float dt)
{
	Move(dt);
  MoveSprite();
  GameObject::CollisionWithWall();
	CreateShot(dt);
}

bool EnemyRange::ToStopAtADistanceFromTheHero()
{
	float length = LengthBetweenTwoPoints(coordinates, hero->GetPosition());
	if(hero_distance < length) return false;
	else if(hero_distance > length)
	{
		if(not GameObject::CollisionWithObject(hero))
		{
			direction.x *= -1;
			direction.y *= -1;
		}
		return false;
	}
	return true;
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

void EnemyRange::ShotSelectionToCreate(sf::Vector2f target) 
{
	Shot* shot = nullptr;
	switch(type_shot)
	{
		case TypeShot::NONE:
		case TypeShot::BASE:
		{
			shot = new ShotBase(GetPositionHead(), target, speed_shot,
														range_fire_shot, damage, type_effect, TypeObject::ENEMY);
		} break;
		case TypeShot::RICOCHET:
		{
			shot = new ShotRicochet(GetPositionHead(), target, speed_shot,
														range_fire_shot, damage, type_effect, TypeObject::ENEMY);
		} break;
		default: break;
	}
	if(shot)
		Message::CreateShot(shot, this);
}