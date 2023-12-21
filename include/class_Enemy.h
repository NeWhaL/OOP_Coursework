#ifndef ENM
#define ENM
#include "class_GameObject.h"

class Enemy : public GameObject {
protected:
  sf::Vector2f direction;
  float damage;
  float attack_cooldown;
  float cooldown_counter_time = 0;

  virtual bool CollisionWithObject(GameObject *object) override;

public:
  Enemy(sf::Vector2f coordinates, float speed, float health,
        float attack_cooldown, float damage, sf::Texture *main_texture);
  virtual ~Enemy();
  virtual void Move(float dt) override;
};
#endif
