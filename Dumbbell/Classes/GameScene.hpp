//
//  GameScene.hpp
//  HelloWorld
//
//  Created by NakadaTakuya on 2015/11/22.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

USING_NS_CC;

class Dumbbell;
class BlockManager;
class DumbbellController;
class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    void update(float delta);
    
    int calcCollisionObstacleBlock();
    int calcCollisionScoreBlock();
    
public:
    Dumbbell* m_dumbbell;
    DumbbellController* m_dumbbellcontroller;
    BlockManager* m_blockManager;
    double m_rotationRate;
    
    int m_score;
    int m_hitPoint;
    float m_leaveTime;
    float m_playTime;
    
    Label* m_scoreLabel;
    Label* m_leaveTimeLabel;
    
    Label* m_scoreHeaderLabel;
    Label* m_leaveTimeHeaderLabel;
};

#endif /* GameScene_hpp */
