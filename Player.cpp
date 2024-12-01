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
    //Insert head
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
        
        case '1':
            mainGameMechsRef->setGameSpeed(1);  // Slowest
            break;
        case '2':
            mainGameMechsRef->setGameSpeed(2);  // Normal
            break;
        case '3':
            mainGameMechsRef->setGameSpeed(3);  // Fastest
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
        temp.pos->x %= (boardSizeX-1);
        if(temp.pos->x == 0)
            temp.pos->x = 1;
    }
    else
        temp.pos->x = (boardSizeX - 2);
    
    if(temp.pos->y >= 0)
        temp.pos->y %= (boardSizeY - 2);
    else
        temp.pos->y = (boardSizeY - 3);
        
    
    //insert temp objpos to the head of the list
    playerPosList->insertHead(temp);
    playerPosList->removeTail();

    if (checkSelfCollision())
    {
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();
    }

    //check food consumption 
    if(checkFoodConsumption(temp))
    {
        increasePlayerLength(temp);
        foodRef->generateFood(playerPosList);
        mainGameMechsRef->incrementScore(playerPosList,consumedFood);
    }
    
}

// More methods to be added
bool Player::checkFoodConsumption(objPos temp)
{
    
    for(int i = 0; i < 5; i++)
    {
        //loop through the food list 
        objPosArrayList *temparrlist = foodRef->getFoodPos();
        objPos temp_buffer = temparrlist->getElement(i);
        // check if player overlaps the food
        if(temp.isPosEqual(&temp_buffer))
        {
            consumedFood = temp_buffer;
            return true;
        }
        
    }
    return false;
}

void Player::increasePlayerLength(objPos temp)
{
    if(consumedFood.symbol == '!') // special food
    {
        for(int i = 0; i < 10; i++) // increase length  by 10
        {
            playerPosList->insertTail(temp);
        }
        foodRef->generateFood(playerPosList);
    }else{
        playerPosList->insertHead(temp);
        foodRef->generateFood(playerPosList);
    }
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

bool Player::checkSelfCollision()
{
    objPos head = playerPosList->getElement(0);  // Get head position
    
    // Start from 1 to skip comparing head with itself
    for(int i = 1; i < playerPosList->getSize(); i++)
    {
        objPos segment = playerPosList->getElement(i);
        if(head.pos->x == segment.pos->x && head.pos->y == segment.pos->y)
        {
            return true;
        }
    }
    return false;
}