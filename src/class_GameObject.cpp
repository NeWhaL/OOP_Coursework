#include "../include/class_GameObject.h"

GameObject::GameObject() {}

GameObject::GameObject(sf::Vector2f coordinates, float speed)
    : coordinates(coordinates), speed(speed) {}

GameObject::~GameObject() {}

void GameObject::SetPosition(sf::Vector2f coordinates) {
  this->coordinates = coordinates;
}

sf::Vector2f GameObject::GetPosition() const { return coordinates; }
