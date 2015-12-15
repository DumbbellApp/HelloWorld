//
//  ScoreBlock.cpp
//  
//
//  Created by Ren Awagakubo on 2015/11/30.
//
//

#include "ScoreBlock.hpp"

ScoreBlock::ScoreBlock()
{
    
}

ScoreBlock::~ScoreBlock()
{
    
}

ScoreBlock* ScoreBlock::createScoreBlock(ScoreBlock::BlockType blockType)
{
    ScoreBlock *pRet = new(std::nothrow) ScoreBlock(); 
    if (pRet && pRet->init(blockType))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool ScoreBlock::init(BlockType blockType){
    if(!Sprite::init()) {
        return false;
    }
    
    Sprite* scoreBlock;
    
    if (blockType == BlockType::LEFT) {
        scoreBlock = Sprite::create("score_block_left.png");
        m_blockType = BlockType::LEFT;
    }
    else if (blockType == BlockType::RIGHT) {
        scoreBlock = Sprite::create("score_block_right.png");
        m_blockType = BlockType::RIGHT;
    }
    else if (blockType == BlockType::ANY) {
        scoreBlock = Sprite::create("score_block_any.png");
        m_blockType = BlockType::ANY;
    }
    //spriteで生成
    
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

