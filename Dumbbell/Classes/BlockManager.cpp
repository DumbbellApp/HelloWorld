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
    
    m_frameCnt = 0;
    
    auto winSize = Director::getInstance()->getWinSize();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("hit_obstacle.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("get_score.mp3");
    
    m_scoreBlockPos = Node::create();
    m_scoreBlockPos->setAnchorPoint(Point(0.5, 0.5));
    m_scoreBlockPos->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
    addChild(m_scoreBlockPos);
    srand((unsigned int)time(NULL));
    int anglePattern = rand() % 8;
    m_lastTimeAnglePattern = anglePattern;
    
    m_moveType = MoveType::CIRCLE;
    
    this->scheduleUpdate();
    return true;
}

void BlockManager::resetBlocks()
{
    for (auto itr = m_obstacles.begin(); itr != m_obstacles.end(); ) {
        (*itr)->removeFromParent();
        m_obstacles.erase(itr);
        continue;
    }
    
    for (auto itr = m_scoreBlock.begin(); itr != m_scoreBlock.end(); ) {
        (*itr)->removeFromParent();
        m_scoreBlock.erase(itr);
        continue;
    }
    
}

void BlockManager::update(float dt)
{
    move();
    
    m_frameCnt++;
    
    if (m_frameCnt % 10 == 0) {
        moveScoreBlockPos();
    }
    
    deleteScoreBlock();
//    calcCollision();
 
}

void BlockManager::createObstacleBlock()
{
    auto winSize = Director::getInstance()->getWinSize();
    
    srand((unsigned int)time(NULL));
    int rand_x = rand() % (int)winSize.width * 0.9 + (int)winSize.width * 0.05;
    float speed = (float)(rand() % 4 + 2) * 2;
    
    //spriteで生成
    auto obstacle = ObstacleBlock::create();
    obstacle->setPosition(Vec2(rand_x, winSize.height + 30));
    obstacle->setMoveSpeed(speed);
    addChild(obstacle);
    m_obstacles.push_back(obstacle);
}

void BlockManager::createScoreBlock(ScoreBlock::BlockType blockType)
{
    
    //spriteで生成
    auto scoreBlock = ScoreBlock::createScoreBlock(blockType);
    scoreBlock->setPosition(m_scoreBlockPos->getPosition());
    addChild(scoreBlock);
    m_scoreBlock.push_back(scoreBlock);
}

void BlockManager::deleteScoreBlock()
{
    for (auto itr = m_scoreBlock.begin(); itr != m_scoreBlock.end(); ) {
        if ((*itr)->isDelete()) {
            (*itr)->removeFromParent();
            m_scoreBlock.erase(itr);
            continue;
        }
        itr++;
    }
}

void BlockManager::move()
{
    for (auto itr : m_obstacles) {
        itr->move();
    }
}

void BlockManager::moveScoreBlockPos()
{
//    auto act = getActionByTag(1);
//    if (act) {
//        m_scoreBlockPos->stopActionByTag(1);
//    }
    
    auto winSize = Director::getInstance()->getWinSize();
    Vec2 nextPosDist = Vec2(winSize.width / 2, winSize.height / 2);
    
    switch (m_moveType) {
        case MoveType::RANDOM:
        {
            //前進んだ方向から180度の範囲で進行方向を決定（現在45度区切り）
            srand((unsigned int)time(NULL));
            int anglePattern = m_lastTimeAnglePattern + (rand() % 3 - 1);
            
            if (anglePattern < 0) {
                anglePattern += 8;
            }
            else if (anglePattern > 7) {
                anglePattern -= 8;
            }
            
            double angle = 45 * anglePattern;
            double rad = angle / 180 * M_PI;
            m_lastTimeAnglePattern = anglePattern;
            
            nextPosDist = Vec2(40*cos(rad), 40*sin(rad));
            
            //画面外に行きそうになったら
            if (m_scoreBlockPos->getPositionX() + nextPosDist.x < winSize.width * 0.05) {
                m_scoreBlockPos->setPositionX(winSize.width * 0.95);
            }
            else if (m_scoreBlockPos->getPositionX() + nextPosDist.x > winSize.width * 0.95) {
                m_scoreBlockPos->setPositionX(winSize.width * 0.05);
            }
            if (m_scoreBlockPos->getPositionY() + nextPosDist.y < winSize.height * 0.1) {
                m_scoreBlockPos->setPositionY(winSize.height * 0.9);
            }
            else if (m_scoreBlockPos->getPositionY() + nextPosDist.y > winSize.height * 0.9) {
                m_scoreBlockPos->setPositionY(winSize.height * 0.1);
            }
            
            auto moveBy = MoveBy::create(1.0, nextPosDist);
            //    moveBy->setTag(1);
            
            m_scoreBlockPos->runAction(moveBy);
            break;
        }
        case MoveType::LINE:
        {
            int anglePattern = m_lastTimeAnglePattern;
            
            
            if (anglePattern < 0) {
                anglePattern += 8;
            }
            else if (anglePattern > 7) {
                anglePattern -= 8;
            }
            
            double angle = 45 * anglePattern;
            double rad = angle / 180 * M_PI;
            m_lastTimeAnglePattern = anglePattern;
            
            nextPosDist = Vec2(200*cos(rad), 200*sin(rad));
            
            auto moveBy = MoveBy::create(1.0, nextPosDist);

            //ラムダ式入れる
            auto callBack = CallFunc::create([this](){
                m_moveType = MoveType::RANDOM;
            });
            
            auto line = Sequence::create(moveBy, callBack, NULL);
            
            m_scoreBlockPos->runAction(line);
            break;
        }
        case MoveType::SQUARE:
        {
            std::vector<MoveBy *> moveBy;
            for (int i = 0; i < 4; i++){
                int anglePattern = m_lastTimeAnglePattern + 2;
                
                
                if (anglePattern < 0) {
                    anglePattern += 8;
                }
                else if (anglePattern > 7) {
                    anglePattern -= 8;
                }
                
                double angle = 45 * anglePattern;
                double rad = angle / 180 * M_PI;
                m_lastTimeAnglePattern = anglePattern;
                
                nextPosDist = Vec2(80*cos(rad), 80*sin(rad));
                
                moveBy.push_back(MoveBy::create(1.0, nextPosDist));
                
            }
            
            auto callBack = CallFunc::create([this](){
                m_moveType = MoveType::RANDOM;
            });
            
            auto square = Sequence::create(moveBy.at(0), moveBy.at(1), moveBy.at(2), moveBy.at(3), callBack, NULL);
            
            m_scoreBlockPos->runAction(square);
            
            moveBy.clear();
            break;
        }
        case MoveType::CIRCLE:
        {
            std::vector<MoveBy *> moveBy;
            for (int i = 0; i < 8; i++) {
            
                int anglePattern = m_lastTimeAnglePattern + 1;
                
                if (anglePattern < 0) {
                    anglePattern += 8;
                }
                else if (anglePattern > 7) {
                    anglePattern -= 8;
                }
                
                double angle = 45 * anglePattern;
                double rad = angle / 180 * M_PI;
                m_lastTimeAnglePattern = anglePattern;
                
                nextPosDist = Vec2(40*cos(rad), 40*sin(rad));
                
            }
            
            auto callBack = CallFunc::create([this](){
                m_moveType = MoveType::RANDOM;
            });
            
            auto square = Sequence::create(moveBy.at(0), moveBy.at(1), moveBy.at(2), moveBy.at(3), moveBy.at(4),
                                           moveBy.at(5), moveBy.at(6), moveBy.at(7), callBack, NULL);
            
            m_scoreBlockPos->runAction(square);
            
            break;
        }
        default:
            break;
    }


}

int BlockManager::calcCollisionObstacleBlock(std::vector<Dumbbell*> dumbbell)
{
    int collisionCnt = 0;
    
    for (auto dum : dumbbell) {
        for (auto itr = m_obstacles.begin(); itr != m_obstacles.end(); ) {
            //pImg1とpImg2の表示領域を取得
            Rect rect = (*itr)->boundingBox();
            
            //障害物とダンベルかさなっているか
            if(isHitCCSprite(dum->m_plateR, (*itr)->getPosition())) {
                ParticleSystemQuad* particle = ParticleSystemQuad::create("particle_texture_2.plist");
                particle->setPosition((*itr)->getPosition());
                particle->setAutoRemoveOnFinish(true);
                addChild(particle);
                
                collisionCnt++;
                (*itr)->removeFromParent();
                m_obstacles.erase(itr);
                
                //音楽を再生する
                //
                int soundID;
                soundID = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("hit_obstacle.mp3");
                log("障害物に衝突");
                continue;
            }
            else if (isHitCCSprite(dum->m_plateL, (*itr)->getPosition())) {
                ParticleSystemQuad* particle = ParticleSystemQuad::create("particle_texture_2.plist");
                particle->setPosition((*itr)->getPosition());
                particle->setAutoRemoveOnFinish(true);
                addChild(particle);
                
                collisionCnt++;
                (*itr)->removeFromParent();
                m_obstacles.erase(itr);
                
                //音楽を再生する
                //
                int soundID;
                soundID = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("hit_obstacle.mp3");
                log("障害物に衝突");
                continue;
            }
            itr++;
            
        }
    }
    
    return collisionCnt;
}

int BlockManager::calcCollisionScoreBlock(std::vector<Dumbbell*> dumbbell)
{
    int collisionCnt = 0;
    
    for (auto dum : dumbbell) {
        for (auto itr = m_scoreBlock.begin(); itr != m_scoreBlock.end(); ) {

            
            //スコアブロックとダンベルかさなっているか
            if(isHitCCSprite(dum->m_plateR, (*itr)->getPosition())) {

                if ((*itr)->getBlockType() != ScoreBlock::BlockType::LEFT) {
                    ParticleSystemQuad* particle = ParticleSystemQuad::create("particle_texture.plist");
                    particle->setPosition((*itr)->getPosition());
                    particle->setAutoRemoveOnFinish(true);
                    addChild(particle);
                    
                    collisionCnt++;
                    
                    (*itr)->removeFromParent();
                    m_scoreBlock.erase(itr);
                    
                    //音楽を再生する
                    //
                    int soundID;
                    soundID = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("get_score.mp3");
                    log("スコアブロック獲得");
                    continue;
                }
            }
            else if (isHitCCSprite(dum->m_plateL, (*itr)->getPosition())) {
                
                if ((*itr)->getBlockType() != ScoreBlock::BlockType::RIGHT) {
                    ParticleSystemQuad* particle = ParticleSystemQuad::create("particle_texture.plist");
                    particle->setPosition((*itr)->getPosition());
                    particle->setAutoRemoveOnFinish(true);
                    addChild(particle);
                    
                    collisionCnt++;
                    
                    (*itr)->removeFromParent();
                    m_scoreBlock.erase(itr);
                    
                    //音楽を再生する
                    //
                    int soundID;
                    soundID = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("get_score.mp3");
                    log("スコアブロック獲得");
                    continue;
                }
            }
            itr++;
            
        }
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