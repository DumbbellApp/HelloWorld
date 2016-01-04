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
    static const double changeBackInterval = 15;
}

bool BackGroundManager::init(void)
{
    if ( !Node::init() )
    {
        return false;
    }
    
    m_backGroundType = BackGroundType::Type1;
    m_time = 0;
    m_type = BackGroundType::Type1;
    scheduleUpdate();
    return true;
}

void BackGroundManager::update(float delta)
{
    m_time += delta;
    
    if(m_time > changeBackInterval)
    {
        int typeNum = static_cast<int>(m_type) + 1;
        if (typeNum >= static_cast<int>(BackGroundType::Max)) {
            typeNum = static_cast<int>(BackGroundType::Type1);
        }
        m_type = static_cast<BackGroundType>(typeNum);
        m_time = 0;
                
        MSG_CHAGE_BACK msg(static_cast<BackGroundType>(m_type));
        EventManager::getInstance()->dispatch(msg);
    }
}