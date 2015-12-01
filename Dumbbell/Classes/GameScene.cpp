//
//  GameScene.cpp
//  HelloWorld
//
//  Created by NakadaTakuya on 2015/11/22.
//
//

#include "GameScene.hpp"
#include "Dumbbell.hpp"
#include "BlockManager.hpp"
#include "ui/UICheckBox.h"
#include "DumbbellController.hpp"

USING_NS_CC;
using namespace std;
Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    m_score = 0;
    m_hitPoint = 5;
    m_leaveTime = 60;
    m_playTime = 0;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
        
    m_dumbbell = Dumbbell::create();
    m_dumbbell->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    m_dumbbell->m_preAnchorX = 0;
    addChild(m_dumbbell);
    
    m_blockManager = BlockManager::create();
    addChild(m_blockManager);
    
    // ラベル類
    m_scoreHeaderLabel = Label::createWithSystemFont("Score", "HiraKakuProN-W6", 20);
    m_scoreHeaderLabel->setAnchorPoint(Vec2(0,1));
    m_scoreHeaderLabel->setPosition(Point(20, visibleSize.height * 0.8 - 5));
    this->addChild(m_scoreHeaderLabel);
    
    m_scoreLabel = Label::createWithSystemFont("", "HiraKakuProN-W6", 20);
    m_scoreLabel->setString(to_string(m_score));
    m_scoreLabel->setAnchorPoint(Vec2(0,1));
    m_scoreLabel->setPosition(Point(100, visibleSize.height * 0.8 - 5));
    this->addChild(m_scoreLabel);
    
    m_leaveTimeHeaderLabel = Label::createWithSystemFont("Time", "HiraKakuProN-W6", 20);
    m_leaveTimeHeaderLabel->setAnchorPoint(Vec2(0,1));
    m_leaveTimeHeaderLabel->setPosition(Point(20, visibleSize.height * 0.8 + 15));
    this->addChild(m_leaveTimeHeaderLabel);
    
    m_leaveTimeLabel = Label::createWithSystemFont("", "HiraKakuProN-W6", 20);
    m_leaveTimeLabel->setString(to_string((int)m_leaveTime));
    m_leaveTimeLabel->setAnchorPoint(Vec2(0,1));
    m_leaveTimeLabel->setPosition(Point(100, visibleSize.height * 0.8 + 15));
    this->addChild(m_leaveTimeLabel);
    
    //ダンベルコントローラー
    auto dumbbelController = DumbbellController::create();
    addChild(dumbbelController);
    
    
//    //タップイベントを作成
//    auto listener = EventListenerTouchOneByOne::create();
//    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
//    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
//    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
#ifdef COCOS2D_DEBUG
    m_isMove = false;
    auto checkBox =  ui::CheckBox::create("dumbbell_plate.png", "check.png", ui::CheckBox::TextureResType::LOCAL);
    checkBox->setScale(0.2);
    checkBox->setAnchorPoint(Point(0,1));
    checkBox->setPosition(Vec2(0, visibleSize.height - 40));
    checkBox->addEventListener( [this]( cocos2d::Ref* target , cocos2d::ui::CheckBox::EventType event_type ) {
        if( event_type == cocos2d::ui::CheckBox::EventType::SELECTED )
            m_isMove = true;
        else
            m_isMove = false;
    } );
    addChild(checkBox);
    
    //メニューを作成
    auto menu = Menu::create();
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
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
    menu->addChild(mItem1);
    menu->addChild(mItem2);
    
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
    menu->addChild(mItem3);
    menu->addChild(mItem4);
    
    m_text4 = Label::createWithSystemFont("", "HiraKakuProN-W6", 20);
    m_text4->setAnchorPoint(Vec2(0,1));
    m_text4->setPosition(Point(20, visibleSize.height-60));
    this->addChild(m_text4);
    
    auto mItem5 = MenuItemImage::create("CloseNormal.png","CloseSelected.png",[this](Ref*sender){
        m_dumbbell->setShaftLength(m_dumbbell->getShaftLength() + 0.5);
        m_dumbbell->m_shaft->setScale(m_dumbbell->getShaftLength(), 1);
        m_dumbbell->setContentSize(Size(m_dumbbell->m_shaft->getContentSize().width*m_dumbbell->getShaftLength(), m_dumbbell->m_shaft->getContentSize().height));
    });
    auto mItem6 = MenuItemImage::create("CloseNormal.png","CloseSelected.png",[this](Ref*sender){
        m_dumbbell->setShaftLength(m_dumbbell->getShaftLength() - 0.5);
        m_dumbbell->m_shaft->setScale(m_dumbbell->getShaftLength(), 1);
        m_dumbbell->setContentSize(Size(m_dumbbell->m_shaft->getContentSize().width*m_dumbbell->getShaftLength(), m_dumbbell->m_shaft->getContentSize().height));
    });
    
    mItem5->setPosition(Point(200, visibleSize.height-60));
    mItem6->setPosition(Point(220, visibleSize.height-60));
    mItem5->setAnchorPoint(Vec2(0,1));
    mItem6->setAnchorPoint(Vec2(0,1));
    mItem5->setScale(0.5);
    mItem6->setScale(0.5);
    menu->addChild(mItem5);
    menu->addChild(mItem6);
    
    //初期化
    auto mItem7 = MenuItemImage::create("CloseNormal.png","CloseSelected.png",[this](Ref*sender){
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        m_dumbbell->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        m_dumbbell->setRotation(0);
        m_dumbbell->m_preAnchorX = 0;
        m_rotationRate = 0;
    });
    mItem7->setPosition(Point(0, visibleSize.height-0));
    mItem7->setAnchorPoint(Vec2(0,1));
    mItem7->setScale(0.5);
    menu->addChild(mItem7);
    
    //水平移動のみ
    m_isHorizonMove = false;
    auto checkBox1 =  ui::CheckBox::create("dumbbell_plate.png", "check.png", ui::CheckBox::TextureResType::LOCAL);
    checkBox1->setScale(0.2);
    checkBox1->setAnchorPoint(Point(0,1));
    checkBox1->setPosition(Vec2(0, visibleSize.height -80));
    checkBox1->addEventListener( [this]( cocos2d::Ref* target , cocos2d::ui::CheckBox::EventType event_type ) {
        if( event_type == cocos2d::ui::CheckBox::EventType::SELECTED )
            m_isHorizonMove = true;
        else
            m_isHorizonMove = false;
    } );
    addChild(checkBox1);

#endif
    
    this->scheduleUpdate();
    return true;
}

void GameScene::update(float delta){
    m_playTime += delta;
    m_leaveTime -= delta;
    
    int collisionCntObs = calcCollisionObstacleBlock();
    m_hitPoint -= collisionCntObs;
    
    int collisionCntScr = calcCollisionScoreBlock();
    m_score += collisionCntScr * 100;
    
    m_scoreLabel->setString(to_string(m_score));
    m_leaveTimeLabel->setString(to_string(m_leaveTime));

    
    if (m_leaveTime < 0)
    {
        //終了
        // create a scene. it's an autorelease object
        auto scene = GameScene::createScene();
        Director::getInstance()->replaceScene(scene);
        log("ゲーム終了");
        
    }
    
    if (m_hitPoint <= 0)
    {
        //終了
        // create a scene. it's an autorelease object
        auto scene = GameScene::createScene();
        Director::getInstance()->replaceScene(scene);
        log("ゲーム終了");
    }
    
    if (m_playTime >= 5) {
        m_blockManager->createObstacleBlock();
        m_blockManager->createScoreBlock();
        m_playTime = 0;
    }
    
#ifdef COCOS2D_DEBUG
    //水平移動のみ
    if(m_isHorizonMove)
    {
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        m_dumbbell->setAnchorPoint(Vec2(0,0.5));
        m_dumbbell->setRotation(m_dumbbell->getRotation() + m_rotationRate*m_dumbbell->getRotationSpeed());
        m_dumbbell->setPositionY(visibleSize.height/2 + origin.y);
    }
    else
    {
        //全方位移動
        m_dumbbell->addRotation(m_rotationRate);
    }
    
    if (m_isMove)
    {
        m_dumbbell->move();
    }

    m_text1->setString(to_string(m_rotationRate));
    m_text2->setString(to_string(m_dumbbell->getRotationSpeed()));
    m_text3->setString(to_string(m_dumbbell->getMoveSpeed()));
    m_text4->setString(to_string(m_dumbbell->getShaftLength()));
#endif
}

bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
    m_rotationRate = calRotationRate(touch);
    return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *event)
{
    m_rotationRate = calRotationRate(touch);
}

//回転の度合いを-1~1の範囲で表す
float GameScene::calRotationRate(Touch* touch)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point touchPoint = Vec2(touch->getLocationInView().x, touch->getLocationInView().y);
    
    return touchPoint.x/visibleSize.width*2 - 1.f;
}

int GameScene::calcCollisionObstacleBlock()
{
    int collisionCnt = 0;
    collisionCnt = m_blockManager->calcCollisionObstacleBlock(m_dumbbell);
    
    return collisionCnt;
}

int GameScene::calcCollisionScoreBlock()
{
    int collisionCnt = 0;
    collisionCnt = m_blockManager->calcCollisionScoreBlock(m_dumbbell);
    
    return collisionCnt;
}







