//
//  Obstacle.cpp
//  
//
//  Created by Ren Awagakubo on 2015/11/29.
//
//

#include "BlockManager.hpp"
#include "ObstacleBlock.hpp"
#include "ScoreBlock.hpp"
#include "Dumbbell.hpp"
#include <time.h>
#include <SimpleAudioEngine.h>

bool BlockManager::init()
{
    if(!Node::init()) {
        return false;
    }
    
    auto winSize = Director::getInstance()->getWinSize();
    
    //spriteで生成
    auto obstacle = ObstacleBlock::create();
    obstacle->setPosition(Vec2(winSize.width /2.0, winSize.height));
    addChild(obstacle);
    m_obstacles.push_back(obstacle);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("akan.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("ookini.mp3");

    this->scheduleUpdate();
    return true;
}

void BlockManager::update(float dt)
{
    
    move();
//    calcCollision();
 
}

void BlockManager::createObstacleBlock()
{
    auto winSize = Director::getInstance()->getWinSize();
    
    srand((unsigned int)time(NULL));
    int rand_x = rand() % (int)winSize.width;
    
    //spriteで生成
    auto obstacle = ObstacleBlock::create();
    obstacle->setPosition(Vec2(rand_x, winSize.height + 30));
    addChild(obstacle);
    m_obstacles.push_back(obstacle);
}

void BlockManager::createScoreBlock()
{
    auto winSize = Director::getInstance()->getWinSize();
    
    srand((unsigned int)time(NULL));
    int rand_x = rand() % (int)winSize.width;
    int rand_y = rand() % (int)winSize.height;
    
    //spriteで生成
    auto scoreBlock = ScoreBlock::create();
    scoreBlock->setPosition(Vec2(rand_x, rand_y));
    addChild(scoreBlock);
    m_scoreBlock.push_back(scoreBlock);
}

void BlockManager::move()
{
    for (auto itr : m_obstacles) {
        itr->move();
    }
}

int BlockManager::calcCollisionObstacleBlock(Dumbbell* dumbbell)
{
    int collisionCnt = 0;
    
    for (auto itr = m_obstacles.begin(); itr != m_obstacles.end(); ) {
        //pImg1とpImg2の表示領域を取得
        Rect rect = (*itr)->boundingBox();
        
        //障害物とダンベルかさなっているか
        if(rect.intersectsRect(dumbbell->boundingBox())) {
            collisionCnt++;
            (*itr)->removeFromParent();
            m_obstacles.erase(itr);
            
            //音楽を再生する
            //
            int soundID;
            soundID = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("akan.mp3");
            log("障害物に衝突");
            continue;
        }
        itr++;
        
    }
    
    return collisionCnt;
}

int BlockManager::calcCollisionScoreBlock(Dumbbell *dumbbell)
{
    int collisionCnt = 0;
    
    for (auto itr = m_scoreBlock.begin(); itr != m_scoreBlock.end(); ) {
        //pImg1とpImg2の表示領域を取得
        Rect rect = (*itr)->boundingBox();
        
        //障害物とダンベルかさなっているか
        if(rect.intersectsRect(dumbbell->boundingBox())) {
            collisionCnt++;
            (*itr)->removeFromParent();
            m_scoreBlock.erase(itr);
            
            //音楽を再生する
            //
            int soundID;
            soundID = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ookini.mp3");
            log("スコアブロック獲得");
            continue;
        }
        itr++;
        
    }
    
    return collisionCnt;
}