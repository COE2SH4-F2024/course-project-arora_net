#include <iostream>
#include <stdlib.h>
#include "MacUILib.h"
#include "objPos.h"

#include "GameMechs.h"
#include "Player.h"
#include "Food.h"
#include "objPosArrayList.h"

using namespace std;

// gloabl pointers 
GameMechs *mechanics;
Player *player_ptr;
Food *food;



#define DELAY_CONST 100000

//bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();
    MacUILib_printf("%d",mechanics->getExitFlagStatus());
    while(mechanics->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    //Initialise pointers on the heap
    mechanics = new GameMechs;
    food = new Food;
    player_ptr = new Player(mechanics,food);

    //seed the random generation
    srand(time(0));

    //generate random location for food
    food->generateFood(player_ptr->getPlayerPos());
}

void GetInput(void)
{
    //collect input from user (find this function in GameMechs class)
    mechanics->collectAsyncInput();
    
}

void RunLogic(void)
{
    //if input does not = 0 (null) colelct it 
    if(mechanics->getInput() != 0){
        player_ptr->updatePlayerDir();
        player_ptr->movePlayer();
    }else if(mechanics->getLastinput() != 0) // this holds a copy of the last input since the input is cleared 
    {                                        // after every loop
        player_ptr->updatePlayerDir();
        player_ptr->movePlayer();
    }
    //clear input 
    mechanics->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    int boardY = mechanics->getBoardSizeY();
    int boardX = mechanics->getBoardSizeX();
    //current player pos 
    objPosArrayList *temp = player_ptr->getPlayerPos();
    objPos temp_player = temp->getElement(0);

    int playerx = temp_player.pos->x;
    int playery = temp_player.pos->y;

    int score = mechanics->getScore();
    
    MacUILib_printf("CONTROLS\n");
    MacUILib_printf("UP: W\n");
    MacUILib_printf("DOWN: S\n");
    MacUILib_printf("LEFT: A\n");
    MacUILib_printf("RIGHT: D\n");
    MacUILib_printf("_____________________________________\n");
    MacUILib_printf("@ = 1 point\n");
    MacUILib_printf("$ = 10 points\n");
    MacUILib_printf("%s\n","##############################");

    for(int i = 0; i < boardY - 2; i++){
        for(int j = 0; j < boardX; j++){
            if(j == 0)
            {
                MacUILib_printf("%c",'#');
            }
            else if(j == 29)
            {
                MacUILib_printf("%c\n",'#');
            }
            
            else
            {   
                //count holds if a charcter was printed in the current iteration
                int count = 0;
                // temp temp for player list
                objPosArrayList *temp_list = player_ptr->getPlayerPos();
                for(int k = 0; k < player_ptr->getsizeoflist(); k++)
                {
                    //temp for current sigment of player list
                    objPos current_seg = temp_list->getElement(k);
                    if(current_seg.pos->x == j && current_seg.pos->y == i)
                    {
                       MacUILib_printf("%c",current_seg.getSymbol());
                       count++; 
                       break;
                    }
                }
                // temp for food list
                objPosArrayList *temp_food = food->getFoodPos();
                for(int z = 0; z < 5; z++)
                {
                    //temp for current food segment
                    objPos tempFood = temp_food->getElement(z);
                    if(tempFood.pos->x == j && tempFood.pos->y == i)
                    {
                       MacUILib_printf("%c",tempFood.getSymbol());
                       count++; 
                       break; 
                    }
                }
                //if no char printed, print a space
                if(!count){
                    MacUILib_printf("%c",' ');
                }
                
            }
        }
    }
    MacUILib_printf("%s\n","##############################");
    const char *direction = player_ptr->getPlayerDir();
    MacUILib_printf("DIRECTION: %s\n",direction);
    MacUILib_printf("SCORE: %d\n",score);

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    MacUILib_uninit();

    delete mechanics;
    delete player_ptr;
    delete food;
}
