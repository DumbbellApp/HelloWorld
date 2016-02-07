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
    
    Dumbbell* dumbbell;
    dumbbell = Dumbbell::create();
    dumbbell->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height - 850 + origin.y));
    dumbbell->setScale(0.7);
    dumbbell->m_preAnchorX = 0;
    addChild(dumbbell, LAYER_MAIN);
    m_dumbbell.push_back(dumbbell);
    
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
    debugLayer->m_dumbbell = m_dumbbell.front();
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
        m_blockType = changeBlockType();
        m_changeScoreBlockItv = 0;
    }
    
    if (m_dumbbell.size() > 0) {
        for (auto itr = m_dumbbell.begin(); itr != m_dumbbell.end(); ) {
            if (isDeleteDumbbell((*itr))) {
                deleteDumbbell(itr);
                log("ダンベル削除");
                continue;
            }
            itr++;
        }
    }
    
    
    for (auto itr : m_dumbbell) {
        if (isCreateDumbbellClone(itr)) {
            createDumbbellclone(itr);
            log("クローン生成");
        }
    }
    
    m_rotationRate = m_dumbbellcontroller->getRotationRate();
    
    if (m_dumbbell.size() > 0) {
        for (auto itr : m_dumbbell) {
            itr->addRotation(m_rotationRate, delta);
            itr->move(delta);
        }
    }

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
            Dumbbell* dumbbell = m_dumbbell.front();
            dumbbell->setRotation(0);
            dumbbell->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height - 850 + origin.y));
            dumbbell->setOrdinal(1);
            
            std::vector<Dumbbell*>::iterator itr = m_dumbbell.begin();
            itr++;
            
            for (; itr != m_dumbbell.end(); itr++) {
                (*itr)->removeFromParent();
            }
            
            m_dumbbell.clear();
            m_dumbbell.push_back(dumbbell);
            
            
            m_blockManager->resetBlocks();
            
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

ScoreBlock::BlockType GameScene::changeBlockType()
{
    srand((unsigned int)time(NULL));
    int blockType = rand() % 3;
    
    switch (blockType) {
        case (int)ScoreBlock::BlockType::LEFT:
            return ScoreBlock::BlockType::LEFT;
            break;
        case (int)ScoreBlock::BlockType::RIGHT:
            return ScoreBlock::BlockType::RIGHT;
            break;
        case (int)ScoreBlock::BlockType::ANY:
            return ScoreBlock::BlockType::ANY;
            break;
        default:
            break;
    }
    
    return ScoreBlock::BlockType::ANY;
}

bool GameScene::isCreateDumbbellClone(Dumbbell* dumbbell)
{
        
    Vec2 dumbbellPos = dumbbell->getPosition();
    Vec2 dumlastPosition = dumbbell->getLastPosition();
    
    if (dumlastPosition.x < CREATE_CLONE_LINE_X_R && dumbbellPos.x >= CREATE_CLONE_LINE_X_R) {
        return true;
    }
    if (dumlastPosition.x > CREATE_CLONE_LINE_X_L && dumbbellPos.x <= CREATE_CLONE_LINE_X_L) {
        return true;
    }
    if (dumlastPosition.y < CREATE_CLONE_LINE_Y_T && dumbbellPos.y >= CREATE_CLONE_LINE_Y_T) {
        return true;
    }
    if (dumlastPosition.y > CREATE_CLONE_LINE_Y_B && dumbbellPos.y <= CREATE_CLONE_LINE_Y_B) {
        return true;
    }
    
    return false;
}

bool GameScene::isDeleteDumbbell(Dumbbell* dumbbell)
{
    
    Vec2 dumbbellPos = dumbbell->getPosition();
    Vec2 dumlastPosition = dumbbell->getLastPosition();

    if (dumlastPosition.x < DELETE_D_LINE_X_R && dumbbellPos.x >= DELETE_D_LINE_X_R) {
        return true;
    }
    if (dumlastPosition.x > DELETE_D_LINE_X_L && dumbbellPos.x <= DELETE_D_LINE_X_L) {
        return true;
    }
    if (dumlastPosition.y < DELETE_D_LINE_Y_T && dumbbellPos.y >= DELETE_D_LINE_Y_T) {
        return true;
    }
    if (dumlastPosition.y > DELETE_D_LINE_Y_B && dumbbellPos.y <= DELETE_D_LINE_Y_B) {
        return true;
    }
    
    return false;
}

void GameScene::createDumbbellclone(Dumbbell* dumbbell)
{
    Dumbbell* dumbbellClone = Dumbbell::create();
    float pos_x;
    float pos_y;
    float lastPos_x;
    float lastPos_y;
    
    if (dumbbell->getPositionX() >= CREATE_CLONE_LINE_X_R) {
        pos_x = dumbbell->getPositionX() - Director::getInstance()->getWinSize().width;
        lastPos_x = dumbbell->getLastPosition().x - Director::getInstance()->getWinSize().width;
    }
    else if (dumbbell->getPositionX() <= CREATE_CLONE_LINE_X_L){
        pos_x = dumbbell->getPositionX() + Director::getInstance()->getWinSize().width;
        lastPos_x = dumbbell->getLastPosition().x + Director::getInstance()->getWinSize().width;

    }
    else {
        pos_x = dumbbell->getPositionX();
        lastPos_x = dumbbell->getLastPosition().x;
    }
    
    if (dumbbell->getPositionY() >= CREATE_CLONE_LINE_Y_T) {
        pos_y = dumbbell->getPositionY() - Director::getInstance()->getWinSize().height * SCORE_LABEL_CORRECTION;
        lastPos_y = dumbbell->getLastPosition().y - Director::getInstance()->getWinSize().height * SCORE_LABEL_CORRECTION;
    }
    else if (dumbbell->getPositionY() <= CREATE_CLONE_LINE_Y_B) {
        pos_y = dumbbell->getPositionY() + Director::getInstance()->getWinSize().height * SCORE_LABEL_CORRECTION;
        lastPos_y = dumbbell->getLastPosition().y + Director::getInstance()->getWinSize().height * SCORE_LABEL_CORRECTION;

    }
    else {
        pos_y = dumbbell->getPositionY();
        lastPos_y = dumbbell->getLastPosition().y;

    }
    
    dumbbellClone->setPosition(Vec2(pos_x, pos_y));
    dumbbellClone->setLastPosition(Vec2(lastPos_x, lastPos_y));
    dumbbellClone->setScale(0.7);
    dumbbellClone->setRotation(dumbbell->getRotation());
    dumbbellClone->setRotationSpeed(dumbbell->getRotationSpeed());
    dumbbellClone->setMoveSpeed(dumbbell->getMoveSpeed());
    dumbbellClone->m_moveDirection = dumbbell->m_moveDirection;
    dumbbellClone->m_preAnchorX = dumbbell->m_preAnchorX;
    dumbbellClone->setOrdinal(2);

    addChild(dumbbellClone, LAYER_MAIN);
    m_dumbbell.push_back(dumbbellClone);
}

void GameScene::deleteDumbbell(std::vector<Dumbbell*>::iterator itr)
{
    (*itr)->removeFromParent();
    m_dumbbell.erase(itr);
}





