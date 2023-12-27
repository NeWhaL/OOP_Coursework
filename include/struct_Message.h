#ifndef MSG
#define MSG

#include "main.h"

enum class TypeShot;
enum class TypeObject;
enum class TypeEffect;
class GameObject;

enum class TypeMessage { MOVE, CREATE, DEATH, EFFECT, ITEM };

struct Message {
  GameObject *who_sent;
  TypeMessage type_message;

  Message() : who_sent(nullptr){};

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
};
#endif
