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
    bool isCreateScoreBlock();
    void move();
    void moveScoreBlockPos();
    int calcCollisionObstacleBlock(std::vector<Dumbbell*> dumbbell);
    int calcCollisionScoreBlock(std::vector<Dumbbell*> dumbbell);
    
    void resetBlocks();

    bool isHitCCSprite(Sprite* sprite, Point glPoint);
    
    std::vector<ObstacleBlock*> m_obstacles;
    std::vector<ScoreBlock*> m_scoreBlock;
    
    enum class MoveType{
        RANDOM,
        LINE,
        SQUARE,
        CIRCLE
    };
    
private:
    Node* m_scoreBlockPos;
    int m_lastTimeAnglePattern;
    int m_frameCnt;
    MoveType m_moveType;
    ScoreBlock::BlockType m_blockType;
    
    void deleteScoreBlock();
    
    
};

#endif /* defined(BlockManager) */
