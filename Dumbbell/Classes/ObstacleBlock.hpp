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
//    bool corisionCalc();
    
    Sprite* m_sprite;
    //    Rect m_rect;
    
    
    
    
};

#endif /* defined(ObstacleBlock_hpp) */
