#ifndef ENM
#define ENM
#include "class_GameObject.h"

class Enemy : public GameObject {
protected:
  sf::Vector2f direction;

  virtual bool CollisionWithObject(GameObject *object) override;

public:
  Enemy(sf::Vector2f coordinates, float speed, float health,
        float damage, sf::Texture *main_texture);
  virtual ~Enemy();
  virtual void Move(float dt) override;
  void Draw(sf::RenderWindow* window) const override;
};
#endif
