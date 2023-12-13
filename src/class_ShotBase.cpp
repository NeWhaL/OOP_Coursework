#include "../include/class_ShotBase.h"

ShotBase::ShotBase(sf::Vector2f coordinates, sf::Vector2f direction,
                   float speed, float range_fire, float damage,
                   TypeEffect effect)
    : Shot(coordinates, direction, speed, range_fire, damage, effect) {}

void ShotBase::SendMessage(Message *message) {}

ShotBase::~ShotBase(){};
