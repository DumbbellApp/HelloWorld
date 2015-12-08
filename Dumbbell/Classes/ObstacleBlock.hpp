//
//  Obstacle.h
//  
//
//  Created by Ren Awagakubo on 2015/11/29.
//
//

#ifndef ObstacleBlock_hpp
#define ObstacleBlock_hpp

USING_NS_CC;

class ObstacleBlock : public Sprite
{
public:
    virtual bool init();
    CREATE_FUNC(ObstacleBlock);
    
    void move();
    void setMoveSpeed(float speed);
    
    Sprite* m_sprite;
    float m_moveSpeed;
    
private:
    ObstacleBlock();
};

#endif /* defined(ObstacleBlock_hpp) */
