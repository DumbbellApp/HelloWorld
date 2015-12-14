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
enum class BackGroundType;
class ScoreLayer : public Layer
{
public:
    virtual bool init();
    virtual void onEnter();
    CREATE_FUNC(ScoreLayer);
    void setScore(int score);
public:
    Label* m_scoreLabelSiro;
    Label* m_scoreLabelKuro;
    Sprite* m_scoreSpriteSiro;
    Sprite* m_scoreSpriteKuro;
    Sprite* m_scoreBack;
    Node* m_kuro;
    Node* m_siro;
    int m_score;
    BackGroundType m_backGroundType;
};

#endif /* ScoreLayer_hpp */
