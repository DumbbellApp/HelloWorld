//
//  DumbbellController.hpp
//  Dumbbell
//
//  Created by NakadaTakuya on 2015/12/01.
//
//

#ifndef DumbbellController_hpp
#define DumbbellController_hpp


USING_NS_CC;

class DumbbellController : public Node
{
public:
    virtual bool init();
    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchMoved(Touch *touch, Event *event);
    CREATE_FUNC(DumbbellController);
public:
    Sprite* m_controlArea;
    Sprite* m_controller;
};

#endif /* DumbbellController_hpp */
