//
//  Obstacles.hpp
//  
//
//  Created by Ren Awagakubo on 2015/11/29.
//
//

#ifndef BlockManager_hpp
#define BlockManager_hpp

class Dumbbell;
class ObstacleBlock;
class ScoreBlock;

USING_NS_CC;

class BlockManager : public Node
{
public:
    virtual bool init();
    CREATE_FUNC(BlockManager);
    
    void update(float dt);
    
    void createObstacleBlock();
    void createScoreBlock();
    void move();
    int calcCollisionObstacleBlock(Dumbbell* dumbbell);
    int calcCollisionScoreBlock(Dumbbell* dumbbell);
    
//    Sprite* m_sprite;
//    Rect m_rect;
    
    std::vector<ObstacleBlock*> m_obstacles;
    std::vector<ScoreBlock*> m_scoreBlock;

    
    
};

#endif /* defined(BlockManager) */
