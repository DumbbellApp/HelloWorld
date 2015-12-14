//
//  TitleLayer.cpp
//  Dumbbell
//
//  Created by NakadaTakuya on 2015/12/05.
//
//

#include "TitleLayer.hpp"
#include "Message.hpp"
#include "GameStateType.h"
#include "EventManager.hpp"
using namespace std;
bool TitleLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    m_titleSprite = Sprite::create("title.png");
    m_titleSprite->setScale(1.25);
    m_titleSprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height - 190));
    addChild(m_titleSprite);

    //タップイベントを作成
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(TitleLayer::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void TitleLayer::onEnter()
{
    Layer::onEnter();
    
    EventManager::getInstance()->addEventLister<MSG_CHAGE_STATE>([this](EventCustom* event){
        auto msg = static_cast<MSG_CHAGE_STATE*>(event->getUserData());
        if (msg->getStete() == STATE::GAME) {
            setVisible(false);
        }
    });
}
bool TitleLayer::onTouchBegan(Touch *touch, Event *event)
{
    if(!isVisible())
        return false;
    
    auto fade = FadeOut::create(1);
    auto callback = CallFunc::create([this](){
        MSG_CHAGE_STATE msg(STATE::GAME);
        EventManager::getInstance()->dispatch(msg);
    });
    m_titleSprite->runAction(Sequence::create(fade, callback, NULL));
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->removeEventListenersForTarget(this);
    return true;
}