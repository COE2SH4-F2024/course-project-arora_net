#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // Initialize player position at the center of the board
    playerPos.x = mainGameMechsRef->getBoardSizeX() / 2;
    playerPos.y = mainGameMechsRef->getBoardSizeY() / 2;
    playerPos.symbol = '*';  // Player symbol as specified in requirements

}


Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos) const
{
    // return the reference to the playerPos arrray list
    returnPos = playerPos;

}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic  
    char input = mainGameMechsRef -> getInput();
    
    switch(input)
    {
        case 'w': 
        case 'W':
            myDir = UP; 
            break;
            
        case 's': 
        case 'S':
            myDir = DOWN; 
            break;
            
        case 'a': 
        case 'A':
            myDir = LEFT; 
            break;
            
        case 'd': 
        case 'D':
            myDir = RIGHT; 
            break;
            
        default: 
            break;
    }
    
    mainGameMechsRef->clearInput();  // Clear input buffer 
    }        
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
            if(playerPos.y <= 0) playerPos.y = boardSizeY - 2;
            else playerPos.y--;
            break;
            
        case DOWN:
            if(playerPos.y >= boardSizeY - 1) playerPos.y = 1;
            else playerPos.y++;
            break;
            
        case LEFT:
            if(playerPos.x <= 0) playerPos.x = boardSizeX - 2;
            else playerPos.x--;
            break;
            
        case RIGHT:
            if(playerPos.x >= boardSizeX - 1) playerPos.x = 1;
            else playerPos.x++;
            break;
            
        case STOP:
            break;  // No movement if direction is STOP
    }
    
}

// More methods to be added