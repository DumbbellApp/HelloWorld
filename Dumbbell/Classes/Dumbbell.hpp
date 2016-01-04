//
//  Dumbbell.hpp
//  HelloWorld
//
//  Created by NakadaTakuya on 2015/11/22.
//
//

#ifndef Dumbbell_hpp
#define Dumbbell_hpp

USING_NS_CC;

class Dumbbell : public Node
{
public:
    virtual bool init();
    CREATE_FUNC(Dumbbell);
    void addRotation(float rotationRate, float delta);
    void move(float delta);

    CC_SYNTHESIZE(double, m_rotationSpeed, RotationSpeed);
    CC_SYNTHESIZE(double, m_moveSpeed, MoveSpeed);

public:
    Sprite* m_plateR;
    Sprite* m_plateL;
    double m_preAnchorX;
    Vec2 m_moveDirection;
};



#endif /* Dumbbell_hpp */
