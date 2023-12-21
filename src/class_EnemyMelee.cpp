#include "../include/class_EnemyMelee.h"
#include "../include/class_Manager.h"

EnemyMelee::EnemyMelee(sf::Vector2f coordinates, float speed, float health,
                       float attack_cooldown, float damage)
    : Enemy(coordinates, speed, health, attack_cooldown, damage,
            ResourceManager::GetInstance()->getTHeroHead()) {
  type = TypeObject::ENEMY;
  amount_sprite = 8;
}

EnemyMelee::~EnemyMelee() {}

void EnemyMelee::Move(float dt) { Enemy::Move(dt); }

void EnemyMelee::MoveSprite() {
  main_sprite->setPosition(coordinates.x, coordinates.y);
}

void EnemyMelee::Draw(sf::RenderWindow *window) const {
  window->draw(*main_sprite);
}

void EnemyMelee::Update(float dt) {
  cooldown_counter_time += dt;
  Move(dt);
  MoveSprite();
  GameObject::CollisionWithWall();
}

void EnemyMelee::SendMessage(Message *message) {
  switch (message->type_message) {
  default:
    if (message->who_sent == this)
      return;
  }
}

bool EnemyMelee::CollisionWithObject(GameObject *object) {
  return Enemy::CollisionWithObject(object);
}
