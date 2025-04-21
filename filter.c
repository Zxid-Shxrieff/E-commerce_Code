#include"filter.h"
TREENODE *BSTCreate(TREENODE *root, PRODUCT product){
    if (!root){
        TREENODE *newnode = (TREENODE *)malloc(sizeof(TREENODE));
        newnode->lchild = newnode->rchild = NULL;
        newnode->product=product;
        return newnode;
    }else{
        if (product.price <= root->product.price){root->lchild = BSTCreate(root->lchild, product);}
        else    {root->rchild = BSTCreate(root->rchild, product);}
    }
    return root;
}
PRODUCT *BSTSearch(TREENODE *root,int lowerLimit,int upperLimit,PRODUCT *recommendations,int i){
    if(root){
        recommendations=BSTSearch(root->lchild,lowerLimit,upperLimit,recommendations,i);
        if(root->product.price>=lowerLimit && root->product.price<=upperLimit){
            recommendations[i]=root->product;
            i++;
        }
        recommendations=BSTSearch(root->rchild,lowerLimit,upperLimit,recommendations,i);
        
    }else{
        return recommendations;
    }
}
void recommend(PRODUCT *products,int lowerLimit,int upperLimit){
    TREENODE *root=NULL;
    for(int i=0;i<MAX_PRODUCTS;i++){root=BSTCreate(root,products[i]);}
    PRODUCT *recommendations=(PRODUCT *)malloc(sizeof(PRODUCT)*MAX_PRODUCTS);
    int i=0;
    recommendations=BSTSearch(root,lowerLimit,upperLimit,recommendations,i);
    printProducts(recommendations);
} 
void BSTDisplay(TREENODE *root)
{
    if (root)
    {
        BSTDisplay(root->lchild);
        printf("%f ", root->product.price);
        BSTDisplay(root->rchild);
    }
}


