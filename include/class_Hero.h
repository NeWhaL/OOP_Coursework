#ifndef HERO
#define HERO

#include "class_GameObject.h"
#include "class_ManagerResource.h"
#include "class_ShotBase.h"

class Hero : public GameObject 
{
private:
   float shot_cooldown_total;
   float shot_cooldown;
   int amount_sprite_legs_up_down = 10;
   float radius_hitbox_legs;
	TypeEffect current_effect_shot;	
	float range_fire_shot;
	float speed_shot;
	float cooldown_take_time;
	float time_after_damage_is_done;

   sf::Sprite *legs_up_down;
   sf::Sprite *legs_left;
   sf::Sprite *legs_right;

   void Move(float dt) override;
   void MoveSprite() override;
   void CreateShot(float dt);
	void DeathObject(GameObject* killer) override;

public:
   Hero(sf::Vector2f coordinates, float speed, float health,
        float shot_cooldown_total, float melee_cooldown_total, float damage);
   ~Hero();

   void Draw(sf::RenderWindow *window) const override;
   void Update(float dt) override;
   void SendMessage(Message *message) override;
   bool CollisionWithObject(GameObject *object) override;
};
#endif
