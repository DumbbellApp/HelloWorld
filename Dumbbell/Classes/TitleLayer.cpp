//
//  TitleLayer.cpp
//  Dumbbell
//
//  Created by NakadaTakuya on 2015/12/05.
//
//

#include "TitleLayer.hpp"
using namespace std;
bool TitleLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    m_titleSprite = Sprite::create("title.png");
    m_titleSprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height - 200));
    addChild(m_titleSprite);

    return true;
}