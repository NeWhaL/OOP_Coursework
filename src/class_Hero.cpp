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

void Hero::Update(float ft) {}

void Hero::Draw(sf::RenderWindow *window) const {
  head->setTextureRect(sf::IntRect(0, 0, 50, 50));
  window->draw(*head);
}
