void splitAndInsertIntoLeaves(BPlusTree *tree, Node *oldNode, timeStampT time, double firstValue){
    
    Node * newNode = Leaf_new(tree->nodeSize);
    int insertPoint, split, i, j;
    double *tempKeys = malloc((tree->nodeSize + 1)* sizeof(double));;
    void **tempPointers = malloc((tree->nodeSize +1)* sizeof(void *));

    insertPoint = 0;
    int nrOfTempKeys = 0;
    insertPoint = getInsertPoint(tree, oldNode, firstValue);
    
    //fills the keys and pointers
    for (i = 0, j = 0; i < oldNode->numOfKeys; i++, j++) {
        //pointers needs to be moved 1 position
        if (j == insertPoint){
            j++;
        }
        //the value where the new record is added is not been filled yet
        tempKeys[j] = oldNode->keys[i];
        tempPointers[j] = oldNode->pointers[i];
        nrOfTempKeys++;
    }
    //enter the record to the right position
    tempKeys[insertPoint] = firstValue;
    ListValue * newTime = listValue_new(time);
    tempPointers[insertPoint] = newTime;
    nrOfTempKeys++;
    
    newNode->numOfKeys = 0;
    oldNode->numOfKeys = 0;
    
    //find split point
    split = getSplitPoint(tree->nodeSize);
    
    //fill first leaf
    fillLeaf(oldNode, tempKeys, tempPointers, split);
    //fill second leaf
    fillLeaf(newNode, tempKeys, tempPointers, split + nrOfTempKeys);

    //update intermediate leaf pointers
    updateLeafPointers(oldNode, newNode);
    
    //the record to insert into the upper node
    double keyForParent;
    keyForParent = newNode->keys[0];
    
    //free allocated memory of pointers
    free(tempKeys);
    free(tempPointers);
    
    insertIntoParent(tree, oldNode, keyForParent, newNode);
}