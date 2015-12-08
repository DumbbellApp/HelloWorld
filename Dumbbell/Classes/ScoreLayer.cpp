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
    
    m_scoreLabel = Label::createWithBMFont("jun.fnt", oss.str());
    m_scoreLabel->setPosition(Point(visibleSize.width - 100, visibleSize.height - 64));
    addChild(m_scoreLabel);
    
    setOpacity(0);
    setCascadeOpacityEnabled(true);
    
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
}

void ScoreLayer::setScore(int score)
{
    m_score = score;
    std::ostringstream oss;
    oss << setw(5) << setfill('0') << m_score;
    m_scoreLabel->setString(oss.str());
}