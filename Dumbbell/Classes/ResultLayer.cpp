//
//  ResultLayer.cpp
//  Dumbbell
//
//  Created by NakadaTakuya on 2015/12/06.
//
//

#include "ResultLayer.hpp"

#include "Message.hpp"
#include "GameStateType.h"
#include "EventManager.hpp"
using namespace std;
bool ResultLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    m_resultBack = Sprite::create("result_back.png");
    m_resultBack->setScale(2.5);
    m_resultBack->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    addChild(m_resultBack);
    
    m_resultTitle = Sprite::create("nice_play.png");
    m_resultTitle->setScale(0.5);
    m_resultTitle->setAnchorPoint(Vec2(0.5,0.5));
    m_resultTitle->setPosition(Vec2(m_resultBack->getContentSize().width/2, m_resultBack->getContentSize().height/2 + 40));
    m_resultBack->addChild(m_resultTitle);
    
    m_resultScore = Sprite::create("score.png");
    m_resultScore->setScale(0.45);
    m_resultScore->setAnchorPoint(Vec2(0,0.5));
    m_resultScore->setPosition(Vec2(m_resultBack->getContentSize().width/2 - 70, m_resultBack->getContentSize().height/2 + 10));
    m_resultBack->addChild(m_resultScore);

    m_resultBest = Sprite::create("best.png");
    m_resultBest->setScale(0.45);
    m_resultBest->setAnchorPoint(Vec2(0,0.5));
    m_resultBest->setPosition(Vec2(m_resultBack->getContentSize().width/2 - 70, m_resultBack->getContentSize().height/2 - 20));
    m_resultBack->addChild(m_resultBest);
    
    
    auto button = MenuItemImage::create("retry_button.png", "retry_button.png", [](Ref*sender){
        MSG_CHAGE_STATE msg(STATE::GAME);
        EventManager::getInstance()->dispatch(msg);
    });
    button->setScale(0.4);
    auto menu = Menu::create(button, NULL);
    menu->setAnchorPoint(Vec2(0.5,0.5));
    menu->setPosition(Vec2(m_resultBack->getContentSize().width/2, 60));
    m_resultBack->addChild(menu);
    
//    setVisible(false);
    return true;
}

void ResultLayer::onEnter()
{
    Layer::onEnter();
    
    EventManager::getInstance()->addEventLister<MSG_CHAGE_STATE>([this](EventCustom* event){
        auto msg = static_cast<MSG_CHAGE_STATE*>(event->getUserData());
        if (msg->getStete() == STATE::RESULT) {
            setVisible(true);
            //結果の表示のコードをここに書く予定
        }
        else
        {
            setVisible(false);
        }
    });
}