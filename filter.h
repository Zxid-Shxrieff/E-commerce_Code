#ifndef FILTER_H
#define FILTER_H
#include "base.h"
typedef struct treenode{
    struct treenode *lchild;
    struct treenode *rchild;
    PRODUCT product;
}TREENODE;
TREENODE *BSTCreate(TREENODE *root, PRODUCT product);
PRODUCT *BSTSearch(TREENODE *root,int lowerLimit,int upperLimit,PRODUCT *recommendations,int i);
void recommend(PRODUCT *products,int lowerLimit,int upperLimit);
void BSTDisplay(TREENODE *root);
#endif