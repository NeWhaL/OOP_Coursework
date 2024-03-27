#ifndef MNG
#define MNG

#include "class_GameObject.h"
#include "class_Hero.h"
#include "class_Item.h"
#include "class_EventManager.h"
#include "class_Wave.h"



class Manager 
{
private:
	static Manager *manager;
   EventManager* event_manager;
   Wave* wave;
   sf::RenderWindow *window;
   std::list<GameObject *> game_objects;
   std::list<Message *> messages;
   Hero *hero;
   sf::Sprite *sprite_room; 

   Manager();
   ~Manager();
   Manager(const Manager &){};
   void DrawAllObject() const;
   void Update(float dt);
   void EventProcessing(sf::Event &ev);
   static void Destroy();

public:
   static Manager *GetInstance();
   sf::RenderWindow *GetWindow() const;
   Hero *GetHero() const;
   void SendMessage(Message *msg);
   void Run();
   void End();
};

#endif