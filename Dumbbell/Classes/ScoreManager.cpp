//
//  ScoreManager.cpp
//  Dumbbell
//
//  Created by NakadaTakuya on 2015/12/09.
//
//

#include "ScoreManager.hpp"
#include "Message.hpp"
#include "EventManager.hpp"

static ScoreManager *s_SharedScoreManager = nullptr;

ScoreManager* ScoreManager::getInstance()
{
    if (!s_SharedScoreManager)
    {
        s_SharedScoreManager = new (std::nothrow) ScoreManager();
        CCASSERT(s_SharedScoreManager, "FATAL: Not enough memory");
        s_SharedScoreManager->init();
    }
    
    return s_SharedScoreManager;
}

ScoreManager::ScoreManager()
{
}

bool ScoreManager::init(void)
{
    m_score = 0;
    
    EventManager::getInstance()->addEventLister<MSG_CHAGE_STATE>([this](EventCustom* event){
        auto msg = static_cast<MSG_CHAGE_STATE*>(event->getUserData());
        if (msg->getStete() == STATE::GAME) {
            m_score = 0;
        }
    });
    return true;
}

ScoreManager::~ScoreManager(void)
{
    s_SharedScoreManager = nullptr;
}

void ScoreManager::addScore(int score)
{
    m_score += score*100;
    
    MSG_CHAGE_SCORE scoreChageMsg(m_score);
    EventManager::getInstance()->dispatch(scoreChageMsg);
}