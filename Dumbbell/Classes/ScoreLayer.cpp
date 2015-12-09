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
    std::ostringstream oss;
    oss << setw(5) << setfill('0') << m_score;
    
    m_kuro = Node::create();
    addChild(m_kuro, 2);
    
    m_scoreSpriteKuro = Sprite::create("score_kuro.png");
    m_scoreSpriteKuro->setPosition(Vec2(visibleSize.width - 300, visibleSize.height - 64));
    m_kuro->addChild(m_scoreSpriteKuro);
    
    m_scoreLabelKuro = Label::createWithBMFont("kuro.fnt", oss.str());
    m_scoreLabelKuro->setPosition(Point(visibleSize.width - 100, visibleSize.height - 55));
    m_kuro->addChild(m_scoreLabelKuro, 2);

    m_siro = Node::create();
    addChild(m_siro, 1);
    
    m_scoreSpriteSiro = Sprite::create("score_siro.png");
    m_scoreSpriteSiro->setPosition(Vec2(visibleSize.width - 300, visibleSize.height - 64));
    m_siro->addChild(m_scoreSpriteSiro);
    
    m_scoreLabelSiro = Label::createWithBMFont("siro.fnt", oss.str());
    m_scoreLabelSiro->setPosition(Point(visibleSize.width - 100, visibleSize.height - 55));
    m_siro->addChild(m_scoreLabelSiro, 1);
    
    m_siro->setVisible(false);
    
    m_kuro->setCascadeOpacityEnabled(true);
    m_siro->setCascadeOpacityEnabled(true);
    
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
                m_siro->setVisible(true);
                //白に変える
                auto fade =  FadeOut::create(3);
                auto callback = CallFunc::create([this](){
                    m_siro->setZOrder(2);
                    m_kuro->setZOrder(1);
                    m_kuro->setOpacity(255);
                    m_kuro->setVisible(false);
                });
                m_kuro->runAction(Sequence::create(fade,callback, NULL));
            }
        }
        else
        {
            if(m_backGroundType == BackGroundType::Type2 || m_backGroundType == BackGroundType::Type3)
            {
                m_kuro->setVisible(true);
                //黒に変える
                auto fade =  FadeOut::create(3);
                auto callback = CallFunc::create([this](){
                    m_kuro->setZOrder(2);
                    m_siro->setZOrder(1);
                    m_siro->setOpacity(255);
                    m_siro->setVisible(false);
                });
                m_siro->runAction(Sequence::create(fade,callback, NULL));
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