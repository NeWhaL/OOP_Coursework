#ifndef MNG
#define MNG

#include "class_EnemyMelee.h"
#include "class_EnemyRange.h"
#include "class_GameObject.h"
#include "class_Hero.h"
#include "class_Item.h"
#include "class_EventManager.h"

struct Size_arena 
{
   sf::Vector2u up_left;
   sf::Vector2u down_right;
};

class Manager 
{
private:
	static Manager *manager;
   sf::RenderWindow *window;
   std::list<GameObject *> game_objects;
   std::list<Message *> messages;
   EventManager* event_manager;
   Hero *hero;
   sf::Sprite *sprite_room; 
   Size_arena size_arena;
	float cooldown_wave; 
	float time_until_the_next_wave;
	int amount_wave;

   Manager();
   ~Manager();
   Manager(const Manager &){};
   void DrawAllObject() const;
   void Update(float dt);
   void EventProcessing(sf::Event &ev);
	void CreateWaveEnemies(float dt);
   static void Destroy();

public:
   static Manager *GetInstance();
   sf::RenderWindow *GetWindow() const;
   Hero *GetHero() const;
   Size_arena GetSizeArena() const;
   void SendMessage(Message *msg);
   void Run();
   void End();
};

#endif