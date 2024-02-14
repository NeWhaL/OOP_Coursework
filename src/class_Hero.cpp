#include "../include/class_Hero.h"
#include "../include/class_Manager.h"


Hero::Hero(sf::Vector2f coordinates, float speed, float health,
           float shot_cooldown_total, float melee_cooldown_total, float damage):
			  GameObject(coordinates, speed, health, ResourceManager::GetInstance()->getTHeroHead(), 8,	damage),
			  shot_cooldown_total(shot_cooldown_total), 
				shot_cooldown(0),
			  current_effect_shot(TypeEffect::NONE),
			  range_fire_shot(400), 
				speed_shot(350)
{
	type_object = TypeObject::PLAYER;
	creator = TypeObject::NONE;
	// время, которое игрок не получает урон полсле нанесения ему урона (в секундах)
	cooldown_take_time = 1;
	// накопленное время после нанесения урона герою
	time_after_damage_is_done = 0;

	ResourceManager *RM = ResourceManager::GetInstance();
	legs_up_down = new sf::Sprite;
	legs_left = new sf::Sprite;
	legs_right = new sf::Sprite;
	legs_up_down->setTexture(*RM->getTHeroLegsUpDown());
	legs_up_down->setScale(0.5 , 0.5);
	legs_left->setTexture(*RM->getTHeroLegsLeft());
	legs_left->setScale(0.5 , 0.5);
	legs_right->setTexture(*RM->getTHeroLegsRight());
	legs_right->setScale(0.5 , 0.5);

	sf::FloatRect bounds_legs_up_down = legs_up_down->getLocalBounds();
	legs_up_down->setTextureRect(
	    sf::IntRect(0, 0, bounds_legs_up_down.width / amount_sprite_legs_up_down,
	                bounds_legs_up_down.height));
	legs_up_down->setOrigin(bounds_legs_up_down.width / amount_sprite_legs_up_down / 2,
                           bounds_legs_up_down.height / 2);
	radius_hitbox_legs = legs_up_down->getGlobalBounds().height / 2;
}

Hero::~Hero() 
{
	delete legs_up_down;
  delete legs_right;
  delete legs_left;
}

void Hero::Update(float dt) 
{
	Move(dt);
   MoveSprite();
   GameObject::CollisionWithWall();
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

	Message::MessageMove(this, manager);
}

void Hero::MoveSprite() 
{
   legs_up_down->setPosition(coordinates.x, coordinates.y);
   main_sprite->setPosition(coordinates.x, coordinates.y - legs_up_down->getLocalBounds().height +
									 legs_up_down->getGlobalBounds().height);
}

void Hero::CreateShot(float dt) 
{
   shot_cooldown += dt;
   if (shot_cooldown < shot_cooldown_total or
      (not(sf::Mouse::isButtonPressed(sf::Mouse::Left) or
           sf::Mouse::isButtonPressed(sf::Mouse::Right))))
		 return;

	shot_cooldown = 0;
  sf::Vector2i current_mouse_position =
      sf::Mouse::getPosition(*manager->GetWindow());
  current_mouse_position = MouseCoordinatesRelativeOtherCoordinates(
      current_mouse_position, main_sprite->getPosition());
  sf::Vector2f normalized_mouse_position =
      NormalizationVector(static_cast<sf::Vector2f>(current_mouse_position));

	Shot* shot = new ShotBase(main_sprite->getPosition(), normalized_mouse_position, speed_shot,
														range_fire_shot, damage, current_effect_shot, TypeObject::PLAYER);
	Message::MessageCreateShot(shot, this, manager);
}

void Hero::Draw(sf::RenderWindow *window) const 
{
   window->draw(*legs_up_down);
   GameObject::Draw(window);
}

bool Hero::CollisionWithObject(GameObject *object) 
{
		return object->GetCreatorObject() == TypeObject::PLAYER and 
					 cooldown_take_time > time_after_damage_is_done and
					 not GameObject::CollisionWithObject(object) and 
					 object->GetCreatorObject() != TypeObject::SHOT and 
					 object->GetCreatorObject() != TypeObject::ENEMY;
}

void Hero::SendMessage(Message *message) 
{		
	if (message->who_sent == this)
		return;
	switch (message->type_message) 
  {
	  case TypeMessage::MOVE:
		{
		  if (not CollisionWithObject(message->who_sent))	return;
			auto& damage_object = message->who_sent;
			health -= damage_object->GetDamage();
			if (health <= 0) DeathObject(damage_object);
		} break;
	  case TypeMessage::EFFECT:
	  {
		  switch(message->effect.type)
			{ 
			  case TypeEffect::EXPLOSION:
			  {
				  if (not (message->effect.creator != TypeObject::PLAYER and 
					 	  GameObject::CollisionWithObject(message->who_sent)))
					  return;
				  health -= message->effect.damage;
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

void Hero::DeathObject(GameObject* killer)
{
	// добавить выход из игры если герой погиб
}
