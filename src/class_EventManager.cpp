#include "../include/class_EventManager.h"
#include "../include/class_GameObject.h"

EventManager::~EventManager()
{
  for(auto& i : effects)
    delete i;
  effects.clear();
}

void EventManager::Update(float dt)
{
  for(const auto& i : effects)
    i->Action(dt);
}

void EventManager::Draw(sf::RenderWindow* window)
{
  for(const auto& i : effects)
    i->Draw(window);
}

void EventManager::SendMessage(Message* message)
{
  switch (message->type_message)
  {
    case TypeMessage::CREATE_EFFECT:
    {
      CreateEffect(message);
    } break;
    case TypeMessage::END_EFFECT:
    {
      DestroyEffect(message->end_effect.effect);
    } break;
    default: break;
  }
}

void EventManager::CreateEffect(Message* message)
{
  GameObject* object = message->who_sent;
  Effect* effect;
  switch (message->create_effect.type_effect)
  {
    case TypeEffect::EXPLOSION:
    {
      effect = new EffectExplosion(message->who_sent->GetPositionHead(),
                   message->create_effect.creator, nullptr);
    } break;
    default: break;
  } 
  effects.push_back(effect);
}

void EventManager::DestroyEffect(Effect* effect)
{
  for (auto i = effects.begin(); i != effects.end(); ++i)
    if (*i == effect)
    {
      delete *i;
      effects.erase(i);
      break;
    }
}