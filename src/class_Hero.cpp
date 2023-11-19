#include "../include/class_Hero.h"

Hero::Hero() : GameObject(), speed(200), shot_cooldown(10), melee_cooldown(10) {
  head = new sf::Sprite;
  legs_up_down = new sf::Sprite;
  legs_left = new sf::Sprite;
  legs_right = new sf::Sprite;

  head->setTexture(*ResourceManager::getInstance()->getTHeroHead());
  legs_up_down->setTexture(
      *ResourceManager::getInstance()->getTHeroLegsUpDown());
  legs_left->setTexture(*ResourceManager::getInstance()->getTHeroLegsLeft());
  legs_right->setTexture(*ResourceManager::getInstance()->getTHeroLegsRight());
}

Hero::~Hero() {}

void Hero::Update(float dt) { Move(dt); }

void Hero::Move(float dt) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    coordinates.y += speed * -dt;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    coordinates.x += speed * -dt;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    coordinates.y += speed * dt;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    coordinates.x += speed * dt;
  }
  MoveSprite();
}

void Hero::MoveSprite() { head->setPosition(coordinates.x, coordinates.y); }

void Hero::Draw(sf::RenderWindow *window) const {
  head->setTextureRect(sf::IntRect(0, 0, 50, 50));
  window->draw(*head);
}
