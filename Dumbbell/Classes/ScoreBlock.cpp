//
//  ScoreBlock.cpp
//  
//
//  Created by Ren Awagakubo on 2015/11/30.
//
//

#include "ScoreBlock.hpp"

bool ScoreBlock::init(){
    if(!Sprite::init()) {
        return false;
    }
    
    //spriteで生成
    auto scoreBlock = Sprite::create("score_block.png");
    scoreBlock->setAnchorPoint(Point(0.5,0.5));
    scoreBlock->setScale(0.02);
    addChild(scoreBlock);
    
    return true;
}

