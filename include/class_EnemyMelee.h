#ifndef ENMELEE
#define ENMELEE

#include "class_Enemy.h"

class EnemyMelee : public Enemy {
private:
  sf::Sprite *head;
  sf::Sprite *body;
  int amount_sprite_head = 8;

  void Move(float dt) override;
  void MoveSprite() override;

public:
  EnemyMelee(sf::Vector2f coordinates, float speed, float health,
             float attack_cooldown);
  ~EnemyMelee();
  void SendMessage(Message *message) override;
  void Draw(sf::RenderWindow *window) const override;
  void Update(float dt) override;
  bool CollisionWithObject(GameObject *object) override;
};
#endif
