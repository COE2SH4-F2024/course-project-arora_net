#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

#include "GameMechs.h"
#include "Player.h"

using namespace std;
GameMechs *mechanics;
Player *player;

#define DELAY_CONST 100000

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(!mechanics->getExitFlagStatus())  
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
    
}

void GetInput(void)
{
    if(MacUILib_hasChar())
    {
        mechanics->setInputStatusTrue();
        mechanics->setInput(MacUILib_getChar());
    }
}

void RunLogic(void)
{
    
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
            }else{
                MacUILib_printf("%c",' ');
            }
        }
    }
    MacUILib_printf("%s\n","##############################");
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
}
