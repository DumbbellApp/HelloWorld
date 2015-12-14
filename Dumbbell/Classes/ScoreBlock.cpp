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
    auto scoreBlock = Sprite::create("score_block_any.png");
    scoreBlock->setAnchorPoint(Point(0.5,0.5));
    scoreBlock->setScale(0.5);
    addChild(scoreBlock);
    
    //spriteで生成
    auto scoreAlpha = Sprite::create("score_block_alpha.png");
    scoreAlpha->setAnchorPoint(Point(0,0));
    scoreAlpha->setScale(2);
    BlendFunc blend;
    blend.src = GL_SRC_ALPHA;
    blend.dst = GL_ONE;
    scoreAlpha->setBlendFunc(blend);
    scoreBlock->addChild(scoreAlpha);
    
    return true;
}

