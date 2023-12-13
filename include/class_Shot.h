#ifndef SHOT
#define SHOT

#include "class_GameObject.h"

enum class TypeEffect { NONE, TORNADO, BLEEDING, EXPLOSION };

class Shot : public GameObject {
protected:
  sf::Sprite *sprite;

  float damage;
  float range_fire;
  sf::Vector2f direction;
  TypeEffect effect;

  void Move(float dt);
  void MoveSprite();

public:
  Shot(sf::Vector2f coordinates, sf::Vector2f direction, float speed,
       float range_fire, float damage, TypeEffect effect);
  virtual ~Shot();
  void Update(float dt);
  void SendMessage(Message *message);
  void Draw(sf::RenderWindow *window) const;
};
#endif
