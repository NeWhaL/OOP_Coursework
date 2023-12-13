#ifndef HERO
#define HERO

#include "class_GameObject.h"
#include "class_ManagerResource.h"
#include "class_ShotBase.h"

class Hero : public GameObject {
private:
  float shot_cooldown_total;
  float shot_cooldown;
  float melee_cooldown;

  sf::Sprite *head;
  sf::Sprite *legs_up_down;
  sf::Sprite *legs_left;
  sf::Sprite *legs_right;

  void Move(float dt);
  void MoveSprite();
  void CreateShot(float dt);

public:
  Hero();
  ~Hero();

  void Draw(sf::RenderWindow *window) const;
  void Update(float dt);
  void SendMessage(Message *message);
};
#endif
