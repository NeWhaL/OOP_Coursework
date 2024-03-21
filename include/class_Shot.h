#ifndef SHT
#define SHT

#include "class_GameObject.h"
#include "class_Effect.h"
#include "class_EffectBomb.h"

enum class TypeShot { NONE, BASE, RICOCHET, THROUGHT };

class Shot : public GameObject 
{
protected:
   float range_fire;
   TypeEffect effect;

   void Move(float dt);
   virtual void CollisionWithWall();

public:
   Shot(sf::Vector2f coordinates, sf::Vector2f direction, float speed,
        float range_fire, float damage, TypeEffect effect,
        TypeObject who_creator);
   virtual ~Shot() = default;
   void Update(float dt);
	void DeathObject(GameObject* killer);
};
#endif
