#ifndef MSG
#define MSG

#include "main.h"

class GameObject;

enum class TypeMessage { MOVE, CREATE, DEATH, DEAL_DAMAGE };

struct Message {
  GameObject *who_sent;
  TypeMessage type_message;

  Message() : who_sent(nullptr){};

  union {
    struct {
      // GameObject *who_goes;
    } move;
    struct {
      GameObject *new_object;
      GameObject *creator;
    } create;
    struct {
      GameObject *who_die;
      GameObject *killer;
    } death;
    struct {
      float damage;
      GameObject *to_who;
    } deal_damage;
  };
};
#endif
