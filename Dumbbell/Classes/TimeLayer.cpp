//
//  TimeLayer.cpp
//  Dumbbell
//
//  Created by NakadaTakuya on 2015/12/04.
//
//

#include "TimeLayer.hpp"
#include "EventManager.hpp"
#include "Message.hpp"
using namespace std;
bool TimeLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    m_time = 0;
    
    m_timeSprite = Sprite::create("time.png");
    m_timeSprite->setAnchorPoint(Vec2(0,0.5));
    m_timeSprite->setPosition(Vec2(0, visibleSize.height - 64));
    addChild(m_timeSprite);
    
    m_timeLabel = Label::createWithBMFont("jun.fnt", to_string(m_time));

    m_timeLabel->setPosition(Point(150, visibleSize.height - 64));
    addChild(m_timeLabel);
    
    setVisible(false);
    
    return true;
}

void TimeLayer::onEnter()
{
    Layer::onEnter();
    
    EventManager::getInstance()->addEventLister<MSG_CHAGE_STATE>([this](EventCustom* event){
        auto msg = static_cast<MSG_CHAGE_STATE*>(event->getUserData());
        if (msg->getStete() == STATE::GAME) {
            setTime(60);
            setVisible(true);
        }
    });
    
    EventManager::getInstance()->addEventLister<MSG_CHAGE_TIME>([this](EventCustom* event){
        auto msg = static_cast<MSG_CHAGE_TIME*>(event->getUserData());
        setTime(msg->getTime());
    });
}

void TimeLayer::setTime(float time)
{
    m_time = time;
    m_timeLabel->setString(to_string(m_time));
}