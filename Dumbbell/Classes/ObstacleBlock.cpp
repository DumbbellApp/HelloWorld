//
//  Obstacle.cpp
//
//
//  Created by Ren Awagakubo on 2015/11/29.
//
//

#include "ObstacleBlock.hpp"


bool ObstacleBlock::init(){
    if(!Sprite::init()) {
        return false;
    }
    
    //spriteで生成
    auto obstacle = Sprite::create("obstacle_block.png");
    obstacle->setAnchorPoint(Point(0.5,0.5));
    obstacle->setPosition(Vec2());
    addChild(obstacle);
    
    return true;
}

void ObstacleBlock::move(){
    auto move = MoveBy::create(0.1, Vec2(0, -0.5));
    
    runAction(move);
}
