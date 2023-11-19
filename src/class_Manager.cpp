#include "../include/class_Manager.h"

Manager *Manager::manager = nullptr;

Manager::Manager() : window(nullptr) { hero = new Hero; }

Manager::~Manager() {}

Manager *Manager::getInstance() {
  if (manager == nullptr)
    manager = new Manager;
  return manager;
}

void Manager::Init() {
  window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "GAME",
                                sf::Style::Fullscreen);
  // window = new sf::RenderWindow(sf::VideoMode(640, 480), "GAME");
}

void Manager::Run() {
  while (window->isOpen()) {
    sf::Event ev;
    while (window->pollEvent(ev)) {
      if (ev.type == sf::Event::Closed) {
        window->close();
      }
    }

    // window->clear(sf::Color(122, 0, 0));
    Update();
    DrawAllObject();
  }
}

void Manager::End() { delete window; }

void Manager::DrawAllObject() const {
  window->clear();
  hero->Draw(window);
  window->display();
}

void Manager::Update() {
  float dt = time.getElapsedTime().asSeconds();
  time.restart();

  hero->Update(dt);
  // for (auto i : )
}
