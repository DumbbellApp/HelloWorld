//
//  TimeLayer.hpp
//  Dumbbell
//
//  Created by NakadaTakuya on 2015/12/04.
//
//

#ifndef TimeLayer_hpp
#define TimeLayer_hpp

USING_NS_CC;
enum class BackGroundType;
class TimeLayer : public Layer
{
public:
    virtual bool init();
    virtual void onEnter();
    CREATE_FUNC(TimeLayer);
    void setTime(float time);
public:
    Label* m_timeLabelKuro;
    Label* m_timeLabelSiro;
    Sprite* m_timeSpriteKuro;
    Sprite* m_timeSpriteSiro;
    Node* m_kuro;
    Node* m_siro;
    int m_time;
    BackGroundType m_backGroundType;
};

#endif /* TimeLayer_hpp */
