#include "class_GameObject.h"
#include "class_ManagerResource.h"

class Hero : public GameObject {
private:
  float speed;
  float shot_cooldown;
  float melee_cooldown;

  sf::Sprite *head;
  sf::Sprite *legs_up_down;
  sf::Sprite *legs_left;
  sf::Sprite *legs_right;

public:
  Hero();
  ~Hero();
  void Draw(sf::RenderWindow *window) const;
  void Update(float dt);
};
