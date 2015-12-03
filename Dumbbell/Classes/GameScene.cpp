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
#include "ScoreLayer.hpp"
#include "TimeLayer.hpp"
#include "DumbbellController.hpp"
#include "BackGroundLayer.hpp"
#include "DebugLayer.hpp"
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
    addChild(m_dumbbell, LAYER_MAIN);
    
    m_blockManager = BlockManager::create();
    addChild(m_blockManager, LAYER_MAIN);
    
    // ラベル類
    m_scoreLayer = ScoreLayer::create();
    addChild(m_scoreLayer, LAYER_UI);
    
    m_timeLayer = TimeLayer::create();
    addChild(m_timeLayer, LAYER_UI);
    
    //ダンベルコントローラー
    m_dumbbellcontroller = DumbbellController::create();
    addChild(m_dumbbellcontroller, LAYER_UI);
    
    //背景
    auto bgLayer =  BackGroundLayer::create();
    addChild(bgLayer,LAYER_BACKGROUND);
    
#ifdef COCOS2D_DEBUG
    //デバックレイヤー
    auto debugLayer = DebugLayer::create();
    debugLayer->m_dumbbell = m_dumbbell;
    debugLayer->m_dumbbellController = m_dumbbellcontroller;
    debugLayer->m_backGroundLayer = bgLayer;
    addChild(debugLayer, 100);
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
    
    m_scoreLayer->setScore(m_score);
    m_timeLayer->setTime(m_leaveTime);
    
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
    
    m_rotationRate = m_dumbbellcontroller->getRotationRate();
    auto direction = m_dumbbellcontroller->getMoveDirection();
    
    m_dumbbell->addRotation(m_rotationRate, direction);
    m_dumbbell->move(direction);

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







