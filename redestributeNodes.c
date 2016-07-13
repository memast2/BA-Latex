void redestributeNodes(BPlusTree * tree, Node * node, Node * neighbor, int neighbourIndex, int kIndex, double kPrime){
    
    //node has a neighbor to the left. Pull the neighbor's last key-pointer pair over from the neighbor's right end to n's left end.
    if (neighbourIndex != -1) {
        if(!node->isLeaf){
            node->pointers[node->numOfKeys + 1] = node->pointers[node->numOfKeys];
        }
        for (i = node->numOfKeys; i > 0; i--) {
            node->keys[i] = node->keys[i - 1];
            node->pointers[i] = node->pointers[i - 1];
        }
        if (!node->isLeaf) {
            node->pointers[0] = neighbor->pointers[neighbor->numOfKeys];
            tmp = (Node *)node->pointers[0];
            tmp->parent = node;
            neighbor->pointers[neighbor->numOfKeys] = NULL;
            node->keys[0] = kPrime;
            
            //clear reason
            node->parent->keys[kIndex] = neighbor->keys[neighbor->numOfKeys-1];
        }
        else {
            node->keys[0] = neighbor->keys[neighbor->numOfKeys - 1];
            node->pointers[0] = neighbor->pointers[neighbor->numOfKeys - 1];
            node->parent->keys[kIndex] = node->keys[0];
        }
    }
    //node is the leftmost child. Take a key-pointer pair from the neighbor to the right.
    // Move the neighbor's leftmost key-pointer pair to n's rightmost position.
    else {
        if (node->isLeaf) {
            node->keys[node->numOfKeys] = neighbor->keys[0];
            node->pointers[node->numOfKeys] = neighbor->pointers[0];
            node->parent->keys[kIndex] = neighbor->keys[1];
        }
        else {
            node->keys[node->numOfKeys] = kPrime;
            node->pointers[node->numOfKeys + 1] = neighbor->pointers[0];
            tmp = (Node *)node->pointers[node->numOfKeys + 1];
            tmp->parent = node;
            node->parent->keys[kIndex] = neighbor->keys[0];
        }
        for (i = 0; i < neighbor->numOfKeys - 1; i++) {
            neighbor->keys[i] = neighbor->keys[i + 1];
            neighbor->pointers[i] = neighbor->pointers[i + 1];
            }
        }
        if (!node->isLeaf){
            neighbor->pointers[i] = neighbor->pointers[i + 1];
        }
    }
    //n now has one more key and one more pointer the neighbor has one fewer
    node->numOfKeys++;
    neighbor->numOfKeys--;
}