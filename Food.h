#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"


class Food
{
    private:
        objPos foodpos;
    public:
        Food();
        ~Food();

        void generateFood(objPos blockOff);
        objPos getFoodPos() const;
        int getfoodx();
        int getfoody();
        char getsymbol();
};

#endif