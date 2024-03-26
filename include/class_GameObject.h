#ifndef GAMEOBJ
#define GAMEOBJ

#include "class_ManagerResource.h"
#include "class_EventManager.h"
#include "global_functions.h"
#include "main.h"
#include "struct_Message.h"

class FontForCharacteristics;
class Manager;

class GameObject 
{
  friend FontForCharacteristics;
protected:
  static Manager* manager;
  static ResourceManager* res_manager;
  TypeObject type_object;
  TypeObject creator;
  int amount_money;
  float health;
  float speed;
  float damage;
  sf::Vector2f coordinates;
  sf::Vector2f direction;
  bool is_object_alive;
  
  float radius_hitbox_head;
  int amount_sprite_head;
  sf::Sprite *head_sprite;
  float radius_hitbox_legs;
  int amount_sprite_legs_up_down = 10;
  sf::Sprite *legs_up_down;
  sf::Sprite *legs_left;
  sf::Sprite *legs_right;
  float scale_sprite;
  FontForCharacteristics* font_characteristics;

  void SetPosition(sf::Vector2f coordinates);
  virtual void CollisionWithWall();
  virtual bool CollisionWithObject(const GameObject * const object);
  virtual void Move(float dt) = 0;
  void MoveSprite();
  virtual void DeathObject(GameObject* killer);
  void SetSpriteFromTexture(const sf::Texture* texture, sf::Sprite*& sprite, int amount_sprite);
  // virtual bool CollisionWithEffect(Effect* effect) const;

public:
  GameObject(sf::Vector2f coordinates, float speed, float health, float damage,
             int amount_head_sprite, int amount_sprite_legs, float scale_sprite,
             sf::Texture* head_texture,
             sf::Texture* legs_up_down_texture,
             sf::Texture* legs_left_texture,
             sf::Texture* legs_right_texture);
  virtual ~GameObject();
  int& GetMoney();
  sf::Vector2f GetDirection() const;
  TypeObject GetTypeObject() const;
  TypeObject GetCreatorObject() const;
  sf::Vector2f GetPosition() const;
  sf::Vector2f GetPositionHead() const;
  float GetRadiusHitbox() const;
  float GetDamage() const;
  void Draw(sf::RenderWindow *window) const;
  virtual void Update(float dt) = 0;
  virtual void SendMessage(Message *message) = 0;
};
#endif
