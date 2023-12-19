#ifndef ENMELEE
#define ENMELEE

#include "class_Enemy.h"

class EnemyMelee : public Enemy {
private:
  sf::Sprite *head;
  sf::Sprite *body;
  int amount_sprite_head = 8;

  virtual void Move(float dt);
  void MoveSprite();

public:
  EnemyMelee(sf::Vector2f coordinates, float speed, float health,
             float attack_cooldown);
  ~EnemyMelee();
  void SendMessage(Message *message);
  void Draw(sf::RenderWindow *window) const;
  void Update(float dt);
};
#endif
