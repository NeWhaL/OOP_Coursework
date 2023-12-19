#ifndef HERO
#define HERO

#include "class_GameObject.h"
#include "class_ManagerResource.h"
#include "class_ShotBase.h"

class Hero : public GameObject {
private:
  float health;
  float damage;
  float shot_cooldown_total;
  float shot_cooldown;
  float melee_cooldown;
  float melee_cooldown_total;
  int amount_sprite_head = 8;
  int amount_sprite_legs_up_down = 10;

  sf::Sprite *head;
  sf::Sprite *legs_up_down;
  sf::Sprite *legs_left;
  sf::Sprite *legs_right;

  void Move(float dt) override;
  void MoveSprite();
  void CreateShot(float dt);
  void CollisionWithObject() override;

public:
  Hero(sf::Vector2f coordinates, float speed, float health,
       float shot_cooldown_total, float melee_cooldown_total, float damage);
  ~Hero();

  void Draw(sf::RenderWindow *window) const override;
  void Update(float dt) override;
  void SendMessage(Message *message) override;
};
#endif
