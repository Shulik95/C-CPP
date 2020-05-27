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
#include "RBTree.h"
#include <stdlib.h>
#include <stdio.h>
#include "utilities/RBUtilities.h"
#include <stdbool.h>

// -------------------------- const definitions -------------------------
/**
 * deals with creating the new node according to given side, balances tree after addition.
 */
#define CREATE_NODE(leftOrRight, tree)\
Node* newNode = (Node*)malloc(sizeof(Node));\
parent->leftOrRight = newNode;\
newNode->color = RED;\
newNode->parent = parent;\
newNode->left = NULL;\
newNode->right = NULL;\
newNode->data = data;\
fixTree(newNode, tree);


long unsigned const EMPTY_TREE_SIZE = 0;
int const SUCCESS = 1;
int const EQUAL = 0;
int const FAILED = 0;


// ------------------------------ functions -----------------------------

/**
 * finds a node with the same data or returns the Node which will be the parent
 * of a new node with the given data/
 * @param node - starts searching from this node downwards.
 * @param data - the data to search for/
 * @param cmp_func - functions which compares data of nodes.
 * @return - pointer to node.
 */
Node* findNode(Node* node, const void* data, CompareFunc cmp_func);

/**
 * left rotation according to different cases.
 * @param node
 */
void rotateLeft(Node* node);

/**
 * right rotation according to given cases.
 * @param node
 */
void rotateRight(Node* node);

/**
 * balanced a RB tree after insertion.
 * @param node - the inserted node.
 * @param tree - RB tree were working on.
 */
void fixTree(Node* node, RBTree* tree);

/**
 * helper function for traversal memory freeing.
 * @param node - starting node.
 * @param freeFunc.
 */
void freeRBHelper(Node** node, FreeFunc freeFunc);

/**
 * checks if the given node is the left child.
 * @param node - node to check.
 * @return - 1 if is left child, otherwise 0.
 */
int isLeftChild(Node* const node)
{
    if(node == NULL || node->parent == NULL)
    {
        return FAILED;
    }
    else
    {
        return (node->parent->left == node) ? SUCCESS : FAILED;
    }
}

/**
 * checks if the given node a right child.
 * @param node - node to check.
 * @return - 1 if right child, 0 otherwise.
 */
int isRightChild(Node* node)
{
    if(node == NULL || node->parent == NULL)
    {
        return FAILED;
    }
    else
    {
        return (node->parent->right == node) ? SUCCESS : FAILED;
    }
}

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
 * add an item to the tree, doesnt assume tree is not empty.
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
        return SUCCESS;
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
            CREATE_NODE(right,tree)
        }
        else // node should be added as left son
        {
            CREATE_NODE(left, tree)
        }
        tree->size++; //update tree size
        return SUCCESS;
    }
}

/**
 * find node with given data, for further info look
 * @param node
 * @param data
 * @param cmp_func
 * @return
 */
Node* findNode(Node* node, const void* data, const CompareFunc cmp_func)
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



/**
 * checks if both right and left child of given node are red.
 * @param node - parent of both nodes.
 * @return - 1 if both are red 0 otherwise.
 */
int bothRed(Node* const node)
{
    if(node->left && node->right)
    {
        return (node->left->color == RED && node->right->color == RED) ? SUCCESS:FAILED;
    }
    return FAILED;
}

/**
 * updates root of tree in case the root was rotated
 * @param tree
 * @param node
 */
void updateRoot(RBTree* tree, Node* node)
{
    if(node == tree->root)
    {
        tree->root = node->parent;
        tree->root->color = BLACK;
    }

}

/**
 * balances the tree from inserted node all the way up.
 * @param node - start balancing from here.
 */
void fixTree(Node* const node, RBTree* tree)
{
    Node* parent = NULL;
    Node* grandParent = NULL;
    if(node)
    {
        if(node->parent == NULL) //node is root.
        {
            node->color = BLACK;
            return;
        }
        else if(node->parent->color == BLACK) //2nd case - do nothing.
        {
          /*do nothing*/
            return;
        }
        parent = node->parent;
        grandParent = parent->parent;
        if (parent->color == RED && bothRed(grandParent)) //3rd case - parent and uncle are red.
        {
            /*two uncle exist so both might be RED, check it.*/
                grandParent->left->color = BLACK;
                grandParent->right->color = BLACK;
                grandParent->color = RED;
                fixTree(grandParent, tree); //run algorithm from grandparent
        }
        else  //4th case - parent is red, uncle is black.
        {
            if(isLeftChild(node) == SUCCESS && isRightChild(parent) == SUCCESS) //left child of right child, 4.a
            {
                rotateRight(parent);
                updateRoot(tree, parent);
            }
            else if(isRightChild(node) == SUCCESS && isLeftChild(parent) == SUCCESS) //right child of left child, 4.a
            {
                rotateLeft(parent);
                updateRoot(tree, parent);
            }
            else // case 4.b
            {
                if(isLeftChild(node) == SUCCESS && isLeftChild(parent) == SUCCESS) // left child of left child, 4.b
                {
                    rotateRight(grandParent);
                    updateRoot(tree, grandParent);
                }
                else if (isRightChild(node) == SUCCESS && isRightChild(parent) == SUCCESS)//right child of right child
                {
                    rotateLeft(grandParent);
                    updateRoot(tree, grandParent);
                }
            }
            parent->color = BLACK;
            grandParent->color = RED;
        }
    }
}

/**
 * rotates given tree to the left.
 * @param node -assumes this node is root of subtree to rotate, meaning this node will go down a level in the tree.
 */
void rotateLeft(Node* const node)
{
    Node* keepNode = node->right->left; //save data
    node->right->left = node; //set node to correct place

    if(keepNode != NULL)
    {
        keepNode->parent = node;
    }

    if(isLeftChild(node) == SUCCESS)
    {
        node->parent->left = node->right;

    }

    else if(isRightChild(node) == SUCCESS)
    {
        node->parent->right = node->right;
    }

    node->right->parent = node->parent; //change parent of son
    node->parent = node->right; //change parent of rotated node.
    node->right = keepNode; //assign value - might be null but were okay

}

/**
 * rotates tree to the right.
 * @param node - assumes this node is root of subtree to rotate, meaning this node will go down a level in the tree.
 */
void rotateRight(Node* node)
{
    Node* keepNode = node->left->right;
    node->left->right = node;

    if(keepNode != NULL)
    {
        keepNode->parent = node;
    }

    if(isLeftChild(node) == SUCCESS)
    {
        node->parent->left = node->left;

    }

    else if(isRightChild(node) == SUCCESS)
    {
        node->parent->right = node->left;
    }

    node->left->parent = node->parent;
    node->parent = node->left;
    node->left = keepNode;
}

/**
 * check whether the tree RBTreeContains this item.
 * @param tree: the tree to check an item in.
 * @param data: item to check.
 * @return: 0 if the item is not in the tree, other if it is.
 */
int RBTreeContains(const RBTree *tree, const void *data)
{
    if(tree == NULL)
    {
        return FAILED;
    }
    Node* tempNode = findNode(tree->root, data, tree->compFunc); //returns same node or parent of data
    if(tempNode == NULL) //findNode function failed :(
    {
        return FAILED;
    }
    return tree->compFunc(tempNode->data, data) == EQUAL;
}

/**
 * helper function which activates a function on all node in-order.
 * @param node - starting node.
 * @param func - function to activate.
 * @param args - more optional args.
 * @return- 1 if all goes well, 0 otherwise.
 */
int forEachHelper(Node* node, forEachFunc func, void *args)
{
    if(!node)
    {
        return SUCCESS;
    }
    int lSubTreeSuccess = forEachHelper(node->left, func, args);
    int rootSuccess = func(node->data, args);
    int rSubTreeSuccess = forEachHelper(node->right, func, args);
    return (rootSuccess && lSubTreeSuccess && rSubTreeSuccess);
}

/**
 * Activate a function on each item of the tree. the order is an ascending order. if one of the activations of the
 * function returns 0, the process stops.
 * @param tree: the tree with all the items.
 * @param func: the function to activate on all items.
 * @param args: more optional arguments to the function (may be null if the given function support it).
 * @return: 0 on failure, other on success.
 */

int forEachRBTree(const RBTree *tree, forEachFunc func, void *args)
{
    if(tree == NULL)
    {
        return SUCCESS;
    }
    return  forEachHelper(tree->root, func, args);
}

/**
 * helper for freeRBTree, traverses both subtrees and free memory using given function.
 * @param node - startin node.
 * @param freeFunc - funtion for freeing given data type.
 */
void freeRBHelper(Node** node, FreeFunc freeFunc)
{
    if((*node) == NULL)
    {
        /*base case*/
        return;
    }
    else
    {
        freeRBHelper(&(*node)->right, freeFunc); //free left subtree
        freeRBHelper(&(*node)->left, freeFunc); //free right subtree
        freeFunc((*node)->data); //free data
        freeFunc((*node)); //free the node itself.
    }
}

/**
 * free all memory of the data structure.
 * @param tree: pointer to the tree to free.
 */
void freeRBTree(RBTree **tree)
{
    freeRBHelper(&(*(tree))->root, (*tree)->freeFunc);
    free((*tree));
}



int main()
{
    return 0;
}


