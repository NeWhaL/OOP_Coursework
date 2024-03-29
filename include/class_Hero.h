#ifndef HERO
#define HERO

#include "class_GameObject.h"
#include "class_ManagerResource.h"
#include "class_ShotBase.h"
#include "class_ShotRicochet.h"
#include "class_ShotThrought.h"

class Hero : public GameObject 
{
private:
   float shot_cooldown_total;
   float shot_cooldown;
	TypeEffect current_effect_shot;	
	TypeShot current_type_shot;
	float range_fire_shot;
	float speed_shot;
	float cooldown_take_time;
	float time_after_damage_is_done;

   void Move(float dt);
   void CreateShot(float dt);
	void DeathObject(GameObject* killer);
   bool CollisionWithObject(const GameObject * const object);
   void ShotSelectionToCreate(sf::Vector2f mouse_pos);
   bool CollisionWithEffect(Effect* effect) const;

public:
   Hero(sf::Vector2f coordinates, float speed, float health,
        float shot_cooldown_total, float melee_cooldown_total, float damage);
   ~Hero() = default;

   void Update(float dt);
   void SendMessage(Message *message);
};
#endif