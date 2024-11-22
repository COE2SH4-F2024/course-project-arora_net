#include "food.h"
#include <stdlib.h>

using namespace std;


Food::Food()
{
    foodpos = objPos(400,400,'@');
}
Food::~Food()
{

}

void Food::generateFood(objPos blockOff)
{
    int x_max = 29;
    int y_max = 12; 
    bool generated = false;

    while(!generated){

        int rand_x = 1 + rand() % (x_max - 1);;
        int rand_y = rand() % y_max;
        
        //make new object to test if pos is equal
        const objPos random_pos(rand_x,rand_y,'*');


        if(!blockOff.isPosEqual(&random_pos)){
            foodpos.setPosx(rand_x);
            foodpos.setPosy(rand_y);
            generated = true;
        }
    }
}
objPos Food::getFoodPos() const
{
    return(foodpos.getObjPos());
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