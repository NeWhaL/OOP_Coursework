#include "../include/class_ShotBase.h"

ShotBase::ShotBase(sf::Vector2f coordinates, sf::Vector2f direction,
                   float speed, float range_fire, float damage,
                   TypeEffect effect, WhoCreatedShot who)
    : Shot(coordinates, direction, speed, range_fire, damage, effect, who) {}

void ShotBase::SendMessage(Message *message) {}

ShotBase::~ShotBase(){};

bool ShotBase::CollisionWithObject(GameObject *object) { return true; }
