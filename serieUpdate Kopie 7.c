void update_CircularArray(BPlusTree *tree, CircularArray *array, timeStampT newTime, double newValue){
    
    int newUpdatePosition = 0;
    //array is not full yet
    if(array->count < array->size){
        if(array->count != 0){
            newUpdatePosition = (array->lastUpdatePosition + 1) %array->size;
        }
        array->count++;
    }
    //array is full -> one value is inserted and one is deleted
    else{
        newUpdatePosition = (array->lastUpdatePosition + 1) %array->size;
        //delete measurement from tree 
        delete(tree, array->data[newUpdatePosition].time, array->data[newUpdatePosition].value);
    }
    
    //update circularArray
    array->data[newUpdatePosition].time = newTime;
    array->data[newUpdatePosition].value = newValue;
    array->lastUpdatePosition = newUpdatePosition;
    
    addRecordToTree(tree, newTime, newValue);
    
}