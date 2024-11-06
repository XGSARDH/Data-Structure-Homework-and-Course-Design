#ifndef AVL_BINARY_TREE_H
#define AVL_BINATY_TREE_H

#include "status_enum.h"

typedef int avlBiTElemType;

typedef struct avlBiTNode {
    avlBiTElemType data;
    int balance_factor;
    struct avlBiTNode *lchild, *rchild;
} avlBiTNode, *avlBiTree;

Status makeEqualavlBiTElemType(avlBiTElemType *purpose, avlBiTElemType *origin);
int IsEqualBiTElemType(avlBiTElemType a, avlBiTElemType b);
Status initAVL_default(avlBiTree *p);
Status initAVL(avlBiTree *p, avlBiTElemType avlBiTElemType);
Status destoryAVL(avlBiTree *p);
Status rRotate(avlBiTree *p);
Status lRotate(avlBiTree *p);
Status insertAVL(avlBiTree *p, avlBiTElemType e);
Status deleteAVL(avlBiTree *p, avlBiTElemType e);
Status visitAVL(avlBiTree p);
Status InOrderTraverseAVL(avlBiTree p, Status *visit(avlBiTree t));
Status printAVL(avlBiTree p);


#endif // AVL_BINATY_TREE_H