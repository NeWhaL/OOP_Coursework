#include "../include/class_Manager.h"

Manager *Manager::manager = nullptr;

Manager::Manager()
    : game_objects(), messages(),
      sprite_room(new sf::Sprite(*ResourceManager::GetInstance()->getTRoom())),
      window(new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "GAME",
                                  sf::Style::Fullscreen)) {
  // размеры поля сражения
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

void Manager::Run() {
  hero = new Hero({600, 400}, 300, 10, 0.1, 1, 2);
  game_objects.push_back(new EnemyMelee({1000, 600}, 200, 10, 1));
  sf::Clock time;
  while (window->isOpen()) {
    sf::Event ev;
    float dt = time.getElapsedTime().asSeconds();
    time.restart();
    EventProcessing(ev);
    Update(dt);
    DrawAllObject();
  }
}

void Manager::End() { delete window; }

void Manager::DrawAllObject() const {
  window->clear();
  window->draw(*sprite_room);
  for (const auto &i : game_objects)
    i->Draw(window);
  hero->Draw(window);
  window->display();
}

void Manager::Update(float dt) {
  hero->Update(dt);
  for (auto &object : game_objects)
    object->Update(dt);

  Message *message;
  while (not messages.empty()) {
    message = messages.front();
    messages.pop_front();
    switch (message->type_message) {
    case TypeMessage::CREATE: {
      game_objects.push_back(message->create.new_object);
    } break;
    case TypeMessage::DEATH: {
      auto kill = std::find(game_objects.begin(), game_objects.end(),
                            message->death.who_die);
      delete *kill;
      game_objects.erase(kill);
    } break;
    }
    if (message->type_message == TypeMessage::MOVE or
        message->type_message == TypeMessage::DEAL_DAMAGE) {
      hero->SendMessage(message);
      for (auto i : game_objects) {
        i->SendMessage(message);
      }
    }
    delete message;
  }
}

void Manager::SendMessage(Message *msg) { messages.push_back(msg); }
