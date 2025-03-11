#include <iostream>
#include <vector>

template<typename T>
class BPlusTreeNode {
public:
    std::vector<T> keys;
    std::vector<BPlusTreeNode*> children;
    bool isLeaf;
    int degree;

    BPlusTreeNode(int _degree, bool _isLeaf) {
        degree = _degree;
        isLeaf = _isLeaf;
    }

    void traverse() {
        if (isLeaf) {
            for (const T& key : keys) {
                std::cout << key << " ";
            }
        } else {
            for (size_t i = 0; i < keys.size(); i++) {
                children[i]->traverse();
                std::cout << keys[i] << " ";
            }
            children[keys.size()]->traverse();
        }
    }
};

template<typename T>
class BPlusTree {
public:
    BPlusTreeNode<T>* root;
    int degree;

    BPlusTree(int _degree) {
        root = nullptr;
        degree = _degree;
    }

    void insert(T key) {
        if (root == nullptr) {
            root = new BPlusTreeNode<T>(degree, true);
            root->keys.push_back(key);
        } else {
            if (root->keys.size() == 2 * degree - 1) {
                BPlusTreeNode<T>* newRoot = new BPlusTreeNode<T>(degree, false);
                newRoot->children.push_back(root);
                splitChild(newRoot, 0);
                insertNonFull(newRoot, key);
                root = newRoot;
            } else {
                insertNonFull(root, key);
            }
        }
    }

    void insertNonFull(BPlusTreeNode<T>* node, T key) {
        int i = node->keys.size() - 1;
        if (node->isLeaf) {
            while (i >= 0 && node->keys[i] > key) {
                i--;
            }
            node->keys.insert(node->keys.begin() + i + 1, key);
        } else {
            while (i >= 0 && node->keys[i] > key) {
                i--;
            }
            i++;
            if (node->children[i]->keys.size() == 2 * degree - 1) {
                splitChild(node, i);
                if (node->keys[i] < key) {
                    i++;
                }
            }
            insertNonFull(node->children[i], key);
        }
    }

    void splitChild(BPlusTreeNode<T>* parent, int i) {
        BPlusTreeNode<T>* fullNode = parent->children[i];
        BPlusTreeNode<T>* newNode = new BPlusTreeNode<T>(degree, fullNode->isLeaf);
        
        // 复制键到新节点
        for (int j = 0; j < degree - 1; j++) {
            newNode->keys.push_back(fullNode->keys[j + degree]);
        }
        if (!fullNode->isLeaf) {
            for (int j = 0; j < degree; j++) {
                newNode->children.push_back(fullNode->children[j + degree]);
            }
        }

        parent->keys.insert(parent->keys.begin() + i, fullNode->keys[degree - 1]);
        parent->children.insert(parent->children.begin() + i + 1, newNode);
        
        fullNode->keys.resize(degree - 1);
    }

    void traverse() {
        if (root != nullptr) {
            root->traverse();
        }
    }
};

// 示例用法
int main() {
    BPlusTree<int> bTree(3); // 创建一个最小度数为 3 的 B+ 树
    bTree.insert(10);
    bTree.insert(20);
    bTree.insert(5);
    bTree.insert(6);
    bTree.insert(12);
    bTree.insert(30);
    bTree.insert(7);
    bTree.insert(17);

    std::cout << "B+ 树的遍历结果：";
    bTree.traverse();
    std::cout << std::endl;

    return 0;
}
