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

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    void update(float delta);
    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchMoved(Touch *touch, Event *event);
    
    float calRotationRate(Touch* touch);
public:
    Dumbbell* m_dumbbell;
    Sprite* sprite;
    double m_rotationRate;
    
#ifdef COCOS2D_DEBUG
    Label* m_text1;
    Label* m_text2;
    Label* m_text3;
    Label* m_text4;
    bool m_isMove;
    bool m_isHorizonMove;
#endif
};

#endif /* GameScene_hpp */
