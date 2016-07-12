void addDuplicateToDoublyLinkedList(Node *node, timeStampT newTime, double duplicateKey){
    
    int i;
    //find right key with the associated list
    for(i = 0; i < node->numOfKeys; i++){
        double currentKey = node->keys[i];
        
        if(duplicateKey == currentKey){
            break;
        }
    }
    
    ListValue * newListValue = listValue_new(newTime);
    
    //first value in leaf
    ListValue * firstListValue = node->pointers[i];
    ListValue * lastListValue = firstListValue->prev;
    
    //update doubly linked pointers
    firstListValue->prev = newListValue;
    lastListValue->next = newListValue;
    
    //new Value is inseted to the last position in the list
    newListValue->prev = lastListValue;
    newListValue->next = firstListValue;
    
}