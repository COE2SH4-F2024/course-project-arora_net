#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = START;

    // Initialize player position at the center of the board
    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2,mainGameMechsRef->getBoardSizeY() / 2,'*');
}


Player::~Player()
{
    // delete any heap members here
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;

}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic  
    char input = mainGameMechsRef -> getInput();
    
    switch(input)
    {
        case 'w': 
        case 'W':
            if(myDir != DOWN)
                myDir = UP;   
            break;
            
        case 's': 
        case 'S':
            if(myDir != UP)
                myDir = DOWN; 
            break;
            
        case 'a': 
        case 'A':
            if(myDir != RIGHT)
                myDir = LEFT; 
            break;
            
        case 'd': 
        case 'D':
            if(myDir != LEFT)
                myDir = RIGHT;  
            break;

        case ';':
            myDir = STOP;
            break;
            
        default: 
            break;
    }
    
    mainGameMechsRef->clearInput();  // Clear input buffer 
}        


void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    // Get board dimensions for boundary checking
    int boardSizeX = mainGameMechsRef->getBoardSizeX();
    int boardSizeY = mainGameMechsRef->getBoardSizeY();

    // Update position based on direction
    switch(myDir)
    {
        case UP:
            playerPos.DecrementY();
            break;
            
        case DOWN:
            playerPos.incrementY();
            break;
            
        case LEFT:
            playerPos.DecrementX();
            break;
            
        case RIGHT:
            playerPos.incrementX();
            break;
            
        case STOP:
            mainGameMechsRef->setExitTrue();
            break;  // No movement if direction is STOP
    }
    //wraparound logic
    if(playerPos.getPosx() >= 1)
    {
        playerPos.setPosx(playerPos.getPosx() % (boardSizeX-1));
        if(playerPos.getPosx() == 0)
            playerPos.setPosx(1);
    }
    else
        playerPos.setPosx(boardSizeX - 2);
    

    if(playerPos.getPosy() >= 0)
        playerPos.setPosy(playerPos.getPosy() % (boardSizeY - 2));
    else
        playerPos.setPosy((boardSizeY - 3));
    
    
}

// More methods to be added
int Player::getPlayerX()
{
    return playerPos.getPosx();
}
int Player::getPlayerY()
{
    return playerPos.getPosy();
}
char Player::getplayerchar()
{
    return playerPos.getSymbol();
}
const char* Player::getPlayerDir()
{
    switch (myDir)
    {
        case UP:
            return "UP";
        case DOWN:
            return "DOWN";
        case LEFT:
            return "LEFT";  
        case RIGHT:
            return "RIGHT";
        case STOP:
            return "STOP";
        case START:
            return "START";
        default:
            return "unknown";
    }
}