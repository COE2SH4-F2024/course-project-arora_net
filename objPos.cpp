#include "objPos.h"

objPos::objPos()
{
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0; //NULL
}

objPos::objPos(int xPos, int yPos, char sym)
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Respect the rule of six / minimum four
// [TODO] Implement the missing special member functions to meet the minimum four rule
objPos::objPos(const objPos &obj)
{
    pos = new Pos{obj.pos->x,obj.pos->y};
    symbol = obj.symbol;
    
}
objPos& objPos::operator= (const objPos &obj)
{
    if(this != &obj)
    {
        pos = new Pos{obj.pos->x,obj.pos->y};
        symbol = obj.symbol;
    }

    return *this;
}

objPos::~objPos()
{
    delete pos;
}



void objPos::setObjPos(objPos o)
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

objPos objPos::getObjPos() const
{
    objPos returnPos;
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;
    
    return returnPos;
}

char objPos::getSymbol() const
{
    return symbol;
}

bool objPos::isPosEqual(const objPos* refPos) const
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if(isPosEqual(refPos))
        return symbol;
    else
        return 0;
}

int objPos::getPosx()
{
    return pos->x;
}

int objPos::getPosy()
{
    return pos->y;
}

void objPos::setPosx(int _x)
{
    pos->x = _x;
}
void objPos::setPosy(int _y)
{
    pos->y = _y;
}

void objPos::incrementX()
{
    pos->x = getPosx() + 1;
}
void objPos::incrementY()
{
    pos->y = getPosy() + 1;
}
void objPos::DecrementX()
{
    pos->x = getPosx() - 1;
}
void objPos::DecrementY()
{
    pos->y = getPosy() - 1;
}

void objPos::setX(int _x)
{
    pos->x = _x;
}

void objPos::setY(int _y)
{
    pos->y = _y;
}