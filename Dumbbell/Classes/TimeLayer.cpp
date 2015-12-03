//
//  TimeLayer.cpp
//  Dumbbell
//
//  Created by NakadaTakuya on 2015/12/04.
//
//

#include "TimeLayer.hpp"
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
    
    m_timeLabel = Label::createWithBMFont("jun.fnt", to_string(m_time));

    m_timeLabel->setPosition(Point(150, visibleSize.height - 64));
    addChild(m_timeLabel);
    
    return true;
}

void TimeLayer::setTime(float time)
{
    m_time = time;
    m_timeLabel->setString(to_string(m_time));
}