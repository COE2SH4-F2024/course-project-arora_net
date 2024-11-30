#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "objPosArrayList.h"


class Food
{
    private:
       // objPos foodpos;
        objPosArrayList *foodbucket;
    public:
        Food();
        ~Food();

        void generateFood(objPosArrayList *blockOff);
        objPosArrayList *getFoodPos() const;

        //added member functions 
        
};

#endif