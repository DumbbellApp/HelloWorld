//
//  BackGroundManager.hpp
//  Dumbbell
//
//  Created by NakadaTakuya on 2015/12/10.
//
//

#ifndef BackGroundManager_hpp
#define BackGroundManager_hpp

USING_NS_CC;
enum class BackGroundType;
class BackGroundManager : public Node
{
public:
    CREATE_FUNC(BackGroundManager);
    
private:
    virtual bool init();
    virtual void update(float delta);
    BackGroundType m_backGroundType;
    double m_time;
};

#endif /* BackGroundManager_hpp */
