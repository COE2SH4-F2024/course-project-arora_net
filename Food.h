#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "objPosArrayList.h"


class Food
{
    private:
        objPos foodpos;
    public:
        Food();
        ~Food();

        void generateFood(objPosArrayList *blockOff);
        objPos getFoodPos() const;

        //added member functions 
        int getfoodx();
        int getfoody();
        char getsymbol();
};

#endif