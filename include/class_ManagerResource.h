#ifndef MNGRES
#define MNGRES
#include "main.h"

class ResourceManager {
private:
  static ResourceManager *resource_manager;
  sf::Texture *hero_head;
  sf::Texture *hero_legs_up_down;
  sf::Texture *hero_legs_left;
  sf::Texture *hero_legs_right;
  sf::Texture *shot;

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
};
#endif
