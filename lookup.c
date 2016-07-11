bool lookup(CircularArray *array, timeStampT t, double *value){
    
    //array is empty
    if(array->count == 0){
        return false;
    }
    
    //steps from last timestamp to new timestamp
    int step = (int)(t - array->data[array->lastUpdatePosition].time)/TIMESTAMP_DIFF;
    
    //checks if array has enough values inserted for the necessary steps
    if(abs(step) < array->count){
        
        //chaining modulo for negative numbers
        int pos = (((array->lastUpdatePosition+step)%array->size)+array->size)%array->size;
        
        //value has been found
        if(array->data[pos].time == t){
            //set the pointer to the found value
            *value = array->data[pos].value;
            return true;
        }
    }
    //value was not found
    return false;
}
