//
//  TitleLayer.hpp
//  Dumbbell
//
//  Created by NakadaTakuya on 2015/12/05.
//
//

#ifndef TitleLayer_hpp
#define TitleLayer_hpp

USING_NS_CC;
class TitleLayer : public Layer
{
public:
    virtual bool init();
    virtual void onEnter();
    CREATE_FUNC(TitleLayer);
    bool onTouchBegan(Touch *touch, Event *event);
public:
    Sprite* m_titleSprite;
    
};

#endif /* TitleLayer_hpp */
