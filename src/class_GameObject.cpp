#include "../include/class_GameObject.h"

GameObject::GameObject() : coordinates(0, 0) {}

GameObject::~GameObject() {}

sf::Vector2f GameObject::CurrentPosition() const { return coordinates; }

void GameObject::SetPosition(sf::Vector2f coordinates) {
  this->coordinates = coordinates;
}

sf::Vector2f GameObject::GetPosition() const { return coordinates; }
