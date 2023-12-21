#ifndef GAMEOBJ
#define GAMEOBJ

#include "class_ManagerResource.h"
#include "global_functions.h"
#include "main.h"
#include "struct_Message.h"

struct Message;

enum class TypeObject { PLAYER, ENEMY, SHOT, ITEM };

class GameObject {
protected:
  TypeObject type;
  float health;
  float speed;
  sf::Vector2f coordinates;
  float radius_hitbox_head;
  int amount_sprite;
  sf::Sprite *main_sprite;

  void SetPosition(sf::Vector2f coordinates);
  virtual void Move(float dt) = 0;
  virtual void MoveSprite() = 0;
  virtual void CollisionWithWall();

public:
  GameObject(sf::Vector2f coordinates, float speed, float health,
             sf::Texture *main_texture, int amount_sprite);
  virtual ~GameObject();
  TypeObject GetTypeObject() const;
  sf::Vector2f GetPosition() const;
  float GetRadiusHitbox() const;
  sf::Vector2f GetPositionHead() const;
  float &GetHealth();
  virtual void Draw(sf::RenderWindow *window) const = 0;
  virtual void Update(float dt) = 0;
  virtual void SendMessage(Message *message) = 0;
  virtual bool CollisionWithObject(GameObject *object) = 0;
};
#endif
