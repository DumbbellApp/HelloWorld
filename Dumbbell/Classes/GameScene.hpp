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

#include "GameStateType.h"

class Dumbbell;
class BlockManager;
class DumbbellController;
class UILayer;
class GameScene : public cocos2d::Layer
{
public:
    enum LAYER
    {
        LAYER_BACKGROUND = 1,
        LAYER_MAIN,
        LAYER_UI,
        LAYER_POPUP,
    };
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    virtual void onEnter();
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    void update(float delta);
    
    int calcCollisionObstacleBlock();
    int calcCollisionScoreBlock();
    
public:
    Dumbbell* m_dumbbell;
    DumbbellController* m_dumbbellcontroller;
    UILayer* m_uiLayer;
    BlockManager* m_blockManager;
    double m_rotationRate;
    
    int m_hitPoint;
    float m_leaveTime;
    float m_obstacleItv;
    float m_scoreBlockInv;
    
    Label* m_scoreLabel;
    Label* m_leaveTimeLabel;
    
    Label* m_scoreHeaderLabel;
    Label* m_leaveTimeHeaderLabel;
    
    STATE m_state;
};

#endif /* GameScene_hpp */
