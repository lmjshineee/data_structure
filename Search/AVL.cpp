#include<iostream>
using namespace std;

template<class K,class V>
struct AVLTreeNode {
		AVLTreeNode(const pair<K,V>&kv)
			:_left(nullptr)
			,_right(nullptr)
			,_kv(kv)
			,h(1)//一个节点的高度为 1
		{}
 
		AVLTreeNode<K, V>* _left;//左指针
		AVLTreeNode<K, V>* _right;//右指针
		pair<K, V> _kv;
		int h;//高度
};
 
	template<class K, class V>
	class AVLTree {
	public:
		
	typedef struct AVLTreeNode<K, V> Node;
	AVLTree(int size = 0, Node* root = nullptr)
		:_size(size)
		, _root(root)
	{}
	Node* add(Node* cur, const pair<K, V>& kv){
		if (cur == nullptr) {//空树直接 new 出节点并返回
			return new Node(kv);
		}
		else {
			if (cur->_kv.first < kv.first) {//比当前节点大
				cur->_right = add(cur->_right, kv);//去 cur 的右边插入并将新的头部返回
			}
 
			else {
				cur->_left = add(cur->_left, kv);//去 cur 的左边插入并将新的头部返回
			}
			cur->h = max(cur->_left != nullptr ? cur->_left->h : 0, cur->_right != nullptr ? cur->_right->h : 0)+1;//重新计算高度
			return maintain(cur);//对 cur 这个树进行调整
		}
 
	}
	bool insert(const pair<K, V>& kv) {
		Node* lastNode = findLastIndex(kv.first);
		if (lastNode && lastNode->_kv.first == kv.first) {
			return false;
		}
		else {
			_size++;
			_root = add(_root, kv);
			return true;
		}
	}
 
	Node* Delete(Node* cur, K key) {
		if (cur->_kv.first < key) {
			cur->_right = Delete(cur->_right, key);//去我的右边删除并且返回新的头部
		}
		else if (cur->_kv.first > key) {
			cur->_left = Delete(cur->_left, key);//去我的左边删除并返回新的头部
		}
		else {
			if (cur->_left==nullptr && cur->_right==nullptr) {//叶子节点左右都为空
				delete cur;
				return nullptr;
				
			}
			else if (!cur->_left && cur->_right) {//左为空但右不为空
				Node* subR = cur->_right;
				delete cur;
				cur = subR;
			}
			else if (cur->_left && !cur->_right) {//右为空但左不为空
				Node* subL = cur->_left;
				delete cur;
				cur = subL;
			}
			else {//左右都不为空采用替换法删除既采用值的方式替代
				Node* des = cur->_right;//找到右树最左节点或者找到左树的最右节点都可以
				while (des->_left)
				{
					des = des->_left;
				}
				pair<K, V>Kv = des->_kv;//记录对应的值
				cur->_right = Delete(cur->_right, des->_kv.first);//找到我先不删调用 Delete 将 des 删掉并将树调整好
				cur->_kv = Kv;//替换
			
			}
		}
		if (cur) {//重新计算高度
			cur->h = max(cur->_left ? cur->_left->h : 0, cur->_right ? cur->_right->h : 0) + 1;
		}
 
		return maintain(cur);//调整 cur 这颗树
	}
	void Erase(K key) {
		if (_root == nullptr) {
			return;
		}
		if (containsKey(key)) {
			--_size;
			_root = Delete(_root, key);
		}
	}
	//找到最离 key 最近的节点
	Node* findLastIndex(K key) {
 
		Node* pre = _root;//记录前一个节点
		Node* cur = _root;
		while (cur) {
			pre = cur;
			if (cur->_kv.first == key) {
				break;
			}
			else if (cur->_kv.first > key) {
				cur = cur->_left;
			}
			else {
				cur = cur->_left;
			}
		}
		return pre;
	}
	//找到离 key 最近的最小节点
	Node* findLastNoSmallIndex(K key) {
		Node* ans = nullptr;
		Node* cur = _root;
		while (cur) {
			if (cur->_kv.first == key) {
				ans = cur;
				break;
			}
			else if (cur->_kv.first > key) {
				ans = cur;
				cur = cur->_left;
			}
			else {
				cur = cur->_right;
			}
		}
		return ans;
	}
	//找到离 key 最近的最大节点
	Node* findLastNoBigIndex(K key) {
		Node* ans = nullptr;
		Node* cur = _root;
		while (cur) {
			if (cur->_kv.first == key) {
				ans = cur;
				break;
			}
			else if (cur->_kv.first > key) {
				cur = cur->_left;
			}
			else {
				ans = cur;
				cur = cur->_right;
			}
		}
		return ans;
	}
	//查找树中是否有 key 的这个节点
	public bool containsKey(K key) {
	if(_root==nullptr) {
			return false;
		}
	  Node* lastNode = findLastIndex(key);
		return lastNode && key==lastNode->_kv.first ? true : false;
	}
	
	int maxDepth(Node* root)//求高度
	{
		if (root == NULL)
		{
			return 0;
		}
		int leftDepth = maxDepth(root->_left);
		int rightDepth = maxDepth(root->_right);
		return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
	}
	bool _isBalanced(Node* root)//判断是否平衡
	{
		if (root == nullptr)
		{
			return true;
		}
		int leftHight = maxDepth(root->_left);
		int rightHight = maxDepth(root->_right);
		return abs(leftHight - rightHight) < 2
			&& _isBalanced(root->_left)
			&& _isBalanced(root->_right);
 
	}
 
	bool isBalanced()
	{
		return _isBalanced(_root);
 
	}
	void _Inorder(Node* root) {//中序遍历
		if (!root)
			return;
		_Inorder(root->_left);
		cout << root->_kv.first << ":" << root->_kv.second << endl;
		_Inorder(root->_right);
	}
	void Inorder() {
		_Inorder(_root);
	}
	size_t size() {
		return _size;
	}
	Node* rightRotate(Node* cur) {
		Node* left = cur->_left;
		cur->_left = left->_right;
		left->_right = cur;
		cur->h = max((cur->_left != nullptr ? cur->_left->h : 0), (cur->_right != nullptr ? cur->_right->h : 0)) + 1;//更新高度
		left->h = max((left->_left != nullptr ? left->_left->h : 0), (left->_right != nullptr ? left->_right->h : 0)) + 1;//更新高度
		return left;//返回新的头
	}
	Node* leftRotate(Node* cur) {
		Node* rightNode = cur->_right;
		cur->_right = rightNode->_left;
		rightNode->_left = cur;
		cur->h = max((cur->_left != nullptr ? cur->_left->h : 0), (cur->_right != nullptr ? cur->_right->h : 0)) + 1;//更新高度
		rightNode->h = max((rightNode->_left != nullptr ? rightNode->_left->h : 0), (rightNode->_right != nullptr ? rightNode->_right->h : 0)) + 1;//更新高度
		return rightNode;//
	}
 
	Node* maintain(Node* cur) {
		if (cur == nullptr) {
			return nullptr;
		}
		int leftHeight = cur->_left != nullptr ? cur->_left->h : 0;//计算出 cur 左树的高度
		int rightHeight = cur->_right != nullptr ? cur->_right->h : 0;//计算出 cur 右树的高度
		if (abs(leftHeight - rightHeight) > 1) {//出现不平衡
			if (leftHeight > rightHeight) {//如果是左树高
				//把左树的左右子树的高度来出来比较看到底是左边高还是右边高
				int leftLeftHeight = cur->_left != nullptr && cur->_left->_left != nullptr ? cur->_left->_left->h : 0;
				int leftRightHeight = cur->_left != nullptr && cur->_left->_right != nullptr ? cur->_left->_right->h : 0;
				if (leftLeftHeight >= leftRightHeight) {//注意想等时只能右旋
					cur = rightRotate(cur);
				}
				else {//左右双旋
					cur->_left = leftRotate(cur->_left);
					cur = rightRotate(cur);
				}
			}
			else {
				int rightLeftHeight = cur->_right != nullptr && cur->_right->_left != nullptr ? cur->_right->_left->h: 0;
				int rightRightHeight = cur->_right != nullptr && cur->_right->_right != nullptr ? cur->_right->_right->h : 0;
				if (rightRightHeight >= rightLeftHeight) {
					cur = leftRotate(cur);
				}
				else {//右左双旋
					cur->_right = rightRotate(cur->_right);
					cur = leftRotate(cur);
				}
			}
		}
		return cur;//返回调整好的新头
	}
	
 
	private:
		Node* _root = nullptr;
		int _size = 0;
	};

int main() {
    AVLTree<int, int> tree;
    tree.insert(make_pair(1, 1));
    tree.insert(make_pair(2, 2));
    tree.insert(make_pair(3, 3));
    tree.insert(make_pair(4, 4));
    tree.insert(make_pair(5, 5));
    tree.insert(make_pair(6, 6));
    tree.insert(make_pair(7, 7));
    tree.insert(make_pair(8, 8));
    tree.insert(make_pair(9, 9));
    tree.Inorder();
    cout << "size:" << tree.size() << endl;
    cout << "isBalanced:" << tree.isBalanced() << endl;
    tree.Erase(5);
    tree.Inorder();
    cout << "size:" << tree.size() << endl;
    cout << "isBalanced:" << tree.isBalanced() << endl;
    return 0;
}