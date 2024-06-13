#ifndef HP_h
#define HP_h

#include "Object.h"

class HP: public Object
{
public:
    HP(int x_, int y_);
    bool move1();
    friend void update();
};

#endif
