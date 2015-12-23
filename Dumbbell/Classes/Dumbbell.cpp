//
//  Dumbbell.cpp
//  HelloWorld
//
//  Created by NakadaTakuya on 2015/11/22.
//
//

#include "Dumbbell.hpp"

bool Dumbbell::init() {
    if (!Node::init()) {
        return false;
    }
    m_preAnchorX = 0;
    m_shaftlength = 10;
    
//    m_shaft = Sprite::create("dumbbell_shaft2.png");
//    m_shaft->setAnchorPoint(Point(0.5,0.5));
//    m_shaft->setScale(m_shaftlength, 1);
//    m_shaft->setPosition(Point::ZERO);
//    addChild(m_shaft);
    
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
    
//    setContentSize(Size(m_shaft->getContentSize().width*m_shaftlength, m_shaft->getContentSize().height));
    setAnchorPoint(Vec2(0.0,0.5));
    
    m_rotationSpeed = 10;
    m_moveSpeed = 6;
    return true;
}

//回転率(-1~1)に応じて回転させる
//1->右回転，0->静止，-1->左回転
void Dumbbell::addRotation(float rotationRate, float delta)
{
//    auto anchorX =  (1 - fabs(rotationRate));
    static int fps = 60;
    auto anchorX =  rotationRate/2;
    setAnchorPoint(Vec2(anchorX, 0.5));
    auto rotation = getRotation() + rotationRate*m_rotationSpeed*delta*fps;
    setRotation(rotation);
    
    //anchorを変更した事による座標のズレを元にもどす
    setPositionX(getPosition().x + cos(getRotation()*M_PI/180)*(anchorX - m_preAnchorX)*getContentSize().width);
    setPositionY(getPosition().y - sin(getRotation()*M_PI/180)*(anchorX - m_preAnchorX)*getContentSize().width);
    
    m_preAnchorX = anchorX;
}

void Dumbbell::move(float delta)
{
    static int fps = 60;
    auto moveRate = (1 - fabs(getAnchorPoint().x)*2);
    
    auto rad = -getRotation()*M_PI/180;
    double threshold = 0.5;
    if(moveRate > threshold)
    {
        m_moveDirection = Vec2(-sin(rad), cos(rad));
    }
    else
    {
        //0~1の範囲に
        double rate = moveRate/threshold;
        
        m_moveDirection = (1-rate*rate)*m_moveDirection + rate*rate*Vec2(-sin(rad), cos(rad));
        m_moveDirection = m_moveDirection/m_moveDirection.length();
        moveRate = 0.5;
    }
    
    setPosition(getPosition() + (m_moveDirection*moveRate*m_moveSpeed*delta*fps));
}
