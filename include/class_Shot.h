#ifndef SHT
#define SHT

#include "class_GameObject.h"

enum class TypeEffect { NONE, TORNADO, BLEEDING, EXPLOSION };

class Shot : public GameObject {
protected:
  float damage;
  float range_fire;
  sf::Vector2f direction;
  TypeEffect effect;
  TypeObject creator;

  void Move(float dt) override;
  void MoveSprite() override;
  virtual void CollisionWithWall() override;
  virtual bool CollisionWithObject(GameObject *object) override;

public:
  Shot(sf::Vector2f coordinates, sf::Vector2f direction, float speed,
       float range_fire, float damage, TypeEffect effect,
       TypeObject who_creator);
  virtual ~Shot();
  void Update(float dt) override;
  void SendMessage(Message *message) override;
  void Draw(sf::RenderWindow *window) const override;
};
#endif
