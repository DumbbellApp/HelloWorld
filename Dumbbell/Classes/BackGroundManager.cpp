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
    
    //Stateが変わった時の処理
    EventManager::getInstance()->addEventLister<MSG_CHAGE_STATE>([this](EventCustom* event){
        auto msg = static_cast<MSG_CHAGE_STATE*>(event->getUserData());
        if (msg->getStete() == STATE::GAME)
        {
            m_type = BackGroundType::Type1;
            m_time = 0;
            MSG_RESET_BACK msg;
            EventManager::getInstance()->dispatch(msg);
        }
    });

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