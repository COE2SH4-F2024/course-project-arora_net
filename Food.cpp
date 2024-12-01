#include "food.h"
#include <stdlib.h>

using namespace std;


Food::Food()
{
    //start out of bounds 
    //foodpos = objPos(400,400,'@');
    foodbucket = new objPosArrayList;

}

// Destructor - clean up dynamic memory
Food::~Food()
{
    delete foodbucket;
}

void Food::generateFood(objPosArrayList *blockOff)
{
    int x_max = 29;
    int y_max = 12; 
    bool generated = false;

    int NormalFood = 0; // holds how many succesful 'normal' food objects were generated
    int SpecialFood1 = 0; // holds how many succesful 'special' food objects were generated (increase score by 10)
    int SpecialFood2 = 0; // holds how many succesful 'special' food objects were generated (increase score by 50 and snake length by 10)

    // generates 3 normal foods
    while(NormalFood < 3)
    {
        //generates random coords
        int rand_x = 1 + rand() % (x_max - 1);;
        int rand_y = rand() % y_max;
        
        //make new object to test if pos is equal
        const objPos random_pos(rand_x,rand_y,'*');

        bool overlap = false;
        //check if new food overlaps with any player objects 
        for(int i = 0; i < blockOff->getSize(); i++)
        {
            objPos current_seg = blockOff->getElement(i);

            if(current_seg.isPosEqual(&random_pos))
            {
                overlap = true;
            } 
        }
        //check if new food overlaps with any other food
        for (int j = 0; j < foodbucket->getSize(); j++) 
        {
            objPos overlapfood = foodbucket->getElement(j);
            if (random_pos.isPosEqual(&overlapfood)) {
                overlap = true;
                break;
            }
        }
        //insert food into the the food list if there is no overlap
        if(!overlap)
        {
            objPos tempfood(rand_x,rand_y,'@');
            foodbucket->insertHead(tempfood);
            NormalFood ++;
            

        }
    }
    generated = false;
    
    //genreates 2 special foods (same logic as above just with different symbol)
    while(SpecialFood1 < 1)
    {
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
        for (int j = 0; j < foodbucket->getSize(); j++) 
        {
            objPos overlapfood = foodbucket->getElement(j);
            if (random_pos.isPosEqual(&overlapfood)) {
                overlap = true;
                break;
            }
        }
        if(!overlap)
        {
            objPos tempfood(rand_x,rand_y,'$');
            foodbucket->insertHead(tempfood);
            SpecialFood1++;
            generated = true;

        }
    }
    while(SpecialFood2 < 1)
    {
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
        for (int j = 0; j < foodbucket->getSize(); j++) 
        {
            objPos overlapfood = foodbucket->getElement(j);
            if (random_pos.isPosEqual(&overlapfood)) {
                overlap = true;
                break;
            }
        }
        if(!overlap)
        {
            objPos tempfood(rand_x,rand_y,'!');
            foodbucket->insertHead(tempfood);
            SpecialFood2++;
            generated = true;

        }
    }
}

objPosArrayList* Food::getFoodPos() const
{
    return foodbucket;
}

