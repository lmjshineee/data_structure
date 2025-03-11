/*

Implementation of Huffman greedy algorithm based the huffman algorithm pseudocode in "Introduction to Algorithms, Third Edition"

author: klchang
date: 2020.6
*/

#include <iostream>
#include <queue>
#include <vector>

struct Char {
    char ch;
    unsigned int freq;

    Char(char c, int fq): ch(c), freq(fq) {}
    Char(): ch(0), freq(0) {}
};

typedef struct BinaryTreeNode BinaryTreeNode;
struct BinaryTreeNode {
    Char c;
    BinaryTreeNode* left;
    BinaryTreeNode* right;

    BinaryTreeNode(): c(), left(nullptr), right(nullptr) {}
};

bool operator<(const BinaryTreeNode& lhs, const BinaryTreeNode& rhs)
{
    return lhs.c.freq < rhs.c.freq;
}

bool operator>(const BinaryTreeNode& lhs, const BinaryTreeNode& rhs)
{
    return lhs.c.freq > rhs.c.freq;
}

template<typename T>
T* extract_min(std::priority_queue<T, std::vector<T>, std::greater<T> >& pq)
{
    if (pq.empty()) {
        std::cout << "Empty priority queue!" << std::endl;
        return nullptr;
    }

    T* pnode = new T(pq.top());
    pq.pop();
    return pnode;
}

BinaryTreeNode* huffman(std::vector<Char>& charset)
{
    // Get the number of chars in charset
    int n = charset.size();

    // Construct priority queue (min heap) for char set
    std::priority_queue<BinaryTreeNode, std::vector<BinaryTreeNode>, std::greater<BinaryTreeNode>> pq;
    for (std::vector<Char>::iterator it = charset.begin(); it != charset.end(); ++it) {
        BinaryTreeNode node;
        node.c.ch = it->ch; 
        node.c.freq = it->freq;
        pq.push(node);
    }

    // Get non-leaf and leaf nodes:
    // get the lowest two frequencies objects, then merge them, and insert the merged object into pq
    for (int i = 0; i < n-1; i++) {
        BinaryTreeNode z;
        BinaryTreeNode* x = extract_min(pq);
        BinaryTreeNode* y = extract_min(pq);
        z.left = x;
        z.right = y;
        z.c.freq = x->c.freq + y->c.freq;
        pq.push(z);
    }
    return extract_min(pq);
}

// Use post-order traverse to deallocate BinaryTreeNode memory
void deallocate_memory(BinaryTreeNode* &root)
{
    if (root) {
        if (root->left)
            deallocate_memory(root->left);
        if (root->right)
            deallocate_memory(root->right);
        delete root;
        root = nullptr;
    }
}

void print_binarytree(const BinaryTreeNode* root, int order=0)
{
    if (root != nullptr) {
        if (order == 0)  // preorder traverse
            std::cout << "(" << root->c.ch << ", " << root->c.freq << ") ";
        if (root->left != nullptr)
            print_binarytree(root->left, order);
        if (order == 1) // inorder traverse
            std::cout << "(" << root->c.ch << ", " << root->c.freq << ") ";
        if (root->right != nullptr)
            print_binarytree(root->right, order);
        if (order == 2) // postorder traverse 
            std::cout << "(" << root->c.ch << ", " << root->c.freq << ") ";
    }
}

int main()
{    
    unsigned int table[] = {45, 13, 12, 16, 9, 5};
    int n = sizeof(table)/sizeof(table[0]);

    std::vector<Char> charset;

    for (int i = 0; i < n; i++) {
        charset.push_back(Char('a'+i, table[i]));
    }

    BinaryTreeNode* root = huffman(charset); 

    std::cout << " preorder sequence of huffman binary tree: " << std::endl
              << '\t';
    print_binarytree(root);
    std::cout << std::endl;

    std::cout << " inorder sequence of huffman binary tree: " << std::endl
              << '\t';
    print_binarytree(root, 1);
    std::cout << std::endl;

    std::cout << " postorder sequence of huffman binary tree: " << std::endl
              << '\t';
    print_binarytree(root, 2);
    std::cout << std::endl;

    // Deallocate all memory
    deallocate_memory(root);

    std::cin.get();
    /*  
     preorder sequence of huffman binary tree: 
        100 45 55 25 12 13 30 14 5 9 16 
     inorder sequence of huffman binary tree: 
        45 100 12 25 13 55 5 14 9 30 16 
    */
    return 0;
}