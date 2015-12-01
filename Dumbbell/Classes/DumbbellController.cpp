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
    
    return true;
}