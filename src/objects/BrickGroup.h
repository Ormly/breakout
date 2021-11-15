#ifndef BREAKOUT_BRICKGROUP_H
#define BREAKOUT_BRICKGROUP_H

#include "Brick.h"

class BrickGroup
{
private:
    std::vector<Brick*> m_bricks;
public:
    BrickGroup(std::vector<Brick*> &bricks);
    GLboolean isPenetrated() const;
    GLboolean wasCleared() const;
    std::vector<Brick*> getBricks() const;
};


#endif //BREAKOUT_BRICKGROUP_H
