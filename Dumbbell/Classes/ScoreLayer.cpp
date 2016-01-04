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
    
    m_scoreBack = Sprite::create("score_back.png");
    m_scoreBack->setPosition(Vec2(visibleSize.width/2, visibleSize.height + m_scoreBack->getContentSize().height/2));
    addChild(m_scoreBack);
    
    m_scoreSpriteSiro = Sprite::create("score_siro.png");
    m_scoreSpriteSiro->setPosition(Vec2(235, 46));
    m_scoreBack->addChild(m_scoreSpriteSiro);
    
    m_scoreLabelSiro = Label::createWithBMFont("siro.fnt", oss.str());
    m_scoreLabelSiro->setPosition(Point(405, 46));
    m_scoreBack->addChild(m_scoreLabelSiro, 1);
    
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
            Size visibleSize = Director::getInstance()->getVisibleSize();
            Vec2 origin = Director::getInstance()->getVisibleOrigin();
            auto move = MoveTo::create(2, Vec2(visibleSize.width/2, visibleSize.height - 21));
            m_scoreBack->runAction(move);
        }
        else if(msg->getStete() == STATE::RESULT)
        {
//            auto fade = FadeOut::create(2);
//            this->runAction(fade);
        }
    });
    
    //スコアが変更した時に呼び出されるMsg
    EventManager::getInstance()->addEventLister<MSG_CHAGE_SCORE>([this](EventCustom* event){
        auto msg = static_cast<MSG_CHAGE_SCORE*>(event->getUserData());
        setScore(msg->getScore());
    });
    
//    EventManager::getInstance()->addEventLister<MSG_CHAGE_BACK>([this](EventCustom* event){
//        auto msg = static_cast<MSG_CHAGE_BACK*>(event->getUserData());
//        auto type = msg->getBGType();
//        if (type == BackGroundType::Type2 || type == BackGroundType::Type3) {
//            if(m_backGroundType != BackGroundType::Type2 || m_backGroundType != BackGroundType::Type3)
//            {
//                m_siro->setVisible(true);
//                //白に変える
//                auto fade =  FadeOut::create(3);
//                auto callback = CallFunc::create([this](){
//                    m_kuro->setVisible(false);
//                });
//                m_kuro->runAction(Sequence::create(fade,callback, NULL));
//            }
//        }
//        else
//        {
//            if(m_backGroundType == BackGroundType::Type2 || m_backGroundType == BackGroundType::Type3)
//            {
//                m_kuro->setVisible(true);
//                //黒に変える
//                auto fade =  FadeIn::create(3);
//                auto callback = CallFunc::create([this](){
//                    m_siro->setVisible(false);
//                });
//                m_kuro->runAction(Sequence::create(fade,callback, NULL));
//            }
//        }
//        m_backGroundType = type;
//    });
    
}

void ScoreLayer::setScore(int score)
{
    m_score = score;
    std::ostringstream oss;
    oss << setw(5) << setfill('0') << m_score;
    m_scoreLabelSiro->setString(oss.str());
}