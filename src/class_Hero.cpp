#include "../include/class_Hero.h"
#include "../include/class_Manager.h"

Hero::Hero(sf::Vector2f coordinates, float speed, float health,
           float shot_cooldown_total, float melee_cooldown_total, float damage):
			  GameObject{coordinates, speed, health, damage, 8, 10, 0.5f,
									 res_manager->getTHeroHead(),
									 res_manager->getTHeroLegsUpDown(),
									 res_manager->getTHeroLegsLeft(),
									 res_manager->getTHeroLegsRight()},
			  shot_cooldown_total{shot_cooldown_total}, 
				shot_cooldown{0},
				current_type_shot{TypeShot::THROUGHT},
			  current_effect_shot{TypeEffect::EXPLOSION},
			  range_fire_shot{800}, 
				speed_shot{100}
{
	float speed_shot = 500;
	float range_fire_shot = 1000;
	type_object = TypeObject::PLAYER;
	creator = TypeObject::NONE;
	amount_money = 10;
	// время, которое игрок не получает урон полсле нанесения ему урона (в секундах)
	cooldown_take_time = 1;
	// накопленное время после нанесения урона герою
	time_after_damage_is_done = 0;
}

void Hero::Update(float dt) 
{
	time_after_damage_is_done += dt;
	Move(dt);
  MoveSprite();
  GameObject::CollisionWithWall();
	shot_cooldown += dt;	
  CreateShot(dt);
}

void Hero::Move(float dt) 
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) and
		 sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
	{
		coordinates.x += speed * dt / sqrt(2);
		coordinates.y += speed * -dt / sqrt(2);
	} 
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) and
		      sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
	{
		coordinates.x += speed * -dt / sqrt(2);
		coordinates.y += speed * -dt / sqrt(2);
	} 
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) and
				sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
	{
	  coordinates.x += speed * dt / sqrt(2);
		coordinates.y += speed * dt / sqrt(2);
	} 
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) and
				sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
	{
		coordinates.x += speed * -dt / sqrt(2);
		coordinates.y += speed * dt / sqrt(2);
	} 
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		 coordinates.y += speed * -dt;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
		 coordinates.x += speed * -dt;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		 coordinates.y += speed * dt;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		 coordinates.x += speed * dt;

	Message::Move(this);
}

void Hero::CreateShot(float dt) 
{
  shot_cooldown += dt;
  if (shot_cooldown < shot_cooldown_total or
     (not(sf::Mouse::isButtonPressed(sf::Mouse::Left) or
          sf::Mouse::isButtonPressed(sf::Mouse::Right))))
		return;

	shot_cooldown = 0;
  sf::Vector2i cur_mouse_pos = sf::Mouse::getPosition(*manager->GetWindow());
	cur_mouse_pos = static_cast<sf::Vector2i>(CurrentCoordinatesOfTheObjectRelativeToAnotherObject(
									static_cast<sf::Vector2f>(cur_mouse_pos), GetPositionHead()));
  sf::Vector2f normalized_mouse_position =
 	    NormalizationVector(static_cast<sf::Vector2f>(cur_mouse_pos));

	ShotSelectionToCreate(normalized_mouse_position);
}

void Hero::ShotSelectionToCreate(sf::Vector2f mouse_pos) 
{
	Shot* shot = nullptr;
	switch(current_type_shot)
	{
		case TypeShot::NONE:
		case TypeShot::BASE:
		{
			shot = new ShotBase(GetPositionHead(), mouse_pos, speed_shot,
														range_fire_shot, damage, current_effect_shot, TypeObject::PLAYER);
		} break;
		case TypeShot::RICOCHET:
		{
			shot = new ShotRicochet(GetPositionHead(), mouse_pos, speed_shot,
														range_fire_shot, damage, current_effect_shot, TypeObject::PLAYER);
		} break;
		case TypeShot::THROUGHT:
		{
			shot = new ShotThrought(GetPositionHead(), mouse_pos, speed_shot,
														range_fire_shot, damage, current_effect_shot, TypeObject::PLAYER);
		} break;
	}
	if(shot)
		Message::CreateShot(shot, this);
}

bool Hero::CollisionWithObject(const GameObject * const object) 
{
	return GameObject::CollisionWithObject(object) and object->GetCreatorObject() != TypeObject::PLAYER;
}

void Hero::SendMessage(Message *message) 
{		
	if (message->who_sent == this)
		return;
	switch (message->type_message) 
  {
	  case TypeMessage::MOVE:
		{
			auto& damage_object = message->who_sent;
		  if (not CollisionWithObject(damage_object)) return;
			if (time_after_damage_is_done < cooldown_take_time) return;
			time_after_damage_is_done = 0;
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
					if (not CollisionWithEffect(effect)) return;
					health -= effect->GetDamage();
					if (health <= 0) DeathObject(message->who_sent);
				} break;
				default: break;
			}
	  } break;
		case TypeMessage::ITEM:
		{
		  damage += message->item.damage;
		  speed += message->item.speed;
			range_fire_shot += message->item.range_fire;
			health += message->item.health;
			current_effect_shot = message->item.type_effect;
			current_type_shot = message->item.type_shot;
		} break;
	  default: break;
  }
}

bool Hero::CollisionWithEffect(Effect* effect) const
{
	if (effect->GetCreator() == TypeObject::PLAYER) return false;
	switch (effect->GetTypeEffect())
	{
		case TypeEffect::EXPLOSION:
		{
			EffectExplosion* effect_explosion = static_cast<EffectExplosion*>(effect);
			return radius_hitbox_head + effect_explosion->GetKillRadius() >=
			  LengthBetweenTwoPoints(GetPositionHead(), effect_explosion->GetCoordinates());
		} break;
		default: break;
	}
	return false;
}

void Hero::DeathObject(GameObject* killer)
{
	Message::EndGame(TypeEndGame::DEATH_HERO);
	// добавить выход из игры если герой погиб
}
