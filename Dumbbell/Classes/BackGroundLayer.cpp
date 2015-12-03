//
//  BackGroundLayer.cpp
//  Dumbbell
//
//  Created by NakadaTakuya on 2015/12/04.
//
//

#include "BackGroundLayer.hpp"

using namespace std;
bool BackGroundLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    m_isFading = false;
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bg.plist");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    m_nowBackGroundSprite = Sprite::createWithSpriteFrameName("bg_1.png");
    m_nowBackGroundSprite->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    auto size1 = m_nowBackGroundSprite->getContentSize();
    m_nowBackGroundSprite->setScale( visibleSize.width/size1.width, visibleSize.height/size1.height);
    addChild(m_nowBackGroundSprite, LAYER_NOW);

    m_nextBackGroundSprite = Sprite::createWithSpriteFrameName("bg_1.png");
    m_nextBackGroundSprite->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    auto size2 = m_nextBackGroundSprite->getContentSize();
    m_nextBackGroundSprite->setScale( visibleSize.width/size2.width, visibleSize.height/size2.height);
    addChild(m_nextBackGroundSprite, LAYER_NEXT);
    
    return true;
}

void BackGroundLayer::chageBackGround(BackGroundType type)
{
    if(m_isFading)
        return;
    
    m_isFading = true;
    string spriteName = "bg_" + to_string(static_cast<int>(type)) + ".png";
    auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteName);
    m_nextBackGroundSprite->setTexture(frame->getTexture());
    m_nextBackGroundSprite->setTextureRect(frame->getRect());
    
    auto fade =  FadeOut::create(3);
    auto callback = CallFunc::create([this, frame](){
        m_nowBackGroundSprite->setTexture(frame->getTexture());
        m_nowBackGroundSprite->setTextureRect(frame->getRect());
        m_nowBackGroundSprite->setOpacity(255);
        m_isFading = false;
    });
    m_nowBackGroundSprite->runAction(Sequence::create(fade,callback, NULL));
}