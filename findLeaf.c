Node * findLeaf(BPlusTree *tree, double newKey){
    int i = 0;
    
    Node * curNode = tree->root;
    
    if (curNode == NULL) {
        return curNode;
    }
    while (!curNode->isLeaf) {
        
        i = getInsertPoint(tree, curNode, newKey);
        //new lookup node
        curNode = (Node *)curNode->pointers[i];
    }
    //leaf found
    return curNode;
}
