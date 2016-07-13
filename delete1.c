void delete(BPlusTree *tree, timeStampT time, double value){
    
    leaf = findLeaf(tree, value);
    int positionOfKey = -1;
    
    positionOfKey = findLeafKeyIndexAndSetboolIfMultipleListValues(leaf, value, &hasMultipleTimes);
    
    //key has duplicates -- delete first value ind doubly linked list
    if(hasMultipleTimes){
        deleteFirstListValue(leaf, positionOfKey);
    }
    else{
        //delete key form tree
        deleteEntry(tree, leaf, leaf->keys[positionOfKey], NULL);
    }
}