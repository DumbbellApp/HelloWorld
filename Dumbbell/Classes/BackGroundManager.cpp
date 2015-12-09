//
//  BackGroundManager.cpp
//  Dumbbell
//
//  Created by NakadaTakuya on 2015/12/10.
//
//

#include "BackGroundManager.hpp"
#include "BackGroundType.h"
#include "Message.hpp"
#include "EventManager.hpp"

namespace  {
    static const double changeBackInterval = 5;
}

bool BackGroundManager::init(void)
{
    if ( !Node::init() )
    {
        return false;
    }
    
    m_backGroundType = BackGroundType::Type1;
    m_time = 0;
    scheduleUpdate();
    return true;
}

void BackGroundManager::update(float delta)
{
    m_time += delta;
    
    if(m_time > changeBackInterval)
    {
        m_time = 0;
        
        std::random_device rnd;
        std::mt19937 mt(rnd());
        std::uniform_int_distribution<> rand(1, static_cast<int>(BackGroundType::Max) - 1);
        
        MSG_CHAGE_BACK msg(static_cast<BackGroundType>(rand(mt)));
        EventManager::getInstance()->dispatch(msg);
    }
}