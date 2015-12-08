//
//  ScoreManager.hpp
//  Dumbbell
//
//  Created by NakadaTakuya on 2015/12/09.
//
//

#ifndef ScoreManager_hpp
#define ScoreManager_hpp

USING_NS_CC;
class ScoreManager : public Ref
{
public:
    static ScoreManager* getInstance();
    void addScore(int socre);
private:
    ScoreManager();
    virtual ~ScoreManager();
    virtual bool init();

public:
    
    CC_SYNTHESIZE_READONLY(int, m_score, Score);

};
#endif /* ScoreManager_hpp */
