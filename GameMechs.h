#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;


class GameMechs
{
    private:
        char input;
        bool exitFlag;
        bool loseFlag;
        int score;
        bool inputStatus;

        int boardSizeX;
        int boardSizeY;

        int gameSpeed;

        objPos food;

        char lastinput;
        

    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        ~GameMechs(); // is this one needed at all? Why or why not?
        
        bool getExitFlagStatus() const; 
        void setExitTrue();
        bool getLoseFlagStatus() const;
        void setLoseFlag();

        char getInput() const;
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX() const;
        int getBoardSizeY() const;

        void setGameSpeed(int speed) { gameSpeed = speed; }
        int getGameSpeed() const { return gameSpeed; }
        
        int getScore() const;
        void incrementScore();
        
        // More methods should be added here
        void incrementScore(objPosArrayList *refList, objPos refFood);
        char getLastinput();
        void setlastinput(char in);
        void collectAsyncInput();
        void setLooseFalse();
};

#endif