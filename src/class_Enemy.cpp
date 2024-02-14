#include "../include/class_Enemy.h"
#include "../include/class_Manager.h"

Enemy::Enemy(sf::Vector2f coordinates, float speed, float health, float damage, sf::Texture *main_texture):
			 GameObject{coordinates, speed, health, main_texture, 8, damage},
		 	 direction{sf::Vector2f{0.f, 0.f}},
			 amount_sprite_body{10} {}

Enemy::~Enemy() {}

void Enemy::Move(float dt) 
{
	Message::MessageMove(this, manager);
  coordinates.x += direction.x * speed * dt;
  coordinates.y += direction.y * speed * dt;
}

void Enemy::MoveSprite() { main_sprite->setPosition(coordinates.x, coordinates.y); }

bool Enemy::CollisionWithObject(GameObject *object) 
{
	// Направление у противника считается каждый раз и он всегда идет на игрока
	direction = manager->GetHero()->GetPositionHead() - coordinates;
	direction = NormalizationVector(direction);
	if (not GameObject::CollisionWithObject(object)) return false;
	direction.x *= -1;
	direction.y *= -1;
	return true;
}

void Enemy::Draw(sf::RenderWindow* window) const { GameObject::Draw(window); }