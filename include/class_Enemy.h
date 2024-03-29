#ifndef ENM
#define ENM
#include "class_GameObject.h"
#include "class_Hero.h"

//Для конструкторов в конечных классах противников
struct EnemyCharacteristics
{
  sf::Vector2f coordinates;
  float speed;
  float health;
  float damage;
  int amount_money;
};

class Enemy : public GameObject {
protected:
  const Hero* const hero;

  virtual void DirectionOnHero();
  bool CollisionWithEffect(Effect* effect) const;

public:
  Enemy(sf::Vector2f coordinates, float speed, float health, float damage, int amount_sprite_head,
        int amount_sprite_legs, sf::Texture* head_texture, sf::Texture* legs_up_down_texture, 
        sf::Texture* legs_left_texture, sf::Texture* legs_right_texture);
  virtual ~Enemy() = default;
  virtual void Move(float dt);
};
#endif
