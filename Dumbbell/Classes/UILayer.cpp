//
//  UILayer.cpp
//  Dumbbell
//
//  Created by NakadaTakuya on 2015/12/05.
//
//

#include "UILayer.hpp"

#include "TitleLayer.hpp"
#include "ScoreLayer.hpp"
#include "TimeLayer.hpp"
#include "ResultLayer.hpp"

using namespace std;
bool UILayer::init() {
    if (!Layer::init()) {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    m_titleLayer = TitleLayer::create();
    addChild(m_titleLayer,100);
    
    // ラベル類
    m_scoreLayer = ScoreLayer::create();
    addChild(m_scoreLayer);
    
//    m_timeLayer = TimeLayer::create();
//    addChild(m_timeLayer);
    
    m_resultLayer = ResultLayer::create();
    addChild(m_resultLayer);
    
    return true;
}