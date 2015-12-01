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
    CREATE_FUNC(DumbbellController);
public:
    Sprite* m_controlArea;
};

#endif /* DumbbellController_hpp */
