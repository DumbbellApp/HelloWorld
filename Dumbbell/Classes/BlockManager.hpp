//
//  Obstacles.hpp
//  
//
//  Created by Ren Awagakubo on 2015/11/29.
//
//

#ifndef BlockManager_hpp
#define BlockManager_hpp

#include "ScoreBlock.hpp"

class Dumbbell;
class ObstacleBlock;

USING_NS_CC;

class BlockManager : public Node
{
public:
    virtual bool init();
    CREATE_FUNC(BlockManager);
    
    void update(float dt);
    
    void createObstacleBlock();
    void createScoreBlock(ScoreBlock::BlockType blockType);
    void move();
    void moveScoreBlockPos();
    int calcCollisionObstacleBlock(Dumbbell* dumbbell);
    int calcCollisionScoreBlock(Dumbbell* dumbbell);

    bool isHitCCSprite(Sprite* sprite, Point glPoint);
    
    std::vector<ObstacleBlock*> m_obstacles;
    std::vector<ScoreBlock*> m_scoreBlock;
    
private:
    Sprite* m_scoreBlockPos;
    int m_lastTimeAnglePattern;
    int m_frameCnt;
    
    
};

#endif /* defined(BlockManager) */
