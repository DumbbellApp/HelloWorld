//
//  GameScene.hpp
//  HelloWorld
//
//  Created by NakadaTakuya on 2015/11/22.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include "BlockManager.hpp"

USING_NS_CC;

#include "GameStateType.h"

class Dumbbell;
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
    
    bool isCreateDumbbellClone(Dumbbell* dumbbell);
    void createDumbbellclone(Dumbbell* dumbbell);
    bool isDeleteDumbbell(Dumbbell* dumbbell);
    void deleteDumbbell(std::vector<Dumbbell*>::iterator itr);
    
    ScoreBlock::BlockType changeBlockType();
    
public:
    std::vector<Dumbbell*> m_dumbbell;
    DumbbellController* m_dumbbellcontroller;
    UILayer* m_uiLayer;
    BlockManager* m_blockManager;
    double m_rotationRate;
    
    int m_hitPoint;
    float m_leaveTime;
    float m_obstacleItv;
    float m_scoreBlockItv;
    float m_changeScoreBlockItv;
    
    ScoreBlock::BlockType m_blockType;
    int m_createScoreBlockCnt;
    
    bool m_isCreateScoreBlock;
    
    Label* m_scoreLabel;
    Label* m_leaveTimeLabel;
    
    Label* m_scoreHeaderLabel;
    Label* m_leaveTimeHeaderLabel;
    
    STATE m_state;
    
    const float SCORE_LABEL_CORRECTION = 0.9372;
        
    const float CREATE_CLONE_LINE_X_L = Director::getInstance()->getWinSize().width * 0.2;
    const float CREATE_CLONE_LINE_X_R = Director::getInstance()->getWinSize().width * 0.8;
    const float CREATE_CLONE_LINE_Y_T = Director::getInstance()->getWinSize().height * SCORE_LABEL_CORRECTION * 0.8;
    const float CREATE_CLONE_LINE_Y_B = Director::getInstance()->getWinSize().height * SCORE_LABEL_CORRECTION * 0.2;
    
    const float DELETE_D_LINE_X_L = CREATE_CLONE_LINE_X_R - Director::getInstance()->getWinSize().width;
    const float DELETE_D_LINE_X_R = CREATE_CLONE_LINE_X_L + Director::getInstance()->getWinSize().width;
    const float DELETE_D_LINE_Y_T = CREATE_CLONE_LINE_Y_B + Director::getInstance()->getWinSize().height * SCORE_LABEL_CORRECTION;
    const float DELETE_D_LINE_Y_B = CREATE_CLONE_LINE_Y_T - Director::getInstance()->getWinSize().height * SCORE_LABEL_CORRECTION;
};

#endif /* GameScene_hpp */
