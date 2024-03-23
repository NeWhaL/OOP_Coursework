#ifndef SHOTRICOCHET
#define SHOTRICOCHET
#include "class_Shot.h"

class ShotRicochet : public Shot
{
private:
  void CollisionWithWall();
  bool CollisionWithObject(const GameObject* const object);

public:
  ShotRicochet(sf::Vector2f coordinates, sf::Vector2f direction,
               float speed, float range_fire, float damage, TypeEffect effect,
               TypeObject who_creator);
  void SendMessage(Message* message);
};

#endif