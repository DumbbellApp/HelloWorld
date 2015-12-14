//
//  Obstacle.cpp
//
//
//  Created by Ren Awagakubo on 2015/11/29.
//
//

#include "ObstacleBlock.hpp"

ObstacleBlock::ObstacleBlock()
:m_moveSpeed(0)
{
    
}

bool ObstacleBlock::init(){
    if(!Sprite::init()) {
        return false;
    }
    
    //spriteで生成
    auto obstacle = Sprite::create("obstacle_block.png");
    obstacle->setAnchorPoint(Point(0.5,0.5));
    obstacle->setScale(0.7);
    obstacle->setPosition(Vec2());
    addChild(obstacle);
    
    //spriteで生成
    auto obstacleAlpha = Sprite::create("obstacle_block_alpha.png");
    obstacleAlpha->setAnchorPoint(Point(0,0));
    BlendFunc blend;
    blend.src = GL_SRC_ALPHA;
    blend.dst = GL_ONE;
    obstacleAlpha->setBlendFunc(blend);
    obstacle->addChild(obstacleAlpha);
    
    return true;
}

void ObstacleBlock::move(){
    auto move = MoveBy::create(0.1, Vec2(0, -m_moveSpeed));
    
    runAction(move);
}

void ObstacleBlock::setMoveSpeed(float speed)
{
    m_moveSpeed = speed;
}