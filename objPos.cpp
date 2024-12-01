#include "objPos.h"

objPos::objPos()
{
    pos = new Pos; // Allocate memory for position
    pos->x = 0;
    pos->y = 0;
    symbol = 0; // Set symbol to NULL character
}

//initializes with specific position and symbol
objPos::objPos(int xPos, int yPos, char sym)
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym; // Set symbol to provided character
}

// Respect the rule of six / minimum four
// [TODO] Implement the missing special member functions to meet the minimum four rule

// Copy constructor
objPos::objPos(const objPos &obj)
{
    pos = new Pos; // allocate new memory not shared with the original
    pos->x = obj. pos->x;
    pos->y = obj. pos->y;
    symbol = obj. symbol;
    
}
objPos& objPos::operator= (const objPos &obj)
{
    if(this != &obj)
    {
        this->pos->x = obj. pos->x;
        this->pos->y = obj. pos->y;
        this->symbol = obj. symbol;
    }

    return *this;
}

objPos::~objPos()
{
    delete pos;  // Free Pos
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

// checks if this object's position matches another object's position
// used for collision detection
bool objPos::isPosEqual(const objPos* refPos) const
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

// If positions match returns object's symbol
char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if(isPosEqual(refPos))
        return symbol;
    else
        return 0;
}

