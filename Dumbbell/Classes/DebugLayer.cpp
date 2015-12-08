//
//  DebugLayer.cpp
//  Dumbbell
//
//  Created by NakadaTakuya on 2015/12/03.
//
//

#include "DebugLayer.hpp"
#include "Dumbbell.hpp"
#include "DumbbellController.hpp"
#include "ui/UICheckBox.h"
#include "BackGroundLayer.hpp"
#include "BackGroundType.h"
using namespace std;

bool DebugLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto checkBox2 =  ui::CheckBox::create("dumbbell_plate.png", "check.png", ui::CheckBox::TextureResType::LOCAL);
    checkBox2->setScale(0.2);
    checkBox2->setAnchorPoint(Point(0,1));
    checkBox2->setPosition(Vec2(visibleSize.width - 20, visibleSize.height - 20));
    checkBox2->addEventListener( [this]( cocos2d::Ref* target , cocos2d::ui::CheckBox::EventType event_type ) {
        if( event_type == cocos2d::ui::CheckBox::EventType::SELECTED )
        {
            m_menu->setVisible(true);
            m_text1->setVisible(true);
            m_text2->setVisible(true);
            m_text3->setVisible(true);
            m_text4->setVisible(true);
        }else
        {
            m_menu->setVisible(false);
            m_text1->setVisible(false);
            m_text2->setVisible(false);
            m_text3->setVisible(false);
            m_text4->setVisible(false);
        }
    } );
    addChild(checkBox2);
    
    m_isMove = false;
//    auto checkBox =  ui::CheckBox::create("dumbbell_plate.png", "check.png", ui::CheckBox::TextureResType::LOCAL);
//    checkBox->setScale(0.2);
//    checkBox->setAnchorPoint(Point(0,1));
//    checkBox->setPosition(Vec2(0, visibleSize.height - 40));
//    checkBox->addEventListener( [this]( cocos2d::Ref* target , cocos2d::ui::CheckBox::EventType event_type ) {
//        if( event_type == cocos2d::ui::CheckBox::EventType::SELECTED )
//            m_isMove = true;
//        else
//            m_isMove = false;
//    } );
//    addChild(checkBox);
    
    //メニューを作成
    m_menu = Menu::create();
    m_menu->setPosition(Point::ZERO);
    this->addChild(m_menu);
    
    m_text1 = Label::createWithSystemFont(" ", "HiraKakuProN-W6", 20);
    m_text1->setAnchorPoint(Vec2(0,1));
    m_text1->setPosition(Point(20, visibleSize.height));
    this->addChild(m_text1);
    
    m_text2 = Label::createWithSystemFont("", "HiraKakuProN-W6", 20);
    m_text2->setAnchorPoint(Vec2(0,1));
    m_text2->setPosition(Point(20, visibleSize.height-20));
    this->addChild(m_text2);
    
    auto mItem1 = MenuItemImage::create("CloseNormal.png","CloseSelected.png",[this](Ref*sender){
        m_dumbbell->setRotationSpeed(m_dumbbell->getRotationSpeed() + 0.5);
    });
    auto mItem2 = MenuItemImage::create("CloseNormal.png","CloseSelected.png",[this](Ref*sender){
        m_dumbbell->setRotationSpeed(m_dumbbell->getRotationSpeed() - 0.5);
    });
    
    mItem1->setPosition(Point(200, visibleSize.height-20));
    mItem2->setPosition(Point(220, visibleSize.height-20));
    mItem1->setAnchorPoint(Vec2(0,1));
    mItem2->setAnchorPoint(Vec2(0,1));
    mItem1->setScale(0.5);
    mItem2->setScale(0.5);
    m_menu->addChild(mItem1);
    m_menu->addChild(mItem2);
    
    m_text3 = Label::createWithSystemFont("", "HiraKakuProN-W6", 20);
    m_text3->setAnchorPoint(Vec2(0,1));
    m_text3->setPosition(Point(20, visibleSize.height-40));
    this->addChild(m_text3);
    
    auto mItem3 = MenuItemImage::create("CloseNormal.png","CloseSelected.png",[this](Ref*sender){
        m_dumbbell->setMoveSpeed(m_dumbbell->getMoveSpeed() + 0.1);
    });
    auto mItem4 = MenuItemImage::create("CloseNormal.png","CloseSelected.png",[this](Ref*sender){
        m_dumbbell->setMoveSpeed(m_dumbbell->getMoveSpeed() - 0.1);
    });
    
    mItem3->setPosition(Point(200, visibleSize.height-40));
    mItem4->setPosition(Point(220, visibleSize.height-40));
    mItem3->setAnchorPoint(Vec2(0,1));
    mItem4->setAnchorPoint(Vec2(0,1));
    mItem3->setScale(0.5);
    mItem4->setScale(0.5);
    m_menu->addChild(mItem3);
    m_menu->addChild(mItem4);
    
    m_text4 = Label::createWithSystemFont("", "HiraKakuProN-W6", 20);
    m_text4->setAnchorPoint(Vec2(0,1));
    m_text4->setPosition(Point(20, visibleSize.height-60));
    this->addChild(m_text4);
    
    auto mItem5 = MenuItemImage::create("CloseNormal.png","CloseSelected.png",[this](Ref*sender){
        m_dumbbell->setShaftLength(m_dumbbell->getShaftLength() + 0.5);
        m_dumbbell->setScale(m_dumbbell->getShaftLength(), 1);
        m_dumbbell->setContentSize(Size(m_dumbbell->getContentSize().width*m_dumbbell->getShaftLength(), m_dumbbell->getContentSize().height));
    });
    auto mItem6 = MenuItemImage::create("CloseNormal.png","CloseSelected.png",[this](Ref*sender){
        m_dumbbell->setShaftLength(m_dumbbell->getShaftLength() - 0.5);
        m_dumbbell->setScale(m_dumbbell->getShaftLength(), 1);
        m_dumbbell->setContentSize(Size(m_dumbbell->getContentSize().width*m_dumbbell->getShaftLength(), m_dumbbell->getContentSize().height));
    });
    
    mItem5->setPosition(Point(200, visibleSize.height-60));
    mItem6->setPosition(Point(220, visibleSize.height-60));
    mItem5->setAnchorPoint(Vec2(0,1));
    mItem6->setAnchorPoint(Vec2(0,1));
    mItem5->setScale(0.5);
    mItem6->setScale(0.5);
    m_menu->addChild(mItem5);
    m_menu->addChild(mItem6);
    
    //初期化
    auto mItem7 = MenuItemImage::create("CloseNormal.png","CloseSelected.png",[this](Ref*sender){
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        m_dumbbell->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        m_dumbbell->setRotation(0);
        m_dumbbell->m_preAnchorX = 0;
    });
    mItem7->setPosition(Point(0, visibleSize.height-0));
    mItem7->setAnchorPoint(Vec2(0,1));
    mItem7->setScale(0.5);
    m_menu->addChild(mItem7);
    
    //水平移動のみ
    m_isHorizonMove = false;
//    auto checkBox1 =  ui::CheckBox::create("dumbbell_plate.png", "check.png", ui::CheckBox::TextureResType::LOCAL);
//    checkBox1->setScale(0.2);
//    checkBox1->setAnchorPoint(Point(0,1));
//    checkBox1->setPosition(Vec2(0, visibleSize.height -80));
//    checkBox1->addEventListener( [this]( cocos2d::Ref* target , cocos2d::ui::CheckBox::EventType event_type ) {
//        if( event_type == cocos2d::ui::CheckBox::EventType::SELECTED )
//            m_isHorizonMove = true;
//        else
//            m_isHorizonMove = false;
//    } );
//    addChild(checkBox1);

    //背景のでばっく機能
    auto mItem8 = MenuItemImage::create("CloseNormal.png","CloseSelected.png",[this](Ref*sender){
        m_backGroundLayer->chageBackGround(BackGroundType::Type1);
    });
    mItem8->setPosition(Point(0, visibleSize.height-80));
    mItem8->setAnchorPoint(Vec2(0,1));
    mItem8->setScale(0.5);
    m_menu->addChild(mItem8);
    
    mItem8 = MenuItemImage::create("CloseNormal.png","CloseSelected.png",[this](Ref*sender){
        m_backGroundLayer->chageBackGround(BackGroundType::Type2);
    });
    mItem8->setPosition(Point(20, visibleSize.height-80));
    mItem8->setAnchorPoint(Vec2(0,1));
    mItem8->setScale(0.5);
    m_menu->addChild(mItem8);

    mItem8 = MenuItemImage::create("CloseNormal.png","CloseSelected.png",[this](Ref*sender){
        m_backGroundLayer->chageBackGround(BackGroundType::Type3);
    });
    mItem8->setPosition(Point(40, visibleSize.height-80));
    mItem8->setAnchorPoint(Vec2(0,1));
    mItem8->setScale(0.5);
    m_menu->addChild(mItem8);
    
    mItem8 = MenuItemImage::create("CloseNormal.png","CloseSelected.png",[this](Ref*sender){
        m_backGroundLayer->chageBackGround(BackGroundType::Type4);
    });
    mItem8->setPosition(Point(60, visibleSize.height-80));
    mItem8->setAnchorPoint(Vec2(0,1));
    mItem8->setScale(0.5);
    m_menu->addChild(mItem8);
    
    mItem8 = MenuItemImage::create("CloseNormal.png","CloseSelected.png",[this](Ref*sender){
        m_backGroundLayer->chageBackGround(BackGroundType::Type5);
    });
    mItem8->setPosition(Point(80, visibleSize.height-80));
    mItem8->setAnchorPoint(Vec2(0,1));
    mItem8->setScale(0.5);
    m_menu->addChild(mItem8);
    
    mItem8 = MenuItemImage::create("CloseNormal.png","CloseSelected.png",[this](Ref*sender){
        m_backGroundLayer->chageBackGround(BackGroundType::Type6);
    });
    mItem8->setPosition(Point(100, visibleSize.height-80));
    mItem8->setAnchorPoint(Vec2(0,1));
    mItem8->setScale(0.5);
    m_menu->addChild(mItem8);
    
    m_menu->setVisible(false);
    m_text1->setVisible(false);
    m_text2->setVisible(false);
    m_text3->setVisible(false);
    m_text4->setVisible(false);
    
    scheduleUpdate();
    return true;
}

void DebugLayer::update(float delta)
{
    m_text1->setString(to_string(m_dumbbellController->getRotationRate()));
    m_text2->setString(to_string(m_dumbbell->getRotationSpeed()));
    m_text3->setString(to_string(m_dumbbell->getMoveSpeed()));
    m_text4->setString(to_string(m_dumbbell->getShaftLength()));
}