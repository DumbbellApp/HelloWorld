//
//  ScoreLayer.cpp
//  Dumbbell
//
//  Created by NakadaTakuya on 2015/12/04.
//
//

#include "ScoreLayer.hpp"
#include "iomanip"
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
    
    return true;
}

void ScoreLayer::setScore(int score)
{
    m_score = score;
    std::ostringstream oss;
    oss << setw(5) << setfill('0') << m_score;
    m_scoreLabel->setString(oss.str());
}