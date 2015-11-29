//
//  ScoreBlock.h
//  
//
//  Created by Ren Awagakubo on 2015/11/30.
//
//

#ifndef ScoreBlock_hpp
#define ScoreBlock_hpp

USING_NS_CC;

class ScoreBlock : public Sprite
{
public:
    virtual bool init();
    CREATE_FUNC(ScoreBlock);
    
//    bool corisionCalc();
    
    Sprite* m_sprite;
    //    Rect m_rect;
    
};

#endif /* defined(ScoreBlock_hpp) */
