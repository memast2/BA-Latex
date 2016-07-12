void deleteFirstListValue(Node * leaf, int index){
    
    //first value in leaf
    ListValue * firstListValue = leaf->pointers[index];
    
    ListValue * next = firstListValue->next;
    ListValue * prev = firstListValue->prev;
    
    //next is the second oldest key
    leaf->pointers[index] = next;
    prev->next = next;
    next->prev = prev;
    
    /*always the first list value must be the oldest list value and
     therefore the one that is deleted first*/
    free(firstListValue);
}