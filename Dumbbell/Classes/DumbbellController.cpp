//
//  DumbbellController.cpp
//  Dumbbell
//
//  Created by NakadaTakuya on 2015/12/01.
//
//

#include "DumbbellController.hpp"
#include "EventManager.hpp"
#include "Message.hpp"

bool DumbbellController::init() {
    if (!Node::init()) {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    //背景
    m_controlArea = Sprite::create("dumbbell_controller.png");
    m_controlArea->setAnchorPoint(Vec2(0.5,0.5));
    m_controlArea->setScale(2.6);
    m_controlArea->setPosition(Vec2(visibleSize.width/2, visibleSize.height - 1060));
    addChild(m_controlArea);
    
    m_controlNode = Node::create();
    m_controlNode->setAnchorPoint(Vec2(0.5,0.5));
    m_controlNode->setPosition(Vec2(visibleSize.width/2, visibleSize.height - 1060));
    addChild(m_controlNode);
    
    //丸いやつ
    m_controller = Sprite::create("controller.png");
    m_controller->setAnchorPoint(Vec2(0.5,0.5));
    m_controlNode->addChild(m_controller);
    
    //丸いやつのふわふわ
    m_controllerAlpha = Sprite::create("controller_alpha.png");
    m_controllerAlpha->setAnchorPoint(Vec2(0.5,0.5));
    BlendFunc blend;
    blend.src = GL_SRC_ALPHA;
    blend.dst = GL_ONE;
    m_controllerAlpha->setBlendFunc(blend);
    m_controlNode->addChild(m_controllerAlpha);
    
    //タップを検出する大きさ
    m_touchArea = Node::create();
    m_touchArea->setAnchorPoint(Vec2(0.5,0.5));
    m_touchArea->setPosition(Vec2(visibleSize.width/2, 100));
    m_touchArea->setContentSize(Size(550,200));
    addChild(m_touchArea);
    
    //タップイベントを作成
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(DumbbellController::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(DumbbellController::onTouchMoved, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, m_touchArea);

    isEnable = false;
    return true;
}

void DumbbellController::onEnter()
{
    Node::onEnter();
    
    EventManager::getInstance()->addEventLister<MSG_CHAGE_STATE>([this](EventCustom* event){
        auto msg = static_cast<MSG_CHAGE_STATE*>(event->getUserData());
        if (msg->getStete() == STATE::GAME) {
            isEnable = true;
            Size visibleSize = Director::getInstance()->getVisibleSize();
            m_controlNode->setPosition(Vec2(visibleSize.width/2, visibleSize.height - 1060));
        }
        else
        {
            isEnable = false;
        }
    });
}

bool DumbbellController::onTouchBegan(Touch *touch, Event *event)
{
    if(!isEnable)
        return false;

    auto target = (Sprite*)event->getCurrentTarget();
    Rect targetBox = target->getBoundingBox();
    Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
    if (targetBox.containsPoint(touchPoint))
    {
        m_controlNode->setPositionX(touch->getLocation().x);
        return true;
    }
    return false;
}

void DumbbellController::onTouchMoved(Touch *touch, Event *event)
{
    if(!isEnable)
        return;
    
    auto target = (Sprite*)event->getCurrentTarget();
    Rect targetBox = target->getBoundingBox();
    Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
    if (targetBox.containsPoint(touchPoint))
    {
        m_controlNode->setPositionX(touch->getLocation().x);
    }
}

double DumbbellController::getRotationRate()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto pos = m_controlNode->getPosition();
    auto tocuhAreaSize = m_touchArea->getContentSize();
    auto rate = (pos.x - (visibleSize.width/2 - tocuhAreaSize.width/2))/ tocuhAreaSize.width;
    return rate*2-1;
}







