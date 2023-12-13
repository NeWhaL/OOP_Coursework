#include "../include/class_Hero.h"
#include "../include/class_Manager.h"

Hero::Hero()
    : GameObject({100, 100}, 200), shot_cooldown(0), shot_cooldown_total(0.2),
      melee_cooldown(0) {
  ResourceManager *RM = ResourceManager::GetInstance();
  head = new sf::Sprite;
  legs_up_down = new sf::Sprite;
  legs_left = new sf::Sprite;
  legs_right = new sf::Sprite;

  head->setTexture(*RM->getTHeroHead());
  legs_up_down->setTexture(*RM->getTHeroHead());
  legs_left->setTexture(*RM->getTHeroHead());
  legs_right->setTexture(*RM->getTHeroHead());

  head->setTextureRect(sf::IntRect(0, 0, 50, 50));
  sf::FloatRect bounds_head = head->getLocalBounds();
  head->setOrigin(bounds_head.width / 2, bounds_head.height / 2);
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
    message->move.old_position = coordinates;
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

void Hero::MoveSprite() { head->setPosition(coordinates.x, coordinates.y); }

void Hero::CreateShot(float dt) {
  shot_cooldown += dt;
  if (shot_cooldown < shot_cooldown_total)
    return;

  if (sf::Mouse::isButtonPressed(sf::Mouse::Left) or
      sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
    shot_cooldown = 0;
    sf::Vector2i current_mouse_position =
        sf::Mouse::getPosition(*Manager::GetInstance()->GetWindow());

    current_mouse_position = MouseCoordinatesRelativeOtherCoordinates(
        current_mouse_position, coordinates);

    sf::Vector2f normalized_mouse_position =
        NormalizationVector(current_mouse_position);

    Message *message = new Message;
    message->type_message = TypeMessage::CREATE;
    message->create.new_object = new ShotBase(
        coordinates, normalized_mouse_position, 200, 400, 10, TypeEffect::NONE);
    message->create.creator = this;
    Manager::GetInstance()->SendMessage(message);
  }
}

void Hero::Draw(sf::RenderWindow *window) const { window->draw(*head); }

void Hero::SendMessage(Message *message) {
  // сюда отдается сообщение извне на обработку этим обьектом
}
