#include <iostream>
#include <stdlib.h>
#include "MacUILib.h"
#include "objPos.h"

#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

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
    player_ptr = new Player(mechanics);
    food = new Food;

    srand(time(0));
    food->generateFood(player_ptr->getPlayerPos());
}

void GetInput(void)
{
    if(MacUILib_hasChar())
    {
        mechanics->setInput(MacUILib_getChar());
        mechanics->setlastinput(mechanics->getInput());

        if(mechanics->getInput() == ']')
            food->generateFood(player_ptr->getPlayerPos());
    }
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
    MacUILib_printf("%s\n","##############################");
    for(int i = 0; i < mechanics->getBoardSizeY() - 2; i++){
        for(int j = 0; j < mechanics->getBoardSizeX(); j++){
            if(j == 0){
                MacUILib_printf("%c",'#');
            }else if(j == 29){
                MacUILib_printf("%c\n",'#');
            }else if(i == player_ptr->getPlayerY() && j == player_ptr->getPlayerX()){
                MacUILib_printf("%c",player_ptr->getplayerchar());
            }else if(i == food->getfoody() && j == food->getfoodx()){
                MacUILib_printf("%c",food->getsymbol());
            }else{
                MacUILib_printf("%c",' ');
            }
        }
    }
    MacUILib_printf("%s\n","##############################");
    const char *direction = player_ptr->getPlayerDir();
    MacUILib_printf("%s\n",direction);

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
