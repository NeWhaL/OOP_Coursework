#ifndef MSG
#define MSG

#include "main.h"

enum class TypeShot;
enum class TypeObject;
enum class TypeEffect;
class Manager;
class GameObject;
class Shot;
class Effect;

enum class TypeMessage { MOVE, CREATE, DEATH, EFFECT, ITEM };

struct Message {
  GameObject *who_sent;
  TypeMessage type_message;
  Message() : who_sent{nullptr} {};
  
	union 
  {
     struct 
	  {
        GameObject *new_object;
        GameObject *creator;
     } create;
     struct 
	  {
        GameObject *who_die;
        GameObject *killer;
		  int money;
     } death;
	  struct 
	  {
		  TypeEffect type;
		  TypeObject creator;
		  float damage;
	  } effect;
	  struct
	  {
		  TypeEffect type_effect;
		  TypeShot type_shot;
		  float damage;
		  float speed;
		  float health;
		  float range_fire;
	  } item;
  };

	static void MessageMove(GameObject* who_sent, Manager* manager);
	static void MessageCreateShot(Shot* shot, GameObject* creator, Manager* manager);
	static void MessageCreateEffect(Effect* effect, GameObject* who_sent, GameObject* creator, Manager* manager);
	static void ActionEffect(GameObject* who_sent, TypeObject creator, TypeEffect type_effect, float damage, Manager* manager);
	static void Death(GameObject* who_die, GameObject* killer, int amount_money, Manager* manager);
  static void BuyItem(GameObject* who_sent, TypeShot type_shot, TypeEffect type_effect, 
							float health, float damage, float speed, float range_fire, Manager* manager);
};
#endif
