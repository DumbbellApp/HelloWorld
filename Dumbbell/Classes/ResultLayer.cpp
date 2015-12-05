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
    
    m_resultSprite = Sprite::create("result_back.png");
    m_resultSprite->setScale(3);
    m_resultSprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    addChild(m_resultSprite);
    
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