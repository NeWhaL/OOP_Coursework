#include "../include/class_Enemy.h"
#include "../include/class_Manager.h"

Enemy::Enemy(sf::Vector2f coordinates, float speed, float health,
             float attack_cooldown)
    : GameObject(coordinates, speed, health), attack_cooldown(attack_cooldown),
      direction({0, 0}) {}

Enemy::~Enemy() {}

void Enemy::Move(float dt) {
  Message *message = new Message;
  message->who_sent = this;
  message->type_message = TypeMessage::MOVE;
  Manager *manager = Manager::GetInstance();
  manager->SendMessage(message);
  coordinates.x += direction.x * speed * dt;
  coordinates.y += direction.y * speed * dt;
}

bool Enemy::CollisionWithObject(GameObject *object) {
  Manager *manager = Manager::GetInstance();
  object = manager->GetHero();
  direction = object->GetPosition() - coordinates;
  direction = NormalizationVector(direction);
  if (GameObject::CollisionWithObject(object)) {
    direction.x *= -1;
    direction.y *= -1;
  } else
    return false;
  if (attack_cooldown > cooldown_counter_time)
    return true;
  Message *message = new Message;
  message->who_sent = this;
  message->type_message = TypeMessage::DEAL_DAMAGE;
  message->deal_damage.damage = damage;
  message->deal_damage.to_who = object;
  Manager::GetInstance()->SendMessage(message);
  cooldown_counter_time = 0;
  return true;
}
