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
    virtual void onEnter();
    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchMoved(Touch *touch, Event *event);
    CREATE_FUNC(DumbbellController);
    double getRotationRate();
private:
    Node* m_controlNode;
    Sprite* m_controlArea;
    Sprite* m_controller;
    Sprite* m_controllerAlpha;
    Node* m_touchArea;
    bool isEnable;
};

#endif /* DumbbellController_hpp */
