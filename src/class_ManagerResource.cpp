#include "../include/class_ManagerResource.h"

ResourceManager *ResourceManager::resource_manager = nullptr;

ResourceManager::ResourceManager() 
{
	sprite_room = new sf::Texture;
	sprite_room->loadFromFile("images/Basement_main.png");
	hero_head = new sf::Texture;
	hero_head->loadFromFile("images/head_isaac.png");	
	hero_legs_up_down = new sf::Texture;
	hero_legs_up_down->loadFromFile("images/isaac_legs_up_down.png");
	hero_legs_left = new sf::Texture;
	hero_legs_left->loadFromFile("images/hero_legs_left.png");
	hero_legs_right = new sf::Texture;
	hero_legs_right->loadFromFile("images/hero_legs_right.png");
	shot = new sf::Texture;
	shot->loadFromFile("images/shot.png");
	head_enemy = new sf::Texture;
	head_enemy->loadFromFile("images/enemy_head.png");
	explosion = new sf::Texture;
	explosion->loadFromFile("images/explosion.png");
}

ResourceManager *ResourceManager::GetInstance() {
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

sf::Texture *ResourceManager::getTShot() const { return shot; }

sf::Texture *ResourceManager::getTRoom() const { return sprite_room; }
sf::Texture *ResourceManager::getTEnemyHead() const { return head_enemy; }
sf::Texture *ResourceManager::getTEffectBomb() const
{
	return explosion;
}
