#ifndef MNGRES
#define MNGRES
#include "main.h"

class ResourceManager {
private:
  static ResourceManager *resource_manager;
  sf::Texture *sprite_room;
  sf::Texture *hero_head;
  sf::Texture *hero_legs_up_down;
  sf::Texture *hero_legs_left;
  sf::Texture *hero_legs_right;
  sf::Texture *shot;
  sf::Texture *head_enemy;
  sf::Texture *explosion;

  ResourceManager();
  ResourceManager(const ResourceManager &);
  ~ResourceManager();

public:
  static ResourceManager *GetInstance();
  sf::Texture *getTHeroHead() const;
  sf::Texture *getTHeroLegsUpDown() const;
  sf::Texture *getTHeroLegsLeft() const;
  sf::Texture *getTHeroLegsRight() const;
  sf::Texture *getTShot() const;
  sf::Texture *getTEffectBomb() const;
  sf::Texture *getTEnemyHead() const;
  sf::Texture *getTRoom() const;
};
#endif
