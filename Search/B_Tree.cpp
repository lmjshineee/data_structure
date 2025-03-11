#include <iostream>

template<typename T>
class BTreeNode {
public:
    T* keys;          // 存储键的数组
    BTreeNode** children; // 存储子节点的指针数组
    int degree;       // B 树的最小度数
    int numKeys;      // 当前节点的键数
    bool isLeaf;      // 是否是叶子节点

    BTreeNode(int _degree, bool _isLeaf) {
        degree = _degree;
        isLeaf = _isLeaf;
        keys = new T[2 * degree - 1];
        children = new BTreeNode * [2 * degree];
        numKeys = 0;
    }

    ~BTreeNode() {
        delete[] keys;
        delete[] children;
    }

    void insertNonFull(T key);
    void splitChild(int i);
    void traverse();
};

template<typename T>
class BTree {
public:
    BTreeNode<T>* root; // B 树的根节点
    int degree;         // B 树的最小度数

    BTree(int _degree) {
        root = nullptr;
        degree = _degree;
    }

    void insert(T key) {
        if (root == nullptr) {
            root = new BTreeNode<T>(degree, true);
            root->keys[0] = key;
            root->numKeys = 1;
        } else {
            if (root->numKeys == 2 * degree - 1) {
                BTreeNode<T>* newRoot = new BTreeNode<T>(degree, false);
                newRoot->children[0] = root;
                newRoot->splitChild(0);
                int i = 0;
                if (newRoot->keys[0] < key)
                    i++;
                newRoot->children[i]->insertNonFull(key);
                root = newRoot;
            } else {
                root->insertNonFull(key);
            }
        }
    }

    void traverse() {
        if (root != nullptr)
            root->traverse();
    }
};

template<typename T>
void BTreeNode<T>::insertNonFull(T key) {
    int i = numKeys - 1;
    if (isLeaf) {
        while (i >= 0 && keys[i] > key) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = key;
        numKeys++;
    } else {
        while (i >= 0 && keys[i] > key)
            i--;
        if (children[i + 1]->numKeys == 2 * degree - 1) {
            splitChild(i + 1);
            if (keys[i + 1] < key)
                i++;
        }
        children[i + 1]->insertNonFull(key);
    }
}

template<typename T>
void BTreeNode<T>::splitChild(int i) {
    BTreeNode<T>* z = new BTreeNode<T>(degree, children[i]->isLeaf);
    BTreeNode<T>* y = children[i];
    z->numKeys = degree - 1;

    for (int j = 0; j < degree - 1; j++)
        z->keys[j] = y->keys[j + degree];

    if (!y->isLeaf) {
        for (int j = 0; j < degree; j++)
            z->children[j] = y->children[j + degree];
    }
    y->numKeys = degree - 1;

    for (int j = numKeys; j >= i + 1; j--)
        children[j + 1] = children[j];

    children[i + 1] = z;

    for (int j = numKeys - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[degree - 1];
    numKeys++;
}

//中序遍历
template<typename T>
void BTreeNode<T>::traverse() {
    for (int i = 0; i < numKeys; i++) {
        if (!isLeaf)
            children[i]->traverse();
        std::cout << keys[i] << " ";
    }
    if (!isLeaf)
        children[numKeys]->traverse();
}

// 示例用法
int main() {
    BTree<int> bTree(3); // 创建一个最小度数为 3 的 B 树
    bTree.insert(10);
    bTree.insert(20);
    bTree.insert(5);
    bTree.insert(6);
    bTree.insert(12);
    bTree.insert(30);
    bTree.insert(7);
    bTree.insert(17);

    std::cout << "B 树的遍历结果：";
    bTree.traverse();
    std::cout << std::endl;

    return 0;
}
