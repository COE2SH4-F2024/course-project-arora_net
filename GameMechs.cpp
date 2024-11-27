#include "GameMechs.h"
#include "MacUILib.h"
#include "objPosArrayList.h"



GameMechs::GameMechs()
{   
    exitFlag = 0;
    loseFlag = 0;
    score = 0;
    inputStatus = false;
    exitFlag = false;
    boardSizeX = 30;
    boardSizeY = 15;
    score = 0;
    
}

GameMechs::GameMechs(int boardX, int boardY)
{
    exitFlag = 0;
    loseFlag = 0;
    score = 0;
    inputStatus = false;
    exitFlag = false;
    boardSizeX = boardX;
    boardSizeY = boardY;
    score = 0;
   
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

char GameMechs::getInput() const
{
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score = getScore() + 1;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

// More methods should be added here
void GameMechs::incrementScore(objPosArrayList *refList)
{
    score = refList->getSize() - 1;
}

int GameMechs::getInputStatus() const
{
    return inputStatus;
}

void GameMechs::setInputStatusTrue()
{
    inputStatus = true;
}

char GameMechs::getLastinput() 
{
    return lastinput;
}

void GameMechs::setlastinput(char in)
{
    lastinput = in;
}

void GameMechs::collectAsyncInput()
{
    if(MacUILib_hasChar())
    {
        input = MacUILib_getChar();
        lastinput = input;
    }
}