void deleteEntry(BPlusTree *tree, Node *node, double toDelete, Node * pointer){
    
    // Remove key and pointer from this node
    node = removeEntryFromTheNode(tree, node, toDelete, pointer);
    
    if (node == tree->root){
        adjustTheRoot(tree);
        return;
    }
    minNumberofKeys = getMinNumberOfKeys(tree, node);
    
    //simple case - node has still enough keys
    if (node->numOfKeys >= minNumberofKeys){
        return;
    }
    //node falls below minimum - Either merge or redistribute.
    neighbourIndex = getNeighbourIndex(node);
    kIndex = getKindex(neighbourIndex);
    innerKeyPrime = node->parent->keys[kIndex];
    
    neighbor = getNeighborNode(node);
    capacityOfNode = setCapacity(tree, node);
    
    //Merge if both nodes together have enough space
    if ((neighbor->numOfKeys + node->numOfKeys ) < capacity){
        mergeNodes(tree, node, neighbor, neighbourIndex, innerKeyPrime);
    }
    //Redistribute
    else{
        redestributeNodes(tree, node, neighbor, neighbourIndex, kIndex, innerKeyPrime);
    }
}
