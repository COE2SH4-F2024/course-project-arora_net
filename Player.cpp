#include "Player.h"
#include "Food.h"


Player::Player(GameMechs* thisGMRef, Food *food)
{
    mainGameMechsRef = thisGMRef;
    myDir = START;
    foodRef = food;
    
    // Initialize player position at the center of the board
    playerPosList = new objPosArrayList;
    objPos headpos(mainGameMechsRef->getBoardSizeX() / 2,
                   mainGameMechsRef->getBoardSizeY() / 2,
                   '*');
    playerPosList->insertHead(headpos);
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos() const 
{
    // return the reference to the playerPos arrray list
    return playerPosList;

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

    // create a temp objpos to calculate the position of the head
    // get the head element of hte playerposlist as a good starting point
    objPos temp = playerPosList->getHeadElement();
    
    // Update position based on direction
    switch(myDir)
    {
        //calc the new position of the head using the temp 
        case UP:
            temp.pos->y--;
            break;
            
        case DOWN:
            temp.pos->y++;
            break;
            
        case LEFT:
            temp.pos->x--;
            break;
            
        case RIGHT:
            temp.pos->x++;
            break;
            
        case STOP:
            mainGameMechsRef->setExitTrue();
            break;  // No movement if direction is STOP
    }
    //wraparound logic
    if(temp.pos->x >= 1)
    {
        temp.setPosx(temp.pos->x % (boardSizeX-1));
        if(temp.pos->x == 0)
            temp.setPosx(1);
    }
    else
        temp.setPosx(boardSizeX - 2);
    

    if(temp.pos->y >= 0)
        temp.setPosy(temp.pos->y % (boardSizeY - 2));
    else
        temp.setPosy((boardSizeY - 3));
    
    //insert temp objpos to the head of the list
    playerPosList->insertHead(temp);
    playerPosList->removeTail();

    //iteration 2
    //  check if new objpos overlaps with foodpos (gamemechecs class) (isposequal)
    //  if overlaped food consumed do not remove snake tail and take the required actions 
    //  to increase the score
    
    if(checkFoodConsumption(temp))
    {
        increasePlayerLength(temp);
        foodRef->generateFood(playerPosList);
    }else{
        playerPosList->insertHead(temp);
        playerPosList->removeTail();
    }
    
    

    //Iteration 3
    // If no overlap remove tail complete movemnet


}

// More methods to be added
bool Player::checkFoodConsumption(objPos temp)
{

    objPos temp_buffer = foodRef->getFoodPos();
    if(temp.isPosEqual(&temp_buffer))
    {
        return true;
        playerPosList->insertHead(temp);
        foodRef->generateFood(playerPosList);
    }else{
        return false;
    }
    
}
void Player::increasePlayerLength(objPos temp)
{
    playerPosList->insertHead(temp);
    foodRef->generateFood(playerPosList);
}

int Player::getsizeoflist()
{
    return playerPosList->getSize();
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