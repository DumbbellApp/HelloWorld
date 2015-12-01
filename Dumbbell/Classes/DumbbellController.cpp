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
    
    m_controlArea = Sprite::create("control_area.png");
    m_controlArea->setAnchorPoint(Vec2(0.5,0.5));
    m_controlArea->setPosition(Vec2(visibleSize.width/2, 100));
    addChild(m_controlArea);
    
    //タップイベントを作成
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(DumbbellController::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(DumbbellController::onTouchMoved, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, m_controlArea);
    
    m_controller = Sprite::create("controller.png");
    m_controller->setAnchorPoint(Vec2(0.5,0.5));
    m_controller->setPosition(Vec2(visibleSize.width/2, 100));
    addChild(m_controller);
    
    return true;
}

bool DumbbellController::onTouchBegan(Touch *touch, Event *event)
{
    auto target = (Sprite*)event->getCurrentTarget();
    Rect targetBox = target->getBoundingBox();
    Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
    if (targetBox.containsPoint(touchPoint))
    {
        m_controller->stopAllActions();
        auto length = m_controller->getPosition().getDistance(touch->getLocation());
        auto move = MoveTo::create(length/10000.0, touch->getLocation());
        m_controller->runAction(move);
        return true;
    }
    return true;
}

void DumbbellController::onTouchMoved(Touch *touch, Event *event)
{
    auto target = (Sprite*)event->getCurrentTarget();
    Rect targetBox = target->getBoundingBox();
    Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
    if (targetBox.containsPoint(touchPoint))
    {
        m_controller->stopAllActions();
        auto length = m_controller->getPosition().getDistance(touch->getLocation());
        auto move = MoveTo::create(length/10000.0, touch->getLocation());
        m_controller->runAction(move);
    }
}

double DumbbellController::getRotationRate()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto pos = m_controller->getPosition();
    auto areaSize = m_controlArea->getContentSize();
    auto rate = (pos.x - (visibleSize.width/2 - areaSize.width/2))/ areaSize.width;
    return rate*2-1;
}

int DumbbellController::getMoveDirection()
{
    auto conPos = m_controller->getPosition();
    auto areaPos = m_controlArea->getPosition();
    return (conPos.y > areaPos.y ? 1 : -1);
}







