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
#include "DumbbellController.hpp"
#include "BackGroundLayer.hpp"
#include "DebugLayer.hpp"
#include "UILayer.hpp"
#include "EventManager.hpp"
#include "Message.hpp"
#include "ScoreManager.hpp"

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
    
    m_hitPoint = 5;
    m_leaveTime = 60;
    m_obstacleItv = 0;
    m_scoreBlockItv = 0;
    m_state = STATE::TITLE;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
        
    m_dumbbell = Dumbbell::create();
    m_dumbbell->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height - 850 + origin.y));
    m_dumbbell->setScale(0.7);
    m_dumbbell->m_preAnchorX = 0;
    addChild(m_dumbbell, LAYER_MAIN);
    
    m_blockManager = BlockManager::create();
    addChild(m_blockManager, LAYER_MAIN);
        
    //ダンベルコントローラー
    m_dumbbellcontroller = DumbbellController::create();
    addChild(m_dumbbellcontroller, LAYER_UI);
    
    //背景
    auto bgLayer =  BackGroundLayer::create();
    addChild(bgLayer,LAYER_BACKGROUND);
    
    //UI
    m_uiLayer = UILayer::create();
    addChild(m_uiLayer, LAYER::LAYER_UI);
    
#ifdef COCOS2D_DEBUG
    //デバックレイヤー
    auto debugLayer = DebugLayer::create();
    debugLayer->m_dumbbell = m_dumbbell;
    debugLayer->m_dumbbellController = m_dumbbellcontroller;
    debugLayer->m_backGroundLayer = bgLayer;
    addChild(debugLayer, 100);
#endif
    return true;
}

void GameScene::update(float delta){
    m_obstacleItv += delta;
    m_scoreBlockItv += delta;
    m_leaveTime -= delta;
    
    if (!m_isCreateScoreBlock) {
        m_changeScoreBlockItv += delta;
    }
    
    int collisionCntObs = calcCollisionObstacleBlock();
    m_hitPoint -= collisionCntObs;
    
    ScoreManager::getInstance()->addScore(calcCollisionScoreBlock());

    MSG_CHAGE_TIME timeChangeMsg((int)m_leaveTime);
    EventManager::getInstance()->dispatch(timeChangeMsg);
    
    if (m_hitPoint <= 0 || m_leaveTime < 0)
    {
        //終了
        MSG_CHAGE_STATE msg(STATE::RESULT);
        EventManager::getInstance()->dispatch(msg);
        log("ゲーム終了");
    }
    
    if (m_obstacleItv >= 5) {
        m_blockManager->createObstacleBlock();
        m_obstacleItv = 0;
    }
    
    if (m_scoreBlockItv >= 1 && m_isCreateScoreBlock) {
        m_blockManager->createScoreBlock(m_blockType);
        m_createScoreBlockCnt++;
        if (m_createScoreBlockCnt == 5) {
            m_createScoreBlockCnt = 0;
            m_isCreateScoreBlock = false;
        }
        
        m_scoreBlockItv = 0;
    }
    
    if (m_changeScoreBlockItv >= 3) {
        m_isCreateScoreBlock = true;
        m_changeScoreBlockItv = 0;
    }
    
    m_rotationRate = m_dumbbellcontroller->getRotationRate();
    
    m_dumbbell->addRotation(m_rotationRate);
    m_dumbbell->move();

}

void GameScene::onEnter()
{
    Layer::onEnter();
    
    //Stateが変わった時の処理
    EventManager::getInstance()->addEventLister<MSG_CHAGE_STATE>([this](EventCustom* event){
        auto msg = static_cast<MSG_CHAGE_STATE*>(event->getUserData());
        if (msg->getStete() == STATE::GAME) {
            //ゲーム開始時の初期化処理をここに書く
            Size visibleSize = Director::getInstance()->getVisibleSize();
            Vec2 origin = Director::getInstance()->getVisibleOrigin();

            m_hitPoint = 5;
            m_leaveTime = 60;
            m_obstacleItv = 0;
            m_scoreBlockItv = 0;
            m_changeScoreBlockItv = 0;
            m_createScoreBlockCnt = 0;
            m_isCreateScoreBlock = true;
            m_blockType = ScoreBlock::BlockType::ANY;
            m_dumbbell->setRotation(0);
            m_dumbbell->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height - 850 + origin.y));
            
            auto func = CallFunc::create([this](){
                this->scheduleUpdate();
            });
            this->runAction(Sequence::create(DelayTime::create(2),func, NULL));

        }
        else if(msg->getStete() == STATE::RESULT)
        {
            this->unscheduleUpdate();
        }
        
    });
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







