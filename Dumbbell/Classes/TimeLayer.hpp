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
class TimeLayer : public Layer
{
public:
    virtual bool init();
    virtual void onEnter();
    CREATE_FUNC(TimeLayer);
    void setTime(float time);
public:
    Label* m_timeLabel;
    Sprite* m_timeSprite;
    int m_time;
};

#endif /* TimeLayer_hpp */
