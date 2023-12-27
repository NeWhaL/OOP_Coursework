#ifndef GAMEOBJ
#define GAMEOBJ

#include "class_ManagerResource.h"
#include "global_functions.h"
#include "main.h"
#include "struct_Message.h"

class Manager;

enum class TypeObject { NONE, PLAYER, ENEMY, SHOT, ITEM, EFFECT };

class GameObject {
protected:
  Manager* manager;
  TypeObject type_object;
  TypeObject creator;
  float health;
  float speed;
  float damage;
  sf::Vector2f coordinates;
  float radius_hitbox_head;
  int amount_sprite;
  sf::Sprite *main_sprite;
  bool is_object_alive;

  void SetPosition(sf::Vector2f coordinates);
  virtual void CollisionWithWall();
  virtual bool CollisionWithObject(GameObject *object);
  virtual void Move(float dt) = 0;
  virtual void MoveSprite();
  virtual void DeathObject(GameObject* killer);

public:
  GameObject(sf::Vector2f coordinates, float speed, float health,
             sf::Texture *main_texture, int amount_sprite, float damage);
  virtual ~GameObject();
  TypeObject GetTypeObject() const;
  TypeObject GetCreatorObject() const;
  sf::Vector2f GetPosition() const;
  sf::Vector2f GetPositionHead() const;
  float GetRadiusHitbox() const;
  float GetDamage() const;
  virtual void Draw(sf::RenderWindow *window) const;
  virtual void Update(float dt) = 0;
  virtual void SendMessage(Message *message) = 0;
};
#endif
