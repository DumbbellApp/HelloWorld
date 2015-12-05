//
//  EventManager.hpp
//  Dumbbell
//
//  Created by NakadaTakuya on 2015/12/05.
//
//

#ifndef EventManager_hpp
#define EventManager_hpp

USING_NS_CC;
class EventManager : public Ref
{
public:
    static EventManager* getInstance();
    
public:
    template <typename T>
    void addEventLister(std::function<void(EventCustom* evt)> callback)
    {
        auto dispatcher =  Director::getInstance()->getEventDispatcher();
        dispatcher->addCustomEventListener(T::id, callback);
    }
    
    template <typename T>
    void dispatch(T msg)
    {
        auto dispatcher =  Director::getInstance()->getEventDispatcher();
        auto evt = EventCustom(msg.id);
        evt.setUserData(&msg);
        dispatcher->dispatchEvent(&evt);
    }
private:
    EventManager();
    virtual ~EventManager();
    virtual bool init();
};
#endif /* EventManager_hpp */
