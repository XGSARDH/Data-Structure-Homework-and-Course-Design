#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "status.h"

typedef int AvlElementType;

// AVL 树节点定义
typedef struct AvlNode {
    AvlElementType data;
    int balanceFactor;
    struct AvlNode *leftChild, *rightChild;
    int depth;
} AvlNode, *AvlTree;

typedef enum AvlElementCompareResult {
    // 表示左侧元素小于右侧元素
    AVLELEMENT_LESS = -1,
    // 表示两个元素相等
    AVLELEMENT_EQUAL = 0,
    // 表示左侧元素大于右侧元素
    AVLELEMENT_GREATER = 1
} AvlElementCompareResult;

/* 初始化 AVL 树 */
Status Avl_Init(AvlTree *root);

/* 默认初始化 AVL 树节点 */
Status AvlNode_InitDefault(AvlTree *node);

/* 初始化 AVL 树节点 */
Status AvlNode_Init(AvlTree *node, AvlElementType element);

/* 销毁 AVL 树 */
Status Avl_Destroy(AvlTree *root);

/* 右旋操作 */
Status Avl_RotateRight(AvlTree *root);

/* 左旋操作 */
Status Avl_RotateLeft(AvlTree *root);

/* 插入节点 */
Status Avl_Insert(AvlTree *root, AvlElementType element);

/* 删除节点 */
Status Avl_Delete(AvlTree *root, AvlElementType element);

/* 更新平衡因子 */
Status Avl_UpdateBalanceFactor(AvlTree root);

/* 访问节点值 */
Status Avl_VisitNode(AvlTree node);

/* 中序遍历 */
Status Avl_InOrderTraverse(AvlTree root);

/* 图形化打印 AVL 树 */
Status Avl_PrintTree(AvlTree root);

/* 元素赋值 */
Status AvlElement_Assign(AvlElementType *destination, AvlElementType *source);

/* 比较两个元素是否相等 */
AvlElementCompareResult AvlElement_IsEqual(AvlElementType a, AvlElementType b);

#endif // AVL_TREE_H