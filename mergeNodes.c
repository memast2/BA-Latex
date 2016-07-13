void mergeNodes(BPlusTree *tree, Node *node, Node *neighbor, int neighborIndex, double kPrime){

    //Swap neighbor with node if node is on the extreme left and neighbor is to its right.
    if (neighborIndex == -1) {
        tmp = node;
        node = neighbor;
        neighbor = tmp;
    }
    /*Starting point in the neighbor for copying keys and pointers from the other node.
    Recall that n and neighbor have swapped places
    in the special case of the node being a leftmost child */
    neighborInsertionIndex = neighbor->numOfKeys;
    
    //Append k_prime and the following pointer - append all pointers and keys from the neighbor
    if(!node->isLeaf)
    {
        neighbor->keys[neighborInsertionIndex] = kPrime;
        neighbor->numOfKeys++;
        
        int decreasingIndex = 0;
        int numOfKeysBefore = node->numOfKeys;
        
        for (i = neighborInsertionIndex + 1, j = 0; j < node->numOfKeys; i++, j++) {
            neighbor->keys[i] = node->keys[j];
            neighbor->pointers[i] = node->pointers[j];
            neighbor->numOfKeys++;
            //decreases numOfKeys
            decreasingIndex++;
        }
        node->numOfKeys = numOfKeysBefore - decreasingIndex;
        neighbor->pointers[i] = node->pointers[j];
        //All children must now point up to the same parent.
        for (i = 0; i < neighbor->numOfKeys + 1; i++) {
            tmp = (Node *)neighbor->pointers[i];
            tmp->parent = neighbor;
        }
    }
    // leaf node, append the keys and pointers of the node to the neighbor.
    //Set the neighbor's last pointer to point to what had been the node's right neighbor.
    else
    {
        for (i = neighborInsertionIndex, j = 0; j < node->numOfKeys; i++, j++) {
            neighbor->keys[i] = node->keys[j];
            neighbor->pointers[i] = node->pointers[j];
            neighbor->numOfKeys++;
        }
        //relink leafs
        if(node->next != NULL){
            (node->next)->prev = neighbor;
        }
        neighbor->next = node->next;
    }
    deleteEntry(tree, node->parent, kPrime, node);
    destroyNode(node);
}
