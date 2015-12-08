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

    m_plateL = Sprite::create("dumbbell_left.png");
    m_plateL->setAnchorPoint(Point(0.5,0.5));
    m_plateL->setPositionX(this->getPosition().x - m_plateR->getContentSize().width / 2 + 20);
    m_plateL->setPositionY(0);
    addChild(m_plateL);
    
    
//    setContentSize(Size(m_shaft->getContentSize().width*m_shaftlength, m_shaft->getContentSize().height));
    setAnchorPoint(Vec2(0.0,0.5));
    
    m_rotationSpeed = 10;
    m_moveSpeed = 6;
    return true;
}

//回転率(-1~1)に応じて回転させる
//1->右回転，0->静止，-1->左回転
void Dumbbell::addRotation(float rotationRate)
{
//    auto anchorX =  (1 - fabs(rotationRate));
    auto anchorX =  rotationRate/2;
    setAnchorPoint(Vec2(anchorX, 0.5));
    auto rotation = getRotation() + rotationRate*m_rotationSpeed;
    setRotation(rotation);
    
    //anchorを変更した事による座標のズレを元にもどす
    setPositionX(getPosition().x + cos(getRotation()*M_PI/180)*(anchorX - m_preAnchorX)*getContentSize().width);
    setPositionY(getPosition().y - sin(getRotation()*M_PI/180)*(anchorX - m_preAnchorX)*getContentSize().width);
    
    m_preAnchorX = anchorX;
}

void Dumbbell::move()
{
    auto moveRate = (1 - fabs(getAnchorPoint().x)*2);
    
    auto rad = -getRotation()*M_PI/180;
    Vec2 housenn(-sin(rad), cos(rad));
    setPosition(getPosition() + (housenn*moveRate*m_moveSpeed));
}
