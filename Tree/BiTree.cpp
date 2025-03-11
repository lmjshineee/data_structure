#include <iostream>
#include <stack>
#include <queue>

class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;

    // 构造函数
    TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    TreeNode* root;

public:
    // 构造函数
    BinaryTree() : root(nullptr) {}

    // 建立二叉树（手动插入节点）
    void insert(int value) {
        root = insertRec(root, value);
    }

    // 递归插入节点
    TreeNode* insertRec(TreeNode* node, int value) {
        if (!node) {
            return new TreeNode(value);
        }
        if (value < node->val) {
            node->left = insertRec(node->left, value);
        } else {
            node->right = insertRec(node->right, value);
        }
        return node;
    }

    // 使用层序遍历来构建二叉树
    void buildTreeLevelOrder(const std::vector<int>& values) {
        if (values.empty()) return;
        
        root = new TreeNode(values[0]);  // 创建根节点
        std::queue<TreeNode*> q;
        q.push(root);
        int i = 1;
        
        while (!q.empty() && i < values.size()) {
            TreeNode* current = q.front();
            q.pop();

            // 插入左节点
            if (i < values.size() && values[i] != -1) {  // -1 表示空节点
                current->left = new TreeNode(values[i]);
                q.push(current->left);
            }
            i++;

            // 插入右节点
            if (i < values.size() && values[i] != -1) {
                current->right = new TreeNode(values[i]);
                q.push(current->right);
            }
            i++;
        }
    }

    // 获取根节点
    TreeNode* getRoot() {
        return root;
    }

    // 前序遍历（递归）
    void preOrderRec(TreeNode* node) {
        if (node) {
            std::cout << node->val << " ";
            preOrderRec(node->left);
            preOrderRec(node->right);
        }
    }

    // 中序遍历（递归）
    void inOrderRec(TreeNode* node) {
        if (node) {
            inOrderRec(node->left);
            std::cout << node->val << " ";
            inOrderRec(node->right);
        }
    }

    // 后序遍历（递归）
    void postOrderRec(TreeNode* node) {
        if (node) {
            postOrderRec(node->left);
            postOrderRec(node->right);
            std::cout << node->val << " ";
        }
    }

    // 前序遍历（非递归）
    void preOrderIter(TreeNode* node) {
        if (!node) return;
        std::stack<TreeNode*> stack;
        stack.push(node);

        while (!stack.empty()) {
            TreeNode* current = stack.top();
            stack.pop();
            std::cout << current->val << " ";

            if (current->right) stack.push(current->right);
            if (current->left) stack.push(current->left);
        }
    }

    // 中序遍历（非递归）
    void inOrderIter(TreeNode* node) {
        std::stack<TreeNode*> stack;
        TreeNode* current = node;

        while (!stack.empty() || current != nullptr) {
            while (current != nullptr) {
                stack.push(current);
                current = current->left;
            }

            current = stack.top();
            stack.pop();
            std::cout << current->val << " ";

            current = current->right;
        }
    }

    // 后序遍历（非递归）
    void postOrderIter(TreeNode* node) {
        if (!node) return;

        std::stack<TreeNode*> stack1, stack2;
        stack1.push(node);

        while (!stack1.empty()) {
            TreeNode* current = stack1.top();
            stack1.pop();
            stack2.push(current);

            if (current->left) stack1.push(current->left);
            if (current->right) stack1.push(current->right);
        }

        while (!stack2.empty()) {
            std::cout << stack2.top()->val << " ";
            stack2.pop();
        }
    }

    // 层序遍历（非递归）
    void levelOrder(TreeNode* node) {
        if (!node) return;

        std::queue<TreeNode*> q;
        q.push(node);

        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();
            std::cout << current->val << " ";

            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
    }
    /*P158.04 从下到上 从右到左 递归*/
    void levelOrder_adverse(TreeNode* node){
        if (!node) return;

        std::queue<TreeNode*> q;
        std::stack<TreeNode*> s;
        q.push(node);

       while (!q.empty()) {
           TreeNode* current = q.front();
           q.pop();
           s.push(current);

           // 先将左子节点入队，再将右子节点入队
           if (current->left) q.push(current->left);
           if (current->right) q.push(current->right);
       }

       // 从栈中弹出节点，实现从下到上、从右到左的顺序
       while (!s.empty()) {
           std::cout << s.top()->val << " ";
           s.pop();
        }
    }

    int height(TreeNode* node){
        if (!node) return 0;
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return std::max(leftHeight, rightHeight) + 1;
    }
    /*.05 非递归求树的高度 */
    int height_iter(TreeNode* node){
        if (!node) return 0;
        std::queue<TreeNode*> q;
        q.push(node);
        int height = 0;

        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++) {
                TreeNode* current = q.front();
                q.pop();
                if (current->left) q.push(current->left);
                if (current->right) q.push(current->right);
            }
            height++;
        }
        return height;
    }

    /*.06 判断是完全二叉树*/
    bool isComplete(TreeNode* node){

    }

};

int main() {
    BinaryTree tree;

    // 使用层序遍历构建二叉树
    std::vector<int> values = {1, 2, 3, 4, -1, 5, 6};  // -1 代表空节点
    tree.buildTreeLevelOrder(values);

    TreeNode* root = tree.getRoot();

    std::cout << "前序遍历（递归）: ";
    tree.preOrderRec(root);
    std::cout << "\n中序遍历（递归）: ";
    tree.inOrderRec(root);
    std::cout << "\n后序遍历（递归）: ";
    tree.postOrderRec(root);
    std::cout << "\n层序遍历：";
    tree.levelOrder(root);

    return 0;
}
