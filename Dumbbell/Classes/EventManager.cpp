//
//  EventManager.cpp
//  Dumbbell
//
//  Created by NakadaTakuya on 2015/12/05.
//
//

#include "EventManager.hpp"

static EventManager *s_SharedEventManager = nullptr;

EventManager* EventManager::getInstance()
{
    if (!s_SharedEventManager)
    {
        s_SharedEventManager = new (std::nothrow) EventManager();
        CCASSERT(s_SharedEventManager, "FATAL: Not enough memory");
        s_SharedEventManager->init();
    }
    
    return s_SharedEventManager;
}

EventManager::EventManager()
{
}

bool EventManager::init(void)
{
    return true;
}

EventManager::~EventManager(void)
{
    s_SharedEventManager = nullptr;
}