#include <iostream>
using namespace std;

typedef int ElemType;


/* AVL 树节点结构 */
typedef struct AVLTreeNode {
    ElemType key;
    int height;
    AVLTreeNode *left;
    AVLTreeNode *right;
} AVLTreeNode, *AVLTree;

/* 获取节点 node 的高度 */
int getHeight(AVLTreeNode *node) {
    return node == NULL ? -1 : node->height;
}


/* 获取节点 node 的平衡因子 */
int getBalanceFactor(AVLTreeNode *node) {
    return getHeight(node->left) - getHeight(node->right);
}

/* 打印 AVL 树 */
void printAVLTree(AVLTree T) {
    if (T == NULL) {
        return;
    }
    cout << T->key << " ";
    printAVLTree(T->left);
    printAVLTree(T->right);
}

/* 执行旋转操作，使该子树重新恢复平衡 */
AVLTreeNode *RotateLL(AVLTreeNode *node) {
    AVLTreeNode *left = node->left;
    node->left = left->right;
    left->right = node;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    left->height = max(getHeight(left->left), getHeight(left->right)) + 1;
    return left;
}

AVLTreeNode *RotateRR(AVLTreeNode *node) {
    AVLTreeNode *right = node->right;
    node->right = right->left;
    right->left = node;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    right->height = max(getHeight(right->left), getHeight(right->right)) + 1;
    return right;
}

AVLTreeNode *RotateLR(AVLTreeNode *node) {
    node->left = RotateRR(node->left);
    return RotateLL(node);
}

AVLTreeNode *RotateRL(AVLTreeNode *node) {
    node->right = RotateLL(node->right);
    return RotateRR(node);
}

void Balance(AVLTreeNode *node) {
    if (node == NULL) {
        return;
    }
    if (getBalanceFactor(node) > 1) {
        if (getBalanceFactor(node->left) > 0) {
            node = RotateLL(node);
        } else {
            node = RotateLR(node);
        }
    } else if (getBalanceFactor(node) < -1) {
        if (getBalanceFactor(node->right) < 0) {
            node = RotateRR(node);
        } else {
            node = RotateRL(node);
        }
    }
}

/* 插入节点 */
AVLTreeNode *Insert(AVLTreeNode *node, ElemType key) {
    if (node == NULL) {
        node = new AVLTreeNode();
        node->key = key;
        node->height = 0;
        node->left = node->right = NULL;
    } else if (key < node->key) {
        node->left = Insert(node->left, key);
        Balance(node);
    } else if (key > node->key) {
        node->right = Insert(node->right, key);
        Balance(node);
    }
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    return node;
}

/* 删除节点 */
AVLTreeNode *Delete(AVLTreeNode *node, ElemType key) {
    if (node == NULL) {
        return NULL;
    }
    if (key < node->key) {
        node->left = Delete(node->left, key);
        Balance(node);
    } else if (key > node->key) {
        node->right = Delete(node->right, key);
        Balance(node);
    } else {
        if (node->left != NULL && node->right != NULL) {
            AVLTreeNode *tmp = node->right;
            while (tmp->left != NULL) {
                tmp = tmp->left;
            }
            node->key = tmp->key;
            node->right = Delete(node->right, tmp->key);
            Balance(node);
        } else {
            AVLTreeNode *tmp = node;
            if (node->left == NULL) {
                node = node->right;
            } else if (node->right == NULL) {
                node = node->left;
            }
            delete tmp;
        }
    }
    if (node != NULL) {
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    }
    return node;
}


int main(){
    AVLTree T = NULL;
    int arr[] = {3, 2, 1, 4, 5, 6, 7, 10, 9, 8};
    int n=sizeof(arr)/sizeof(arr[0]);
    for (int i = 0; i < n; i++) {
        cout << "Inserting " << arr[i] << endl;
        Insert(T, arr[i]);
    }
    printAVLTree(T);
    return 0;
}