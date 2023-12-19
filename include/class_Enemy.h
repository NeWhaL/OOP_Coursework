#ifndef ENEMY
#define ENEMY
#include "class_GameObject.h"

class Enemy : public GameObject {
protected:
  float health;
  sf::Vector2f direction;
  float damage;
  float attack_cooldown;

public:
  Enemy(sf::Vector2f coordinates, float speed, float health,
        float attack_cooldown);
  virtual ~Enemy();
  virtual void Draw(sf::RenderWindow *window) const = 0;
  virtual void Move(float dt);
  virtual void MoveSprite() = 0;
};
#endif
