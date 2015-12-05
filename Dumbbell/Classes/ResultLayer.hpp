//
//  ResultLayer.hpp
//  Dumbbell
//
//  Created by NakadaTakuya on 2015/12/06.
//
//

#ifndef ResultLayer_hpp
#define ResultLayer_hpp

USING_NS_CC;
class ResultLayer : public Layer
{
public:
    virtual bool init();
    virtual void onEnter();
    CREATE_FUNC(ResultLayer);
public:
    Sprite* m_resultSprite;
};

#endif /* ResultLayer_hpp */
