#ifndef SHOTBASE
#define SHOTBASE

#include "class_Shot.h"

class ShotBase : public Shot 
{
private:
   bool CollisionWithObject(const GameObject * const object);

public:
   ShotBase(sf::Vector2f coordinates, sf::Vector2f direction, float speed,
            float range_fire, float damage, TypeEffect effect,
            TypeObject who_creator);
   void SendMessage(Message *message);
};

#endif
