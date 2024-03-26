#ifndef EVENTMANAGER
#define EVENTMANAGER
#include "main.h"
#include "class_EffectExplosion.h"

class GameObject;

class EventManager
{
  static EventManager* ev_man;
  std::list<Effect*> effects;

  EventManager() = default;
  ~EventManager();
  void CreateEffect(Message* message);
	void DestroyEffect(Effect* effect);

public:
  static EventManager* GetInstance();
  void Update(float dt);
  void Draw(sf::RenderWindow* window);
  void SendMessage(Message* message);
};

#endif