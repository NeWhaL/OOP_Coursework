#ifndef SHOTBASE
#define SHOTBASE

#include "class_Shot.h"

class ShotBase : public Shot {
private:
public:
  ShotBase(sf::Vector2f coordinates, sf::Vector2f direction, float speed,
           float range_fire, float damage, TypeEffect effect);
  virtual ~ShotBase();
  void SendMessage(Message *message);
};

#endif
