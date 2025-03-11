#include <iostream>
#include <stack>
#include <queue>

class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;

    // ���캯��
    TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    TreeNode* root;

public:
    // ���캯��
    BinaryTree() : root(nullptr) {}

    // �������������ֶ�����ڵ㣩
    void insert(int value) {
        root = insertRec(root, value);
    }

    // �ݹ����ڵ�
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

    // ʹ�ò������������������
    void buildTreeLevelOrder(const std::vector<int>& values) {
        if (values.empty()) return;
        
        root = new TreeNode(values[0]);  // �������ڵ�
        std::queue<TreeNode*> q;
        q.push(root);
        int i = 1;
        
        while (!q.empty() && i < values.size()) {
            TreeNode* current = q.front();
            q.pop();

            // ������ڵ�
            if (i < values.size() && values[i] != -1) {  // -1 ��ʾ�սڵ�
                current->left = new TreeNode(values[i]);
                q.push(current->left);
            }
            i++;

            // �����ҽڵ�
            if (i < values.size() && values[i] != -1) {
                current->right = new TreeNode(values[i]);
                q.push(current->right);
            }
            i++;
        }
    }

    // ��ȡ���ڵ�
    TreeNode* getRoot() {
        return root;
    }

    // ǰ��������ݹ飩
    void preOrderRec(TreeNode* node) {
        if (node) {
            std::cout << node->val << " ";
            preOrderRec(node->left);
            preOrderRec(node->right);
        }
    }

    // ����������ݹ飩
    void inOrderRec(TreeNode* node) {
        if (node) {
            inOrderRec(node->left);
            std::cout << node->val << " ";
            inOrderRec(node->right);
        }
    }

    // ����������ݹ飩
    void postOrderRec(TreeNode* node) {
        if (node) {
            postOrderRec(node->left);
            postOrderRec(node->right);
            std::cout << node->val << " ";
        }
    }

    // ǰ��������ǵݹ飩
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

    // ����������ǵݹ飩
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

    // ����������ǵݹ飩
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

    // ����������ǵݹ飩
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
    /*P158.04 ���µ��� ���ҵ��� �ݹ�*/
    void levelOrder_adverse(TreeNode* node){
        if (!node) return;

        std::queue<TreeNode*> q;
        std::stack<TreeNode*> s;
        q.push(node);

       while (!q.empty()) {
           TreeNode* current = q.front();
           q.pop();
           s.push(current);

           // �Ƚ����ӽڵ���ӣ��ٽ����ӽڵ����
           if (current->left) q.push(current->left);
           if (current->right) q.push(current->right);
       }

       // ��ջ�е����ڵ㣬ʵ�ִ��µ��ϡ����ҵ����˳��
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
    /*.05 �ǵݹ������ĸ߶� */
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

    /*.06 �ж�����ȫ������*/
    bool isComplete(TreeNode* node){

    }

};

int main() {
    BinaryTree tree;

    // ʹ�ò����������������
    std::vector<int> values = {1, 2, 3, 4, -1, 5, 6};  // -1 ����սڵ�
    tree.buildTreeLevelOrder(values);

    TreeNode* root = tree.getRoot();

    std::cout << "ǰ��������ݹ飩: ";
    tree.preOrderRec(root);
    std::cout << "\n����������ݹ飩: ";
    tree.inOrderRec(root);
    std::cout << "\n����������ݹ飩: ";
    tree.postOrderRec(root);
    std::cout << "\n���������";
    tree.levelOrder(root);

    return 0;
}
