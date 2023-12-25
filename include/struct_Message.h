#ifndef MSG
#define MSG

#include "main.h"

enum class TypeObject;
enum class TypeEffect;
class GameObject;

enum class TypeMessage { MOVE, CREATE, DEATH, EFFECT };

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
  };
};
#endif
