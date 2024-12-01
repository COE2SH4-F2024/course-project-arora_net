#include <iostream>
#include <stdlib.h>
#include "MacUILib.h"
#include "objPos.h"

#include "GameMechs.h"
#include "Player.h"
#include "Food.h"
#include "objPosArrayList.h"

using namespace std;

// pointers to main game objects
GameMechs *mechanics; // points to a new GameMechs object in heap memory
Player *player_ptr;  
Food *food; 



#define DELAY_CONST 300000 // 0.3s delay

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
    //if input does not = 0 (null) collect it 
    if(mechanics->getInput() != 0){
        player_ptr->updatePlayerDir(); // update the direction based on new input
        player_ptr->movePlayer(); 
    }
    else if(mechanics->getLastinput() != 0){ // no new input
        player_ptr->updatePlayerDir(); // keep the same direction
        player_ptr->movePlayer();
    }
    mechanics->clearInput(); // clear the input buffer
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    // get boardsize
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
    MacUILib_printf("SPEED (1:Slow 2:Normal 3:Fast)\n");
    MacUILib_printf("_____________________________________\n");
    MacUILib_printf("\n@ = 1 point\n");
    MacUILib_printf("$ = 10 points\n");
    MacUILib_printf("%s\n","\n##############################");

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
                int count = 0; // track if something was already drew at this position

                // check if any part of the snake is at current position
                objPosArrayList *temp_list = player_ptr->getPlayerPos(); //temporarily hold the snake's position data while drawing
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
                
                // check if any food is at current position
                objPosArrayList *temp_food = food->getFoodPos(); // temporarily hold the food positions while drawing
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
                // if nothing, draw empty space
                if(!count){
                    MacUILib_printf("%c",' ');
                }
                
            }
        }
    }
    MacUILib_printf("%s\n","##############################");
    const char *direction = player_ptr->getPlayerDir();
    MacUILib_printf("\nDIRECTION: %s\n",direction);
    MacUILib_printf("CURRENT SPEED: %d\n", mechanics->getGameSpeed());
    MacUILib_printf("SCORE: %d\n",score);

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST / mechanics->getGameSpeed()); 
    // Speed 1: 400000 / 1 = 400000 microseconds (0.4 seconds, slowest)
    // Speed 2: 400000 / 2 = 200000 microseconds (0.2 seconds, normal)
    // Speed 3: 400000 / 3 = 133333 microseconds (0.13 seconds, fastest)
}


void CleanUp(void)
{
    //MacUILib_clearScreen(); 

    if(mechanics->getLoseFlagStatus() == true)
    {
        MacUILib_printf("\nTHANK YOU FOR PLAYING\n");
        MacUILib_printf("YOUR SCORE WAS: %d\n",mechanics->getScore());

    }else{
        MacUILib_printf("\nYOU QUIT, PLAY AGAIN SOON\n");
    } 

    MacUILib_uninit();

    // free memory allocations
    delete mechanics;
    delete player_ptr;
    delete food;
}
