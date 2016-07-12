void deleteEntry(BPlusTree *tree, Node *node, double toDelete, Node * pointer){
    
    int minNumberofKeys;
    Node * neighbor;
    int neighbourIndex;
    int kIndex;
    int capacity;
    double innerKeyPrime;
    
    // Remove key and pointer from node
    node = removeEntryFromTheNode(tree, node, toDelete, pointer);
    
    if (node == tree->root){
        adjustTheRoot(tree);
        return;
    }
    
    // deletion from an innernode or leaf
    if(node->isLeaf){
        minNumberofKeys = getSplitPoint(tree->nodeSize);
    }
    else{
        minNumberofKeys = getSplitPoint(tree->nodeSize + 1) - 1;
    }
    
    //simple case - node has still enough keys
    if (node->numOfKeys >= minNumberofKeys){
        return;
    }
    
    /*
     node falls below minimum. Either merge or redistribute
     Find the appropriate neighbor node with which to merge.
     Also finds the key (kPrime) in the parent between the pointer to the node and the
     pointer to the neighbor
    */
    neighbourIndex = getNeighbourIndex(node);
    
    if(neighbourIndex ==-1){
        kIndex = 0;
    }
    else{
        kIndex = neighbourIndex;
    }
    
    innerKeyPrime = node->parent->keys[kIndex];
    
    if(neighbourIndex == -1){
        neighbor = node->parent->pointers[1];
    }else{
        neighbor = node->parent->pointers[neighbourIndex];
    }
    
    if(node->isLeaf){
        capacity = tree->nodeSize + 1;
    }
    else{
        capacity = tree->nodeSize;
    }
    
    //Merge if both nodes together have enough space
    if ((neighbor->numOfKeys + node->numOfKeys ) < capacity){
        mergeNodes(tree, node, neighbor, neighbourIndex, innerKeyPrime);
    }
    
    //Redistribute
    else{
        redestributeNodes(tree, node, neighbor, neighbourIndex, kIndex, innerKeyPrime);
    }
}
