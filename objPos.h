#ifndef OBJPOS_H
#define OBJPOS_H

// Not really a C++ thing
typedef struct 
{
    int x;
    int y;
} Pos;

class objPos
{
    public:
        Pos* pos;        
        char symbol;

        objPos();
        objPos(int xPos, int yPos, char sym);
        
        // Respect the rule of six / minimum four
        // [TODO] Implement the missing special member functions to meet the minimum four rule
        ~objPos();
        objPos(const objPos &obj);
        objPos& operator= (const objPos &obj);
        
        void setObjPos(objPos o);        
        void setObjPos(int xPos, int yPos, char sym);  

        objPos getObjPos() const;
        char getSymbol() const;
        char getSymbolIfPosEqual(const objPos* refPos) const;
        
        bool isPosEqual(const objPos* refPos) const;

        int getPosx();
        int getPosy();
        void setPosx(int _x);
        void setPosy(int _y);

        void incrementX();
        void incrementY();
        void DecrementX();
        void DecrementY();

        void setX(int _x);
        void setY(int _y);
};

#endif