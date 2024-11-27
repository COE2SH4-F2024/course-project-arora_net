#include "food.h"
#include <stdlib.h>

using namespace std;


Food::Food()
{
    //start out of bounds 
    foodpos = objPos(400,400,'@');
}
Food::~Food()
{

}

void Food::generateFood(objPosArrayList *blockOff)
{
    int x_max = 29;
    int y_max = 12; 
    bool generated = false;

    while(!generated){

        int rand_x = 1 + rand() % (x_max - 1);;
        int rand_y = rand() % y_max;
        
        //make new object to test if pos is equal
        const objPos random_pos(rand_x,rand_y,'*');

        bool overlap = false;
        for(int i = 0; i < blockOff->getSize(); i++)
        {
            objPos current_seg = blockOff->getElement(i);

            if(current_seg.isPosEqual(&random_pos))
            {
                overlap = true;
            } 
        }
        if(!overlap)
        {
            foodpos.setPosx(rand_x);
            foodpos.setPosy(rand_y);
            generated = true;

        }
    }
}
objPos Food::getFoodPos() const
{
    return foodpos;
}

int Food::getfoodx()
{
    return foodpos.getPosx();
}

int Food::getfoody()
{
    return foodpos.getPosy();
}

char Food::getsymbol()
{
    return foodpos.getSymbol();
}