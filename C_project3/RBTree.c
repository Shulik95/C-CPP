/**
 * @file RBTree.c
 * @author  Shalom Kachko
 * @version 1.0
 * @date 25 may 2020
 *
 * @brief A genetic red and black binary tree implementation.
 *
 * @section DESCRIPTION
 * The system keeps track of the cooking times.
 * Input  : Times to be measured.
 * Process: Summing times if needed, waiting for the correct time and
 *          notifying the user.
 * Output : Notification.
 */

// ------------------------------ includes ------------------------------
#include <stdio.h>
#include "RBTree.h"
#include <stdlib.h>

// -------------------------- const definitions -------------------------
/**
 * deals with creating the new node according to given side, balances tree after addition.
 */
#define CREATE_NODE(leftOrRight)\
Node* newNode = (Node*)malloc(sizeof(Node));\
parent->leftOrRight = newNode;\
newNode->color = RED;\
newNode->parent = parent;\
newNode->left = NULL;\
newNode->right = NULL;\
newNode->data = data;\
fixTree(newNode);


long unsigned const EMPTY_TREE_SIZE = 0;
int const ADD_SUCCESS = 1;
int const EQUAL = 0;
int const FAILED = 0;

// ------------------------------ functions -----------------------------

/**
 * finds a node with the same data or returns the Node which will be the parent
 * of a new node with the given data/
 * @param node - starts searching from this node downwards.
 * @param data - the data to search for/
 * @param cmp_func - functions which compares data of nodes.
 * @return - pointer to node/
 */
Node* findNode(Node* node, const void* data, CompareFunc cmp_func);

/**
 * balanced a RB tree after insertion.
 * @param node - the inserted node.
 */
void fixTree(Node* node);

/**
 * constructs a new RBTree with the given CompareFunc.
 * comp: a function to compare two variables.
 */
RBTree *newRBTree(CompareFunc compFunc, FreeFunc freeFunc)
{
    RBTree*  newTree = (RBTree*)malloc(sizeof(RBTree));
    newTree->root = NULL;
    newTree->compFunc = compFunc;
    newTree->freeFunc = freeFunc;
    newTree->size = EMPTY_TREE_SIZE;
    return newTree;
}

/**
 * add an item to the tree
 * @param tree: the tree to add an item to.
 * @param data: item to add to the tree.
 * @return: 0 on failure, other on success. (if the item is already in the tree - failure).
 */
int insertToRBTree(RBTree *tree, void *data)
{
    if(tree->root == NULL) //the tree is empty, create root.
    {
        Node* root = (Node*)malloc(sizeof(Node));
        root->parent = NULL;
        root->right = NULL;
        root->left = NULL;
        root->color = BLACK;
        root->data = data;
        tree->root = root;
        tree->size++;
        return ADD_SUCCESS;
    }
    else
    {
        Node* parent = findNode(tree->root, data, tree->compFunc); //find the future parent of the node
        int cmpVal = tree->compFunc(data, parent->data); //decide left or right.
        if(cmpVal == EQUAL) //value is already in tree
        {
            return FAILED;
        }
        else if (cmpVal > EQUAL) //node should be added on the right
        {
            CREATE_NODE(right);
        }
        else // node should be added as left son
        {
            CREATE_NODE(left);
        }
        tree->size++; //update tree size


    }
#undef CREATE_NODE
    return 0;
}

/**
 * find node with given data, for further info look
 * @param node
 * @param data
 * @param cmp_func
 * @return
 */
Node* findNode(Node* node, const void* data, CompareFunc cmp_func)
{

    if (node == NULL)
    {
        return node;
    }
    int cmpVal = cmp_func(data, node->data); //compare data to given node.
    if(cmpVal > EQUAL) // search the right subtree if it exists
    {
        if(node->right) //subtree exists
        {
            return findNode(node->right, data, cmp_func);
        }
        else //no subtree that is where the data fits.
        {
            return node;
        }
    }
    else if (cmpVal == EQUAL) // found a node containing the same data.
    {
        return node;
    }
    else // cmpVal < EQUAL, search left subtree
    {
        if(node->left) //subtree exists, search it
        {
            return findNode(node->left, data, cmp_func);
        }
        else // no subtree, returns future parent.
        {
            return node;
        }
    }
}

void fixTree(Node* node)
{
    
}


int main() {

    return 0;
}
