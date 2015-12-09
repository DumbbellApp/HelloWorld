//
//  BackGroundLayer.hpp
//  Dumbbell
//
//  Created by NakadaTakuya on 2015/12/04.
//
//

#ifndef BackGroundLayer_hpp
#define BackGroundLayer_hpp

enum class BackGroundType;
USING_NS_CC;
class BackGroundLayer : public Layer
{
public:
    enum LAYER
    {
        LAYER_NEXT = 1,
        LAYER_NOW,
    };
public:
    virtual bool init();
    virtual void onEnter();
    CREATE_FUNC(BackGroundLayer);
    void chageBackGround(BackGroundType type);
public:
    Sprite* m_nowBackGroundSprite;
    Sprite* m_nextBackGroundSprite;
private:
    bool m_isFading;
};

#endif /* BackGroundLayer_hpp */
