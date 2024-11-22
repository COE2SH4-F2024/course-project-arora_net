#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    arrayCapacity = ARRAY_MAX_CAP;  // Using the defined constant
    listSize = 0;
    aList = new objPos[arrayCapacity];
    
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if(listSize >= ARRAY_MAX_CAP){
        return;
    }   
    for(int i = listSize; i > 0; i--){ // shift right
        aList[i] = aList[i - 1];
    }
    aList[0] = thisPos;
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize < ARRAY_MAX_CAP) { // if there's still room
        aList[listSize] = thisPos;  // no shift needed
        listSize++; 
    } 
}

void objPosArrayList::removeHead()
{
    if(listSize == 0) // empty list
        return;
    for(int i = 0; i < listSize - 1; i++) // shift left
        aList[i] = aList[i + 1];
    listSize--; 
}

void objPosArrayList::removeTail()
{
    if(listSize > 0)
        listSize--; // no shift needed
}

objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    return aList[listSize - 1];
}

objPos objPosArrayList::getElement(int index) const
{
    if(index < 0)
        index = 0;
    else if(index >= arrayCapacity)
        index = listSize - 1;

    return aList[index];
}