#ifndef GAMEOBJ
#define GAMEOBJ

#include "class_ManagerResource.h"
#include "global_functions.h"
#include "main.h"
#include "struct_Message.h"

struct Message;

class GameObject {
protected:
  float health;
  float speed;
  sf::Vector2f coordinates;
  float radius_hitbox;

  void SetPosition(sf::Vector2f coordinates);
  virtual void Move(float dt) = 0;
  virtual void MoveSprite() = 0;
  virtual void CollisionWithWall();
  virtual bool CollisionWithObject(GameObject *object) = 0;

public:
  GameObject();
  GameObject(sf::Vector2f coordinates, float speed, float health);
  sf::Vector2f GetPosition() const;
  virtual ~GameObject();
  float GetRadiusHitbox() const;
  virtual void Draw(sf::RenderWindow *window) const = 0;
  virtual void Update(float dt) = 0;
  virtual void SendMessage(Message *message) = 0;
};
#endif
