//
//  UILayer.hpp
//  Dumbbell
//
//  Created by NakadaTakuya on 2015/12/05.
//
//

#ifndef UILayer_hpp
#define UILayer_hpp
class ScoreLayer;
class TimeLayer;
class TitleLayer;
USING_NS_CC;
class UILayer : public Layer
{
public:
    virtual bool init();
    CREATE_FUNC(UILayer);
public:
    ScoreLayer* m_scoreLayer;
    TimeLayer* m_timeLayer;
    TitleLayer* m_titleLayer;
};

#endif /* UILayer_hpp */
