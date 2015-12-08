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
    float speed = (float)(rand() % 4 + 4) / 5;
    
    //spriteで生成
    auto obstacle = ObstacleBlock::create();
    obstacle->setPosition(Vec2(rand_x, winSize.height + 30));
    obstacle->setMoveSpeed(speed);
    addChild(obstacle);
    m_obstacles.push_back(obstacle);
}

void BlockManager::createScoreBlock()
{
    auto winSize = Director::getInstance()->getWinSize();
    
    srand((unsigned int)time(NULL));
    int rand_x = rand() % ((int)winSize.width - 30) + 15;
    int rand_y = rand() % ((int)winSize.height - 80) + 60;
    
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
        if(isHitCCSprite(dumbbell->m_plateR, (*itr)->getPosition())) {
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
        else if (isHitCCSprite(dumbbell->m_plateL, (*itr)->getPosition())) {
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

        
        //障害物とダンベルかさなっているか
        if(isHitCCSprite(dumbbell->m_plateR, (*itr)->getPosition())) {
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
        else if (isHitCCSprite(dumbbell->m_plateL, (*itr)->getPosition())) {
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

bool BlockManager::isHitCCSprite(Sprite* sprite, Point glPoint)
{
    // 変換前のスプライトの矩形を求める
    Size size = sprite->getContentSize();
    
    Point v[4] = {
        Vec2(0,0),
        Vec2(0, size.height),
        Vec2(size.width, size.height),
        Vec2(size.width, 0),
    };
    
    // 矩形をワールド座標に変換する
    AffineTransform affine = sprite->nodeToWorldTransform();
    
    for( int i=0; i<4; i++ ) {
        v[i] = PointApplyAffineTransform(v[i], affine);
    }
    
    // 外積判定用のベクトルを求める
    Point vec[4] = {
        v[1] - v[0],
        v[2] - v[1],
        v[3] - v[2],
        v[0] - v[3],
    };
    
    Point vecP[4] = {
        v[0] - glPoint,
        v[1] - glPoint,
        v[2] - glPoint,
        v[3] - glPoint,
    };
    
    // 外積計算 求めた外積の向きが揃っていれば点は内包されている
    // （この例の場合は正方向に揃っていれば内包されている）
    for( int i=0; i<4; i++ ) {
        if( (vec[i].x * vecP[i].y - vec[i].y * vecP[i].x) < 0 ) {
            return false;
        }
    }
    
    return true;
}