//
//  ScoreBlock.h
//  
//
//  Created by Ren Awagakubo on 2015/11/30.
//
//

#ifndef ScoreBlock_hpp
#define ScoreBlock_hpp

USING_NS_CC;

class ScoreBlock : public Sprite
{
public:
    
    enum class BlockType {
      LEFT,
      RIGHT,
      ANY
    };
    
    virtual ~ScoreBlock();
    
//    virtual bool init();
//    CREATE_FUNC(ScoreBlock);
    static ScoreBlock* createScoreBlock(BlockType blockType);
    
private:
    ScoreBlock();
    bool init(BlockType blockType);
    
    Sprite* m_sprite;
    BlockType m_blockType;
};

#endif /* defined(ScoreBlock_hpp) */
