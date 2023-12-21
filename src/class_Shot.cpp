#include "../include/class_Shot.h"
#include "../include/class_Manager.h"

Shot::Shot(sf::Vector2f coordinates, sf::Vector2f direction, float speed,
           float range_fire, float damage, TypeEffect effect,
           TypeObject who_creator)
    : GameObject(coordinates, speed, 1,
                 ResourceManager::GetInstance()->getTShot(), 1),
      direction(direction), damage(damage), range_fire(range_fire),
      effect(effect), creator(who_creator) {
  type = TypeObject::SHOT;
  amount_sprite = 1;
}

void Shot::Update(float dt) {
  Move(dt);
  MoveSprite();
  CollisionWithWall();
}

void Shot::CollisionWithWall() {
  Manager *manager = Manager::GetInstance();
  Size_arena tmp_size = manager->GetSizeArena();
  if (not(coordinates.x - radius_hitbox_head < tmp_size.up_left.x or
          coordinates.x + radius_hitbox_head > tmp_size.down_right.x or
          coordinates.y - radius_hitbox_head < tmp_size.up_left.y or
          coordinates.y + radius_hitbox_head > tmp_size.down_right.y))
    return;
  Message *message = new Message;
  message->type_message = TypeMessage::DEATH;
  message->who_sent = this;
  message->death.killer = nullptr;
  message->death.who_die = this;
  manager->SendMessage(message);
}

bool Shot::CollisionWithObject(GameObject *object) {
  if ((object == Manager::GetInstance()->GetHero() and
       creator == TypeObject::PLAYER) or
      object == this or type == object->GetTypeObject() or
      (creator == object->GetTypeObject()))
    return false;
  if (not GameObject::CollisionWithObject(object))
    return false;
  Manager *manager = Manager::GetInstance();
  Message *message_deal_damage = new Message;
  message_deal_damage->who_sent = this;
  message_deal_damage->type_message = TypeMessage::DEAL_DAMAGE;
  message_deal_damage->deal_damage.damage = damage;
  message_deal_damage->deal_damage.to_who = object;
  manager->SendMessage(message_deal_damage);

  Message *message_death_shot = new Message;
  message_death_shot->who_sent = this;
  message_death_shot->type_message = TypeMessage::DEATH;
  message_death_shot->death.killer = this;
  message_death_shot->death.who_die = this;
  manager->SendMessage(message_death_shot);

  if (object->GetHealth() > 0)
    return true;
  Message *message_death_object = new Message;
  message_death_object->who_sent = object;
  message_death_object->type_message = TypeMessage::DEATH;
  message_death_object->death.killer = this;
  message_death_object->death.who_die = object;
  manager->SendMessage(message_death_object);
  return true;
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

void Shot::MoveSprite() {
  main_sprite->setPosition(coordinates.x, coordinates.y);
}

void Shot::SendMessage(Message *message) {}

void Shot::Draw(sf::RenderWindow *window) const { window->draw(*main_sprite); }

Shot::~Shot() {}
