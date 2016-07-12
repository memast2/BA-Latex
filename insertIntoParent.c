void insertIntoParent(BPlusTree *tree, Node *oldChild, double newKey, Node *newChild){
    
    int pointerPositionToLeftNode;
    Node * parent = oldChild->parent;
    
    //new root
    if(parent == NULL){
        insertIntoANewRoot(tree, oldChild, newKey, newChild);
        return;
    }
    
    //Find the parents pointer to the old node
    pointerPositionToLeftNode = getLeftPointerPosition(parent, oldChild);
    
    //the new key fits into the node
    if (parent->numOfKeys < tree->nodeSize){
        insertIntoTheNode(parent, pointerPositionToLeftNode, newKey, newChild);
    }
    else{
        //split a node in order to preserve the B+ tree properties
        splitAndInsertIntoInnerNode(tree, parent, pointerPositionToLeftNode, newKey, newChild);
    }
}