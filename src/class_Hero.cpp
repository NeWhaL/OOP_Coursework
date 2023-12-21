#include "../include/class_Hero.h"
#include "../include/class_Manager.h"

Hero::Hero(sf::Vector2f coordinates, float speed, float health,
           float shot_cooldown_total, float melee_cooldown_total, float damage)
    : GameObject(coordinates, speed, health),
      shot_cooldown_total(shot_cooldown_total),
      melee_cooldown_total(melee_cooldown_total), shot_cooldown(0),
      melee_cooldown(0), damage(damage) {
  ResourceManager *RM = ResourceManager::GetInstance();
  head = new sf::Sprite;
  legs_up_down = new sf::Sprite;
  legs_left = new sf::Sprite;
  legs_right = new sf::Sprite;

  head->setTexture(*RM->getTHeroHead());
  legs_up_down->setTexture(*RM->getTHeroLegsUpDown());
  legs_left->setTexture(*RM->getTHeroLegsLeft());
  legs_right->setTexture(*RM->getTHeroLegsRight());

  sf::FloatRect bounds_head = head->getLocalBounds();
  head->setTextureRect(sf::IntRect(0, 0, bounds_head.width / amount_sprite_head,
                                   bounds_head.height));
  head->setOrigin(bounds_head.width / amount_sprite_head / 2,
                  bounds_head.height / 2);

  sf::FloatRect bounds_legs_up_down = legs_up_down->getLocalBounds();
  legs_up_down->setTextureRect(
      sf::IntRect(0, 0, bounds_legs_up_down.width / amount_sprite_legs_up_down,
                  bounds_legs_up_down.height));
  legs_up_down->setOrigin(bounds_legs_up_down.width /
                              amount_sprite_legs_up_down / 2,
                          bounds_legs_up_down.height / 2);
  radius_hitbox = bounds_head.height / 2;
}

Hero::~Hero() {
  delete head;
  delete legs_up_down;
  delete legs_right;
  delete legs_left;
}

void Hero::Update(float dt) {
  Move(dt);
  MoveSprite();
  GameObject::CollisionWithWall();
  CreateShot(dt);
}

void Hero::Move(float dt) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) or
      sf::Keyboard::isKeyPressed(sf::Keyboard::A) or
      sf::Keyboard::isKeyPressed(sf::Keyboard::S) or
      sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    Message *message = new Message;
    message->type_message = TypeMessage::MOVE;
    message->who_sent = this;
    Manager::GetInstance()->SendMessage(message);
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) and
      sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    coordinates.x += speed * dt / sqrt(2);
    coordinates.y += speed * -dt / sqrt(2);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) and
             sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    coordinates.x += speed * -dt / sqrt(2);
    coordinates.y += speed * -dt / sqrt(2);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) and
             sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    coordinates.x += speed * dt / sqrt(2);
    coordinates.y += speed * dt / sqrt(2);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) and
             sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    coordinates.x += speed * -dt / sqrt(2);
    coordinates.y += speed * dt / sqrt(2);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    coordinates.y += speed * -dt;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    coordinates.x += speed * -dt;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    coordinates.y += speed * dt;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    coordinates.x += speed * dt;
  }
}

void Hero::MoveSprite() {
  legs_up_down->setPosition(coordinates.x, coordinates.y);
  head->setPosition(coordinates.x,
                    coordinates.y - legs_up_down->getLocalBounds().height +
                        legs_up_down->getGlobalBounds().height / 11);
}

void Hero::CreateShot(float dt) {
  shot_cooldown += dt;
  if (shot_cooldown < shot_cooldown_total or
      (not(sf::Mouse::isButtonPressed(sf::Mouse::Left) or
           sf::Mouse::isButtonPressed(sf::Mouse::Right))))
    return;

  shot_cooldown = 0;
  sf::Vector2i current_mouse_position =
      sf::Mouse::getPosition(*Manager::GetInstance()->GetWindow());
  current_mouse_position = MouseCoordinatesRelativeOtherCoordinates(
      current_mouse_position, head->getPosition());
  sf::Vector2f normalized_mouse_position =
      NormalizationVector(static_cast<sf::Vector2f>(current_mouse_position));
  Message *message = new Message;
  message->type_message = TypeMessage::CREATE;
  message->create.new_object =
      new ShotBase(head->getPosition(), normalized_mouse_position, 200, 400, 10,
                   TypeEffect::NONE, WhoCreatedShot::PLAYER);
  message->create.creator = this;
  Manager::GetInstance()->SendMessage(message);
}

void Hero::Draw(sf::RenderWindow *window) const {
  window->draw(*legs_up_down);
  window->draw(*head);
}

bool Hero::CollisionWithObject(GameObject *object) {
  // if (radius_hitbox + object->GetRadiusHitbox() <
  //     LengthBetweenTwoPoints(coordinates, object->GetPosition()))
  return true;
}

void Hero::SendMessage(Message *message) {
  // switch (message->type_message) {
  // case TypeMessage::MOVE: {
  // } break;
  // case TypeMessage::DEAL_DAMAGE: {
  //
  // } break;
  // default:
  //   break;
  // }
}
