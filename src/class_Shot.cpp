#include "../include/class_Shot.h"
#include "../include/class_Manager.h"

Shot::Shot(sf::Vector2f coordinates, sf::Vector2f direction, float speed,
           float range_fire, float damage, TypeEffect effect,
           WhoCreatedShot who)
    : GameObject(coordinates, speed, 1), direction(direction), damage(damage),
      range_fire(range_fire), effect(effect), sprite(nullptr), creator(who) {
  sprite = new sf::Sprite;
  sprite->setTexture(*ResourceManager::GetInstance()->getTShot());
  sf::FloatRect bounds_shot = sprite->getLocalBounds();
  sprite->setOrigin(bounds_shot.width / 2, bounds_shot.height / 2);
  radius_hitbox = bounds_shot.height / 2;
}

void Shot::Update(float dt) {
  Move(dt);
  MoveSprite();
  CollisionWithWall();
}

void Shot::CollisionWithWall() {
  Manager *manager = Manager::GetInstance();
  Size_arena tmp_size = manager->GetSizeArena();
  if (not(coordinates.x - radius_hitbox < tmp_size.up_left.x or
          coordinates.x + radius_hitbox > tmp_size.down_right.x or
          coordinates.y - radius_hitbox < tmp_size.up_left.y or
          coordinates.y + radius_hitbox > tmp_size.down_right.y))
    return;
  Message *message = new Message;
  message->type_message = TypeMessage::DEATH;
  message->who_sent = this;
  message->death.killer = nullptr;
  message->death.who_die = this;
  manager->SendMessage(message);
}

void Shot::Move(float dt) {
  sf::Vector2f delta_position = coordinates;
  coordinates.x += direction.x * speed * dt;
  coordinates.y += direction.y * speed * dt;
  delta_position -= coordinates;
  float length_delta_vector = LengthVector(delta_position);
  range_fire -= length_delta_vector;
  if (range_fire > 0)
    return;
  Message *message = new Message;
  message->type_message = TypeMessage::DEATH;
  message->death.who_die = this;
  message->death.killer = nullptr;
  Manager::GetInstance()->SendMessage(message);
}

void Shot::MoveSprite() { sprite->setPosition(coordinates.x, coordinates.y); }

void Shot::SendMessage(Message *message) {}

void Shot::Draw(sf::RenderWindow *window) const { window->draw(*sprite); }

Shot::~Shot() { delete sprite; }
