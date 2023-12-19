#ifndef SHOT
#define SHOT

#include "class_GameObject.h"

enum class TypeEffect { NONE, TORNADO, BLEEDING, EXPLOSION };
enum class WhoCreatedShot { PLAYER, ENEMY };

class Shot : public GameObject {
protected:
  sf::Sprite *sprite;

  float damage;
  float range_fire;
  sf::Vector2f direction;
  TypeEffect effect;
  WhoCreatedShot creator;

  void Move(float dt);
  void MoveSprite();
  virtual void CollisionWithWall();

public:
  Shot(sf::Vector2f coordinates, sf::Vector2f direction, float speed,
       float range_fire, float damage, TypeEffect effect, WhoCreatedShot who);
  virtual ~Shot();
  void Update(float dt);
  void SendMessage(Message *message);
  void Draw(sf::RenderWindow *window) const;
};
#endif
