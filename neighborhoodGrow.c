bool Neighborhood_grow(Neighborhood *self, TimeSet *timeset, timeStampT *timestamp){
    
    bool neighborHoodHasGrown = true;
    //get the left neighbor of the measurement
    
    leftPos = getTMinusNeighborHoodPosition(leftPos);
    offsetMinusTime = getOffsetTime(self, leftPos);

    //get the right neighbor of the measurement
    rightPos = getTPlusNeighborHoodPosition(rightPos);
    offsetPlusTime = getOffsetTime(self, rightPos);
    
    //checks if offsetTime is in timestamp set
    while(leftPos.timeStampPosition != NULL && TimeSet_contains(timeset, offsetMinusTime)){
        leftPos = getTMinusNeighborHoodPosition(leftPos);
        offsetMinusTime = getOffsetTime(self, leftPos);

        //next time doesnt have to check this position again
        self->leftPosition = leftPos;
    }
    
    while(rightPos.timeStampPosition != NULL && TimeSet_contains(timeset, offsetPlusTime)){
        rightPos = getTPlusNeighborHoodPosition(rightPos);
        offsetPlusTime = getOffsetTime(self, rightPos);
        
        //next time doesnt have to check this position again
        self->rightPosition = rightPos;
    }
    
    if(leftPos.timeStampPosition != NULL && rightPos.timeStampPosition != NULL){
        
        long tMinusdifference = fabs(leftPos.LeafPosition->keys[leftPos.indexPosition] - self->key);
        long tPlusdifference = fabs(rightPos.LeafPosition->keys[rightPos.indexPosition] - self->key);
        
        if(tMinusdifference <= tPlusdifference){
            self->leftPosition = leftPos;
            *timestamp = leftPos.timeStampPosition->timestamp;
        }
        else{
            self->rightPosition = rightPos;
            *timestamp = rightPos.timeStampPosition->timestamp;
        }
    }
    else if(leftPos.timeStampPosition != NULL){
        self->leftPosition = leftPos;
        *timestamp = leftPos.timeStampPosition->timestamp;
        
    }
    else if(rightPos.timeStampPosition != NULL){
        self->rightPosition= rightPos;
        *timestamp = rightPos.timeStampPosition->timestamp;
    }
    else{
        neighborHoodHasGrown = false;
    }
    return neighborHoodHasGrown;
    
}