#ifndef SHT
#define SHT

#include "class_GameObject.h"

class Shot : public GameObject 
{
protected:
   float range_fire;
   TypeEffect effect;

   void Move(float dt);
   virtual void CollisionWithWall();
   virtual bool CollisionWithObject(const GameObject * const object);
public:
   Shot(sf::Vector2f coordinates, sf::Vector2f direction, float speed,
        float range_fire, float damage, TypeEffect effect,
        TypeObject who_creator);
   virtual ~Shot() = default;
   virtual void Update(float dt);
	void DeathObject(GameObject* killer);
};
#endif
