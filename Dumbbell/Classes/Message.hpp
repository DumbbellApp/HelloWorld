//
//  Message.hpp
//  Dumbbell
//
//  Created by NakadaTakuya on 2015/12/05.
//
//

#ifndef Message_hpp
#define Message_hpp

#include "GameStateType.h"
using namespace std;

//Stateが変更された時のメッセージ
class MSG_CHAGE_STATE
{
public:
    MSG_CHAGE_STATE(STATE state)
    {
        m_state = state;
    }
    CC_SYNTHESIZE(STATE, m_state, Stete)
    static string id;
};

//スコアが変更された時のメッセージ
class MSG_CHAGE_SCORE
{
public:
    MSG_CHAGE_SCORE(int score)
    {
        m_score = score;
    }
    CC_SYNTHESIZE(int, m_score, Score)
    static string id;
};

//時間が変更した時のメッセージ
class MSG_CHAGE_TIME
{
public:
    MSG_CHAGE_TIME(int time)
    {
        m_time = time;
    }
    CC_SYNTHESIZE(int, m_time, Time)
    static string id;
};

//背景が変更した時のメッセージ
enum class BackGroundType;
class MSG_CHAGE_BACK
{
public:
    MSG_CHAGE_BACK(BackGroundType time)
    {
        m_backGroundType = time;
    }
    CC_SYNTHESIZE(BackGroundType, m_backGroundType, BGType)
    static string id;
};

class MSG_RESET_BACK
{
public:
    MSG_RESET_BACK()
    {
    }
    static string id;
};

#endif /* Message_hpp */
