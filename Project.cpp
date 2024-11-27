#include <iostream>
#include <stdlib.h>
#include "MacUILib.h"
#include "objPos.h"

#include "GameMechs.h"
#include "Player.h"
#include "Food.h"
#include "objPosArrayList.h"

using namespace std;

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
    
    mechanics->collectAsyncInput();

    //debug key
    //if(mechanics->getInput() == ']');
        //food->generateFood(player_ptr->getPlayerPos());
    
}

void RunLogic(void)
{
    if(mechanics->getInput() != 0){
        player_ptr->updatePlayerDir();
        player_ptr->movePlayer();
    }else if(mechanics->getLastinput() != 0)
    {
        player_ptr->updatePlayerDir();
        player_ptr->movePlayer();
    }
    mechanics->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    int boardY = mechanics->getBoardSizeY();
    int boardX = mechanics->getBoardSizeX();
    
    objPosArrayList *temp = player_ptr->getPlayerPos();
    objPos temp_player = temp->getElement(0);
    int playerx = temp_player.pos->x;
    int playery = temp_player.pos->y;

    int foodx = food->getfoodx();
    int foody = food->getfoody();
    char foodsymbol = food->getsymbol();

    int score = mechanics->getScore();
    
    //debugging print statements 
    /*
    MacUILib_printf("food x:%d\n",foodx);
    MacUILib_printf("food y:%d\n",foody);

    MacUILib_printf("player x:%d\n",playerx);
    MacUILib_printf("player y:%d\n",playery);
    MacUILib_printf("player symbol:%c\n",temp_player.getSymbol());
    */

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
            else if(foody == i && foodx == j)
            {
                MacUILib_printf("%c",foodsymbol);
            }
            else
            {
                int count = 0;
                objPosArrayList *temp_list = player_ptr->getPlayerPos();
                for(int k = 0; k < player_ptr->getsizeoflist(); k++)
                {
                    objPos current_seg = temp_list->getElement(k);
                    if(current_seg.pos->x == j && current_seg.pos->y == i)
                    {
                       MacUILib_printf("%c",current_seg.getSymbol());
                       count++; 
                       break;
                    }
                }
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
    //delete food;
}
