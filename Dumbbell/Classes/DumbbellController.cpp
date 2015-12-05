//
//  DumbbellController.cpp
//  Dumbbell
//
//  Created by NakadaTakuya on 2015/12/01.
//
//

#include "DumbbellController.hpp"

bool DumbbellController::init() {
    if (!Node::init()) {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    //背景
    m_controlArea = Sprite::create("dumbbell_controller.png");
    m_controlArea->setAnchorPoint(Vec2(0.5,0.5));
    m_controlArea->setScale(2.5);
    m_controlArea->setPosition(Vec2(visibleSize.width/2, 100));
    addChild(m_controlArea);
    
    //丸いやつ
    m_controller = Sprite::create("controller.png");
    m_controller->setAnchorPoint(Vec2(0.5,0.5));
    m_controller->setScale(0.7);
    m_controller->setPosition(Vec2(visibleSize.width/2, 100));
    addChild(m_controller);
    
    //タップを検出する大きさ
    m_touchArea = Node::create();
    m_touchArea->setAnchorPoint(Vec2(0.5,0.5));
    m_touchArea->setPosition(Vec2(visibleSize.width/2, 100));
    m_touchArea->setContentSize(Size(550,120));
    addChild(m_touchArea);
    
    //タップイベントを作成
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(DumbbellController::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(DumbbellController::onTouchMoved, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, m_touchArea);

    return true;
}

bool DumbbellController::onTouchBegan(Touch *touch, Event *event)
{
    auto target = (Sprite*)event->getCurrentTarget();
    Rect targetBox = target->getBoundingBox();
    Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
    if (targetBox.containsPoint(touchPoint))
    {
        m_controller->setPositionX(touch->getLocation().x);
        return true;
    }
    return false;
}

void DumbbellController::onTouchMoved(Touch *touch, Event *event)
{
    auto target = (Sprite*)event->getCurrentTarget();
    Rect targetBox = target->getBoundingBox();
    Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
    if (targetBox.containsPoint(touchPoint))
    {
        m_controller->setPositionX(touch->getLocation().x);
    }
}

double DumbbellController::getRotationRate()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto pos = m_controller->getPosition();
    auto tocuhAreaSize = m_touchArea->getContentSize();
    auto rate = (pos.x - (visibleSize.width/2 - tocuhAreaSize.width/2))/ tocuhAreaSize.width;
    return rate*2-1;
}







