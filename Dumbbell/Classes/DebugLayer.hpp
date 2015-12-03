//
//  DebugLayer.hpp
//  Dumbbell
//
//  Created by NakadaTakuya on 2015/12/03.
//
//

#ifndef DebugLayer_hpp
#define DebugLayer_hpp
USING_NS_CC;

class Dumbbell;
class DumbbellController;
class BackGroundLayer;
class DebugLayer : public Layer
{
public:
    virtual bool init();
    CREATE_FUNC(DebugLayer);
    void update(float delta);
public:
    Dumbbell* m_dumbbell;
    DumbbellController* m_dumbbellController;
    BackGroundLayer* m_backGroundLayer;
    Menu* m_menu;
    Label* m_text1;
    Label* m_text2;
    Label* m_text3;
    Label* m_text4;
    bool m_isMove;
    bool m_isHorizonMove;
    
};

#endif /* DebugLayer_hpp */
