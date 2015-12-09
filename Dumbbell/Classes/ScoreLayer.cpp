//
//  ScoreLayer.cpp
//  Dumbbell
//
//  Created by NakadaTakuya on 2015/12/04.
//
//

#include "ScoreLayer.hpp"
#include "iomanip"
#include "EventManager.hpp"
#include "Message.hpp"
#include "BackGroundType.h"

using namespace std;
bool ScoreLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    m_score = 0;
    
    m_scoreSprite = Sprite::create("score.png");
    m_scoreSprite->setPosition(Vec2(visibleSize.width - 300, visibleSize.height - 64));
    addChild(m_scoreSprite);
    
    std::ostringstream oss;
    oss << setw(5) << setfill('0') << m_score;
    
    m_scoreLabelKuro = Label::createWithBMFont("kuro.fnt", oss.str());
    m_scoreLabelKuro->setPosition(Point(visibleSize.width - 100, visibleSize.height - 55));
    addChild(m_scoreLabelKuro, 2);

    m_scoreLabelSiro = Label::createWithBMFont("siro.fnt", oss.str());
    m_scoreLabelSiro->setPosition(Point(visibleSize.width - 100, visibleSize.height - 55));
    addChild(m_scoreLabelSiro, 1);
    m_scoreLabelSiro->setVisible(false);
    
    setOpacity(0);
    setCascadeOpacityEnabled(true);
    
    m_backGroundType = BackGroundType::Type1;
    return true;
}

void ScoreLayer::onEnter()
{
    Layer::onEnter();
    
    //Stateにより，UIの表示，非表示を切り替える
    EventManager::getInstance()->addEventLister<MSG_CHAGE_STATE>([this](EventCustom* event){
        auto msg = static_cast<MSG_CHAGE_STATE*>(event->getUserData());
        if (msg->getStete() == STATE::GAME) {
            setScore(0);
            auto fade = FadeIn::create(1);
            this->runAction(fade);
        }
        else if(msg->getStete() == STATE::RESULT)
        {
            auto fade = FadeOut::create(2);
            this->runAction(fade);
        }
    });
    
    //スコアが変更した時に呼び出されるMsg
    EventManager::getInstance()->addEventLister<MSG_CHAGE_SCORE>([this](EventCustom* event){
        auto msg = static_cast<MSG_CHAGE_SCORE*>(event->getUserData());
        setScore(msg->getScore());
    });
    
    EventManager::getInstance()->addEventLister<MSG_CHAGE_BACK>([this](EventCustom* event){
        auto msg = static_cast<MSG_CHAGE_BACK*>(event->getUserData());
        auto type = msg->getBGType();
        if (type == BackGroundType::Type2 || type == BackGroundType::Type3) {
            if(m_backGroundType != BackGroundType::Type2 || m_backGroundType != BackGroundType::Type3)
            {
                m_scoreLabelSiro->setVisible(true);
                //白に変える
                auto fade =  FadeOut::create(3);
                auto callback = CallFunc::create([this](){
                    m_scoreLabelSiro->setZOrder(2);
                    m_scoreLabelKuro->setZOrder(1);
                    m_scoreLabelKuro->setOpacity(255);
                    m_scoreLabelKuro->setVisible(false);
                });
                m_scoreLabelKuro->runAction(Sequence::create(fade,callback, NULL));
            }
        }
        else
        {
            if(m_backGroundType == BackGroundType::Type2 || m_backGroundType == BackGroundType::Type3)
            {
                m_scoreLabelKuro->setVisible(true);
                //黒に変える
                auto fade =  FadeOut::create(3);
                auto callback = CallFunc::create([this](){
                    m_scoreLabelKuro->setZOrder(2);
                    m_scoreLabelSiro->setZOrder(1);
                    m_scoreLabelSiro->setOpacity(255);
                    m_scoreLabelSiro->setVisible(false);
                });
                m_scoreLabelSiro->runAction(Sequence::create(fade,callback, NULL));
            }
        }
        m_backGroundType = type;
    });
    
}

void ScoreLayer::setScore(int score)
{
    m_score = score;
    std::ostringstream oss;
    oss << setw(5) << setfill('0') << m_score;
    m_scoreLabelKuro->setString(oss.str());
    m_scoreLabelSiro->setString(oss.str());
}