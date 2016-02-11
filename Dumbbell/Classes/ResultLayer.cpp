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
#include "DumbbellMenuItemImage.hpp"
#include "iomanip"
#include "ScoreManager.hpp"

using namespace std;
bool ResultLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    m_resultBack = Sprite::create("result_back.png");
    m_resultBack->setAnchorPoint(Vec2(0.5, 0.5));
    m_resultBack->setPosition(Vec2(320, 605));
    addChild(m_resultBack);
    
    std::ostringstream oss;
    oss << setw(5) << setfill('0') << ScoreManager::getInstance()->getScore();
    
    m_resultScoreLabel = Label::createWithBMFont("siro.fnt", oss.str());
    m_resultScoreLabel->setPosition(Vec2(m_resultBack->getContentSize().width/2 + 80, 235));
    m_resultBack->addChild(m_resultScoreLabel);
    
    std::ostringstream oss2;
    oss2 << setw(5) << setfill('0') << 0;
    
    m_bestScoreLabel = Label::createWithBMFont("siro.fnt", oss2.str());
    m_bestScoreLabel->setPosition(Vec2(m_resultBack->getContentSize().width/2 + 80, 150));
    m_resultBack->addChild(m_bestScoreLabel);
    
    m_retryBtn = DumbellMenuItemImage::create("retry_button.png", "retry_button.png", [this](Ref*sender){
        MSG_CHAGE_STATE msg(STATE::GAME);
        EventManager::getInstance()->dispatch(msg);
        m_retryBtn->setScale(1);
    });
    
    m_menu = Menu::create(m_retryBtn, NULL);
    m_menu->setAnchorPoint(Vec2(0.5,0.5));
    m_menu->setPosition(Vec2(269, 40));
    m_menu->setEnabled(false);
    m_resultBack->addChild(m_menu);
    
    m_resultBack->setCascadeOpacityEnabled(true);
    m_resultBack->setVisible(false);

    return true;
}

void ResultLayer::onEnter()
{
    Layer::onEnter();
    
    EventManager::getInstance()->addEventLister<MSG_CHAGE_STATE>([this](EventCustom* event){
        auto msg = static_cast<MSG_CHAGE_STATE*>(event->getUserData());
        if (msg->getStete() == STATE::RESULT) {
            
            int result = ScoreManager::getInstance()->getScore();
            int best = UserDefault::getInstance()->getIntegerForKey("best");
            
            if(result > best)
            {
                UserDefault::getInstance()->setIntegerForKey("best", result);
                best = result;
            }
            std::ostringstream oss;
            oss << setw(5) << setfill('0') << result;
            m_resultScoreLabel->setString(oss.str());
            
            std::ostringstream oss2;
            oss2 << setw(5) << setfill('0') << best;
            m_bestScoreLabel->setString(oss2.str());
            
            m_resultBack->setVisible(true);
            auto fade = FadeIn::create(2);
            auto callback = CallFunc::create([this](){m_menu->setEnabled(true);});
            m_resultBack->runAction(Sequence::create(fade, callback, NULL) );
        }
        else
        {
            m_menu->setEnabled(false);
            m_resultBack->setOpacity(0);
        }
    });
}