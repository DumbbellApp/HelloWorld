//
//  ScoreLayer.hpp
//  Dumbbell
//
//  Created by NakadaTakuya on 2015/12/04.
//
//

#ifndef ScoreLayer_hpp
#define ScoreLayer_hpp
USING_NS_CC;
class ScoreLayer : public Layer
{
public:
    virtual bool init();
    virtual void onEnter();
    CREATE_FUNC(ScoreLayer);
    void setScore(int score);
public:
    Label* m_scoreLabel;
    Sprite* m_scoreSprite;
    int m_score;
};

#endif /* ScoreLayer_hpp */
