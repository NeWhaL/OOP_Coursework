#include "../include/class_EnemyMelee.h"
#include "../include/class_Manager.h"

EnemyMelee::EnemyMelee(sf::Vector2f coordinates, float speed, float health,
                       float attack_cooldown)
    : Enemy(coordinates, speed, health, attack_cooldown) {
  ResourceManager *RM = ResourceManager::GetInstance();
  head = new sf::Sprite;
  head->setTexture(*RM->getTHeroHead());

  sf::FloatRect bounds_head = head->getLocalBounds();
  head->setTextureRect(sf::IntRect(0, 0, bounds_head.width / amount_sprite_head,
                                   bounds_head.height));
  head->setOrigin(bounds_head.width / amount_sprite_head / 2,
                  bounds_head.height / 2);
  radius_hitbox = bounds_head.height / 2;
}

EnemyMelee::~EnemyMelee() { delete head; }

void EnemyMelee::Move(float dt) { Enemy::Move(dt); }

void EnemyMelee::MoveSprite() {
  head->setPosition(coordinates.x, coordinates.y);
}

void EnemyMelee::Draw(sf::RenderWindow *window) const { window->draw(*head); }

void EnemyMelee::Update(float dt) {
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
