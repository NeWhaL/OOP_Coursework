#ifndef SHOT_THROUGHT
#define SHOT_THROUGHT
#include "class_Shot.h"

class ShotThrought : public Shot
{
  float amount_of_time_to_do_damage;
  float timer;
  bool do_damage;

public:
  ShotThrought(sf::Vector2f coordinates, sf::Vector2f direction, 
               float speed, float range_fire, float damage,
               TypeEffect effect, TypeObject who_creator);
  void Update(float dt);
  void SendMessage(Message* message);
};

#endif