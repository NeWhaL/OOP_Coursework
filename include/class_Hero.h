#include "class_GameObject.h"

class Shot;
class MelleWeapon;

class Hero : public GameObject {
private:
  std::vector<Shot> shots;
  MelleWeapon *sword;

  float speed;
  float shot_cooldown;
  float melee_cooldown;

public:
  Hero();
  ~Hero();
};
