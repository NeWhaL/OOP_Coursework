#include "../include/class_ShotBase.h"

ShotBase::ShotBase(sf::Vector2f coordinates, sf::Vector2f direction,
                   float speed, float range_fire, float damage,
                   TypeEffect effect, TypeObject who_creator)
    : Shot(coordinates, direction, speed, range_fire, damage, effect,
           who_creator) {}

void ShotBase::SendMessage(Message *message) {}

ShotBase::~ShotBase(){};

bool ShotBase::CollisionWithObject(GameObject *object) {
  return Shot::CollisionWithObject(object);
}
