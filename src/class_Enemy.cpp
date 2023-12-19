#include "../include/class_Enemy.h"
#include "../include/class_Manager.h"

Enemy::Enemy(sf::Vector2f coordinates, float speed, float health,
             float attack_cooldown)
    : GameObject(coordinates, speed), health(health),
      attack_cooldown(attack_cooldown), direction({0, 0}) {}

Enemy::~Enemy() {}

void Enemy::Move(float dt) {
  Message *message = new Message;
  message->who_sent = this;
  message->type_message = TypeMessage::MOVE;
  Manager *manager = Manager::GetInstance();
  manager->SendMessage(message);
  Hero *hero = manager->GetHero();
  direction = hero->GetPosition() - coordinates;
  direction = NormalizationVector(direction);
  coordinates.x += direction.x * speed * dt;
  coordinates.y += direction.y * speed * dt;
}
