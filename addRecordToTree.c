void addRecordToTree(BPlusTree *tree, timeStampT time, double value){
    
    Node *leaf;
    
    //the tree does not exist yet --> create tree
    if (tree->root == NULL){
        newTree(tree, time, value);
        return;
    }
    
    //find the leaf to insert the record
    leaf = findLeaf(tree, value);
    
    //if duplicate -> insert to leaf as Doubly linked list value
    if(isDuplicateKey(leaf, time, value)){
        addDuplicateToDoublyLinkedList(leaf, time, value);
    }
    //new key
    else if(leaf->numOfKeys < tree->nodeSize){
        insertRecordIntoLeaf(tree, leaf, time, value);
    }
    else{
        //leaf must be split
        splitAndInsertIntoLeaves(tree, leaf, time, value);
    }
}