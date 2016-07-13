Neighborhood *Neighborhood_new(BPlusTree *tree, Measurement *measurement,int patternLength, int offset){
    
    Node * leafNode;
    
    leafNode = findLeaf(tree, measurement->value);
    int pointerIndex = findLeafKeyIndex(leafNode, measurement->value);
    
    ListValue *listValueOnThatKey = leafNode->pointers[pointerIndex];
    
    //The value will be at most patternLength away in the doubly, linked list
    int maxSteps = patternLength;
    while(listValueOnThatKey->timestamp != measurement->timestamp && maxSteps != 0){
        //go from newest value back towards oldest
        listValueOnThatKey = listValueOnThatKey->prev;
        maxSteps--;
    }
    
    setNeighborhoodPositions(newNeighborhood, leftNeighbourhoodPos, rightNeighbourhoodPos, pointerIndex, leafNode, listValueOnThatKey);
    
    return newNeighborhood;
}
