#include "../include/class_Enemy.h"
#include "../include/class_Manager.h"
#include <SFML/Graphics/Texture.hpp>

Enemy::Enemy(sf::Vector2f coordinates, float speed, float health, float damage, int amount_sprite_head, int amount_sprite_legs, 
						 sf::Texture* head_texture, sf::Texture* legs_up_down_texture, sf::Texture* legs_left_texture, 
						 sf::Texture* legs_right_texture):
			 GameObject{coordinates, speed, health, damage, amount_sprite_head, amount_sprite_legs, 0.5f,
			 						head_texture, legs_up_down_texture, legs_left_texture, legs_right_texture},	
			 hero{manager->GetHero()} {}

void Enemy::Move(float dt) 
{
	Message::Move(this);
  coordinates.x += direction.x * speed * dt;
  coordinates.y += direction.y * speed * dt;
}

void Enemy::DirectionOnHero()
{
	direction = hero->GetPositionHead() - coordinates;
	direction = NormalizationVector(direction);
	if (not GameObject::CollisionWithObject(hero)) 
		return;
	if (direction.x > 0 and direction.y > 0)
	{
		direction.x *= -1;
		direction.y *= -1;
	}
}