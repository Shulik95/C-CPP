//#include <stdio.h>
//#include <stdlib.h>
//#include "RBTree.h"
//#include "Structs.h"
//#include "RBUtilities.h"
//
//int compInt(void* data1, void* data2)
//{
//    int a = *((int*) data1);
//    int b = *((int*) data2);
//    if(a == b)
//        return 0;
//    if(a > b)
//        return 1;
//    return -1;
//}
//
//
//void insert(RBTree* t, void* data, const int i, const void* arr)
//{
//    insertToRBTree(t, data);
//    if(!isValidRBTree(t))
//    {
//        printf("ERROR - after the insertion of '%d', the tree is not valid\n", *((int*)data));
//        int* arrInt = (int*) arr;
//        printf("tried to insert in this order: ");
//        for(int j = 0; j < i; j++)
//        {
//            printf("%d ", arrInt[j]);
//        }
//        printf("\n");
//        printRBTree(t->root);
//        freeRBTree(&t);
//        exit(EXIT_FAILURE);
//    }
//}
//
//void delete(RBTree* t, void* data, const int i, const void* arr)
//{
//    if(deleteFromRBTree(t, data) == 0)
//    {
//        t->freeFunc(data);
//    }
//    if(!isValidRBTree(t))
//    {
//        printf("ERROR - after the deletion of '%d', the tree is not valid\n", *((int*)data));
//        int* arrInt = (int*) arr;
//        printf("tried to delete in this order: ");
//        for(int j = 0; j < i; j++)
//        {
//            printf("%d ", arrInt[j]);
//        }
//        printf("\n");
//        printRBTree(t->root);
//        freeRBTree(&t);
//        exit(EXIT_FAILURE);
//    }
//}
//
//void intFree(void* data)
//{
//    int stam_to_not_make_error = 0;
//}
//
//int main(){
//    int a[] = {-2422, -1396, 5630, 9292, 7672, -7625, -1222, 6640, -3898, 2298, 524, -8209, 8819, -7732, 5994, -379, 5273, -8850, 1860}; //todo - change this array's values!
//    RBTree* t = newRBTree((CompareFunc) &compInt, (FreeFunc) &intFree);
//    printf("Ints tree with %lu nodes: ", sizeof(a)/sizeof(a[0]));
//    for(int j = 0; j < sizeof(a)/sizeof(a[0]); j++)
//    {
//        insert(t, &a[j], sizeof(a)/sizeof(a[0]), a);
//    }
//    // finished insertion
//    for(int j = 0; j < sizeof(a)/sizeof(a[0]); j++)
//    {
//        if(j == 4)
//        {
//            printRBTree(t->root);
//        }
//        delete(t, &a[j], sizeof(a)/sizeof(a[0]), a);
//    }
//    if(t->size != 0)
//    {
//        printf("ERROR - deleted all the nodes from the tree and yet the tree's size if not 0\n");
//    }
//    freeRBTree(&t);
//    printf("passed\n");
//    return EXIT_SUCCESS;
//}