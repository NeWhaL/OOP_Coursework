#include "../include/class_GameObject.h"
#include "../include/class_Manager.h"

GameObject::GameObject() {}

GameObject::GameObject(sf::Vector2f coordinates, float speed, float health)
    : coordinates(coordinates), speed(speed), health(health) {}

GameObject::~GameObject() {}

void GameObject::SetPosition(sf::Vector2f coordinates) {
  this->coordinates = coordinates;
}

float GameObject::GetRadiusHitbox() const { return radius_hitbox; }

sf::Vector2f GameObject::GetPosition() const { return coordinates; }

void GameObject::CollisionWithWall() {
  Manager *manager = Manager::GetInstance();
  Size_arena tmp_size = manager->GetSizeArena();
  float d_x = 0.f;
  float d_y = 0.f;
  if (coordinates.x - radius_hitbox < tmp_size.up_left.x)
    d_x = tmp_size.up_left.x - (coordinates.x - radius_hitbox);
  else if (coordinates.x + radius_hitbox > tmp_size.down_right.x)
    d_x = tmp_size.down_right.x - (coordinates.x + radius_hitbox);
  if (coordinates.y - radius_hitbox < tmp_size.up_left.y)
    d_y = tmp_size.up_left.y - (coordinates.y - radius_hitbox);
  else if (coordinates.y + radius_hitbox > tmp_size.down_right.y)
    d_y = tmp_size.down_right.y - (coordinates.y + radius_hitbox);
  coordinates.x += d_x;
  coordinates.y += d_y;
}

bool GameObject::CollisionWithObject(GameObject *object) {
  return radius_hitbox + object->radius_hitbox >=
         LengthBetweenTwoPoints(coordinates, object->coordinates);
}
