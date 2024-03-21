#include "../include/class_ManagerResource.h"

using namespace sf;

ResourceManager *ResourceManager::resource_manager = nullptr;

ResourceManager::ResourceManager() 
{
	sprite_room = new Texture;
	sprite_room->loadFromFile("images/Basement_main.png");
	hero_head = new Texture;
	hero_head->loadFromFile("images/head_isaac.png");	
	hero_legs_up_down = new Texture;
	hero_legs_up_down->loadFromFile("images/isaac_legs_up_down.png");
	hero_legs_left = new Texture;
	hero_legs_left->loadFromFile("images/hero_legs_left.png");
	hero_legs_right = new Texture;
	hero_legs_right->loadFromFile("images/hero_legs_right.png");
	shot = new Texture;
	shot->loadFromFile("images/shot.png");
	melee_head_enemy = new Texture;
	melee_head_enemy->loadFromFile("images/enemy_skull.png");
	range_head_enemy = new Texture;
	range_head_enemy->loadFromFile("images/enemy_head.png");
	support_head_enemy = new Texture;
	support_head_enemy->loadFromFile("images/enemy_twin.png");
	explosion = new Texture;
	explosion->loadFromFile("images/explosion.png");
}

ResourceManager *ResourceManager::GetInstance() {
  if (not resource_manager) {
    resource_manager = new ResourceManager;
  }
  return resource_manager;
}

Texture *ResourceManager::getTHeroHead() const { return hero_head; }
Texture *ResourceManager::getTHeroLegsUpDown() const {
  return hero_legs_up_down;
}
Texture *ResourceManager::getTHeroLegsLeft() const {
  return hero_legs_left;
}
Texture *ResourceManager::getTHeroLegsRight() const {
  return hero_legs_right;
}

Texture *ResourceManager::getTShot() const { return shot; }
Texture *ResourceManager::getTRoom() const { return sprite_room; }
Texture *ResourceManager::getTMeleeEnemyHead() const { return melee_head_enemy; }
Texture *ResourceManager::getTRangeEnemyHead() const { return range_head_enemy; }
Texture *ResourceManager::getTSupportEnemyHead() const { return support_head_enemy; }
Texture *ResourceManager::getTEffectBomb() const { return explosion; }
