//
//  Dumbbell.cpp
//  HelloWorld
//
//  Created by NakadaTakuya on 2015/11/22.
//
//

#include "Dumbbell.hpp"

namespace {
    static const double defaultMoveSpeed = 360;
    static const double defaultRotationSpeed = 600;
    static const double moveThreshold = 0.5;
    static const double decelerationRate = defaultMoveSpeed/3.0;
}

bool Dumbbell::init() {
    if (!Node::init()) {
        return false;
    }
    
    m_preAnchorX = 0;
    
    m_plateR = Sprite::create("dumbbell_right.png");
    m_plateR->setAnchorPoint(Point(0.5,0.5));
    m_plateR->setPositionX(this->getPosition().x + m_plateR->getContentSize().width / 2 - 20);
    m_plateR->setPositionY(0);
    addChild(m_plateR);
    
    auto plateRAlpha = Sprite::create("dumbbell_right_alpha.png");
    plateRAlpha->setAnchorPoint(Point(0,0));
    BlendFunc blend;
    blend.src = GL_SRC_ALPHA;
    blend.dst = GL_ONE;
    plateRAlpha->setBlendFunc(blend);
    m_plateR->addChild(plateRAlpha);
    
    m_plateL = Sprite::create("dumbbell_left.png");
    m_plateL->setAnchorPoint(Point(0.5,0.5));
    m_plateL->setPositionX(this->getPosition().x - m_plateR->getContentSize().width / 2 + 20);
    m_plateL->setPositionY(0);
    addChild(m_plateL);
    
    auto plateLAlpha = Sprite::create("dumbbell_left_alpha.png");
    plateLAlpha->setAnchorPoint(Point(0,0));
    plateLAlpha->setBlendFunc(blend);
    m_plateL->addChild(plateLAlpha);
    
    setAnchorPoint(Vec2(0.0,0.5));
    
    m_rotationSpeed = defaultRotationSpeed;
    m_moveSpeed = defaultMoveSpeed;
    return true;
}

//回転率(-1~1)に応じて回転させる
//1->右回転，0->静止，-1->左回転
void Dumbbell::addRotation(float rotationRate, float delta)
{
    auto anchorX =  rotationRate/2;
    setAnchorPoint(Vec2(anchorX, 0.5));
    auto rotation = getRotation() + rotationRate*m_rotationSpeed*delta;
    setRotation(rotation);
    
    //anchorを変更した事による座標のズレを元にもどす
    setPositionX(getPosition().x + cos(getRotation()*M_PI/180)*(anchorX - m_preAnchorX)*getContentSize().width);
    setPositionY(getPosition().y - sin(getRotation()*M_PI/180)*(anchorX - m_preAnchorX)*getContentSize().width);
    
    m_preAnchorX = anchorX;
}

void Dumbbell::move(float delta)
{
    auto moveRate = (1 - fabs(getAnchorPoint().x)*2);
    auto rad = -getRotation()*M_PI/180;
    
    if(moveRate > moveThreshold)
    {
        m_moveDirection = Vec2(-sin(rad), cos(rad));
        m_moveSpeed = defaultMoveSpeed;
    }
    else
    {
        //0~1の範囲に
        double rate = moveRate/moveThreshold;
        rate = pow(rate, 3);
        m_moveDirection = (1-rate)*m_moveDirection + rate*Vec2(-sin(rad), cos(rad));
        m_moveDirection = m_moveDirection/m_moveDirection.length();
        m_moveSpeed -= decelerationRate*delta;
        m_moveSpeed = clampf(m_moveSpeed, 0, defaultMoveSpeed);
        moveRate = moveThreshold;
    }
    
    setPosition(getPosition() + (m_moveDirection*moveRate*m_moveSpeed*delta));
}
