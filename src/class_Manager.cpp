#include "../include/class_Manager.h"

Manager *Manager::manager = nullptr;

Manager::Manager(): game_objects(), messages(), sprite_room(new sf::Sprite(*ResourceManager::GetInstance()->getTRoom())),
						  window(new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "GAME", sf::Style::Fullscreen)), cooldown_wave(5),
						  time_until_the_next_wave(0), amount_wave(0)
{
	// размеры поля
	size_arena.up_left.x = 320;
	size_arena.up_left.y = 180;
	size_arena.down_right.x = 1720;
	size_arena.down_right.y = 900;
}

Manager::~Manager() {
  for (auto &i : game_objects) {
    delete i;
  }
  game_objects.clear();
  for (auto &i : messages) {
    delete i;
  }
  messages.clear();
  delete window;
}

void Manager::Destroy() {
  if (manager)
    delete manager;
}

Manager *Manager::GetInstance() {
  return manager ? manager : manager = new Manager;
}

sf::RenderWindow *Manager::GetWindow() const { return window; }

void Manager::EventProcessing(sf::Event &ev) {
  while (window->pollEvent(ev)) {
    if (ev.type == sf::Event::Closed)
      window->close();
    else if (ev.type == sf::Event::KeyPressed and
             ev.key.code == sf::Keyboard::Escape)
      window->close();
  }
}

Hero *Manager::GetHero() const { return hero; }

Size_arena Manager::GetSizeArena() const { return size_arena; }

void Manager::Run() 
{
   hero = new Hero({600, 400}, 300, 10, 0.1, 1, 2);
   game_objects.push_back(new Item({1200, 300}, ResourceManager::GetInstance()->getTEffectBomb(), TypeItem::EFFECT,
 								  TypeShot::NONE, TypeEffect::EXPLOSION, 0, 0, 0, 0, 0));
   sf::Clock time;
   while (window->isOpen()) 
	{
      sf::Event ev;
      float dt = time.getElapsedTime().asSeconds();
      time.restart();
      EventProcessing(ev);
      Update(dt);
      DrawAllObject();
   }
}

void Manager::End() { Destroy(); }

void Manager::DrawAllObject() const 
{
   window->clear();
   window->draw(*sprite_room);
   hero->Draw(window);
   for (const auto &i : game_objects)
     i->Draw(window);
   window->display();
}

void Manager::Update(float dt) 
{
   hero->Update(dt);
   for (auto &object : game_objects)
      object->Update(dt);
	CreateWaveEnemies(dt);

   Message *message;
   while (not messages.empty()) 
	{
      message = messages.front();
      messages.pop_front();
      switch (message->type_message)
	   {
		   case TypeMessage::CREATE:
				game_objects.push_back(message->create.new_object);
				break;
			case TypeMessage::DEATH:
			{
				hero->GetMoney() += message->death.money;	
				auto kill = std::find(game_objects.begin(), game_objects.end(), message->death.who_die);
				delete *kill;
				game_objects.erase(kill);
			} break;
			default:
			{
				hero->SendMessage(message);
				for (auto i : game_objects)
					i->SendMessage(message); 
			} break;
		}
		delete message;
   } 
}

void Manager::SendMessage(Message *msg) { messages.push_back(msg); }

void Manager::CreateWaveEnemies(float dt)
{
	time_until_the_next_wave += dt;
	if (cooldown_wave > time_until_the_next_wave)
		return;
	int amount_enemy = 3;
	for (int i = 0; i < amount_enemy + amount_wave; i++)
	{
		game_objects.push_back(new EnemyMelee({static_cast<float>(std::rand() % 1500 + 400), 
									  static_cast<float>(std::rand() % 500 + 400)}, 150, 10, 3));
	}
	time_until_the_next_wave = 0;
	amount_wave++;
}
