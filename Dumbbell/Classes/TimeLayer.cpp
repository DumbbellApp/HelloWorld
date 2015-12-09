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
#include "BackGroundType.h"

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
    
    m_timeLabelKuro = Label::createWithBMFont("kuro.fnt", to_string(m_time));
    m_timeLabelKuro->setPosition(Point(160, visibleSize.height - 55));
    
    m_timeLabelSiro = Label::createWithBMFont("siro.fnt", to_string(m_time));
    m_timeLabelSiro->setPosition(Point(160, visibleSize.height - 55));
    
    addChild(m_timeLabelKuro,2);
    addChild(m_timeLabelSiro,1);
    
    setOpacity(0);
    setCascadeOpacityEnabled(true);
    return true;
}

void TimeLayer::onEnter()
{
    Layer::onEnter();
    
    EventManager::getInstance()->addEventLister<MSG_CHAGE_STATE>([this](EventCustom* event){
        auto msg = static_cast<MSG_CHAGE_STATE*>(event->getUserData());
        if (msg->getStete() == STATE::GAME) {
            setTime(60);
            auto fade = FadeIn::create(1);
            this->runAction(fade);
        }
        else if(msg->getStete() == STATE::RESULT)
        {
            auto fade = FadeOut::create(2);
            runAction(fade);
        }
    });
    
    EventManager::getInstance()->addEventLister<MSG_CHAGE_TIME>([this](EventCustom* event){
        auto msg = static_cast<MSG_CHAGE_TIME*>(event->getUserData());
        setTime(msg->getTime());
    });
    
    EventManager::getInstance()->addEventLister<MSG_CHAGE_BACK>([this](EventCustom* event){
        auto msg = static_cast<MSG_CHAGE_BACK*>(event->getUserData());
        auto type = msg->getBGType();
        if (type == BackGroundType::Type2 || type == BackGroundType::Type3) {
            if(m_backGroundType != BackGroundType::Type2 || m_backGroundType != BackGroundType::Type3)
            {
                m_timeLabelSiro->setVisible(true);
                //白に変える
                auto fade =  FadeOut::create(3);
                auto callback = CallFunc::create([this](){
                    m_timeLabelSiro->setZOrder(2);
                    m_timeLabelKuro->setZOrder(1);
                    m_timeLabelKuro->setOpacity(255);
                    m_timeLabelKuro->setVisible(false);
                });
                m_timeLabelKuro->runAction(Sequence::create(fade,callback, NULL));
            }
        }
        else
        {
            if(m_backGroundType == BackGroundType::Type2 || m_backGroundType == BackGroundType::Type3)
            {
                m_timeLabelKuro->setVisible(true);
                //黒に変える
                auto fade =  FadeOut::create(3);
                auto callback = CallFunc::create([this](){
                    m_timeLabelKuro->setZOrder(2);
                    m_timeLabelSiro->setZOrder(1);
                    m_timeLabelSiro->setOpacity(255);
                    m_timeLabelSiro->setVisible(false);
                });
                m_timeLabelSiro->runAction(Sequence::create(fade,callback, NULL));
            }
        }
        m_backGroundType = type;
    });
}

void TimeLayer::setTime(float time)
{
    m_time = time;
    m_timeLabelSiro->setString(to_string(m_time));
    m_timeLabelKuro->setString(to_string(m_time));
}