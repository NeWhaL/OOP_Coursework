#include "../include/class_ManagerResource.h"

ResourceManager *ResourceManager::resource_manager = nullptr;

ResourceManager::ResourceManager() {
  hero_head = new sf::Texture;
  hero_head->loadFromFile("images/hero_head_alpha.png");
  hero_legs_up_down = new sf::Texture;
  hero_legs_up_down->loadFromFile("images/hero_legs_up_down.png");
  hero_legs_left = new sf::Texture;
  hero_legs_left->loadFromFile("images/hero_legs_left.png");
  hero_legs_right = new sf::Texture;
  hero_legs_right->loadFromFile("images/hero_legs_right.png");
}

ResourceManager *ResourceManager::getInstance() {
  if (not resource_manager) {
    resource_manager = new ResourceManager;
  }
  return resource_manager;
}

sf::Texture *ResourceManager::getTHeroHead() const { return hero_head; }
sf::Texture *ResourceManager::getTHeroLegsUpDown() const {
  return hero_legs_up_down;
}
sf::Texture *ResourceManager::getTHeroLegsLeft() const {
  return hero_legs_left;
}
sf::Texture *ResourceManager::getTHeroLegsRight() const {
  return hero_legs_right;
}
