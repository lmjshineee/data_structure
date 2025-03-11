#include<iostream>
using namespace std;

template<class K,class V>
struct AVLTreeNode {
		AVLTreeNode(const pair<K,V>&kv)
			:_left(nullptr)
			,_right(nullptr)
			,_kv(kv)
			,h(1)//һ���ڵ�ĸ߶�Ϊ 1
		{}
 
		AVLTreeNode<K, V>* _left;//��ָ��
		AVLTreeNode<K, V>* _right;//��ָ��
		pair<K, V> _kv;
		int h;//�߶�
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
		if (cur == nullptr) {//����ֱ�� new ���ڵ㲢����
			return new Node(kv);
		}
		else {
			if (cur->_kv.first < kv.first) {//�ȵ�ǰ�ڵ��
				cur->_right = add(cur->_right, kv);//ȥ cur ���ұ߲��벢���µ�ͷ������
			}
 
			else {
				cur->_left = add(cur->_left, kv);//ȥ cur ����߲��벢���µ�ͷ������
			}
			cur->h = max(cur->_left != nullptr ? cur->_left->h : 0, cur->_right != nullptr ? cur->_right->h : 0)+1;//���¼���߶�
			return maintain(cur);//�� cur ��������е���
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
			cur->_right = Delete(cur->_right, key);//ȥ�ҵ��ұ�ɾ�����ҷ����µ�ͷ��
		}
		else if (cur->_kv.first > key) {
			cur->_left = Delete(cur->_left, key);//ȥ�ҵ����ɾ���������µ�ͷ��
		}
		else {
			if (cur->_left==nullptr && cur->_right==nullptr) {//Ҷ�ӽڵ����Ҷ�Ϊ��
				delete cur;
				return nullptr;
				
			}
			else if (!cur->_left && cur->_right) {//��Ϊ�յ��Ҳ�Ϊ��
				Node* subR = cur->_right;
				delete cur;
				cur = subR;
			}
			else if (cur->_left && !cur->_right) {//��Ϊ�յ���Ϊ��
				Node* subL = cur->_left;
				delete cur;
				cur = subL;
			}
			else {//���Ҷ���Ϊ�ղ����滻��ɾ���Ȳ���ֵ�ķ�ʽ���
				Node* des = cur->_right;//�ҵ���������ڵ�����ҵ����������ҽڵ㶼����
				while (des->_left)
				{
					des = des->_left;
				}
				pair<K, V>Kv = des->_kv;//��¼��Ӧ��ֵ
				cur->_right = Delete(cur->_right, des->_kv.first);//�ҵ����Ȳ�ɾ���� Delete �� des ɾ��������������
				cur->_kv = Kv;//�滻
			
			}
		}
		if (cur) {//���¼���߶�
			cur->h = max(cur->_left ? cur->_left->h : 0, cur->_right ? cur->_right->h : 0) + 1;
		}
 
		return maintain(cur);//���� cur �����
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
	//�ҵ����� key ����Ľڵ�
	Node* findLastIndex(K key) {
 
		Node* pre = _root;//��¼ǰһ���ڵ�
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
	//�ҵ��� key �������С�ڵ�
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
	//�ҵ��� key ��������ڵ�
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
	//���������Ƿ��� key ������ڵ�
	public bool containsKey(K key) {
	if(_root==nullptr) {
			return false;
		}
	  Node* lastNode = findLastIndex(key);
		return lastNode && key==lastNode->_kv.first ? true : false;
	}
	
	int maxDepth(Node* root)//��߶�
	{
		if (root == NULL)
		{
			return 0;
		}
		int leftDepth = maxDepth(root->_left);
		int rightDepth = maxDepth(root->_right);
		return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
	}
	bool _isBalanced(Node* root)//�ж��Ƿ�ƽ��
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
	void _Inorder(Node* root) {//�������
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
		cur->h = max((cur->_left != nullptr ? cur->_left->h : 0), (cur->_right != nullptr ? cur->_right->h : 0)) + 1;//���¸߶�
		left->h = max((left->_left != nullptr ? left->_left->h : 0), (left->_right != nullptr ? left->_right->h : 0)) + 1;//���¸߶�
		return left;//�����µ�ͷ
	}
	Node* leftRotate(Node* cur) {
		Node* rightNode = cur->_right;
		cur->_right = rightNode->_left;
		rightNode->_left = cur;
		cur->h = max((cur->_left != nullptr ? cur->_left->h : 0), (cur->_right != nullptr ? cur->_right->h : 0)) + 1;//���¸߶�
		rightNode->h = max((rightNode->_left != nullptr ? rightNode->_left->h : 0), (rightNode->_right != nullptr ? rightNode->_right->h : 0)) + 1;//���¸߶�
		return rightNode;//
	}
 
	Node* maintain(Node* cur) {
		if (cur == nullptr) {
			return nullptr;
		}
		int leftHeight = cur->_left != nullptr ? cur->_left->h : 0;//����� cur �����ĸ߶�
		int rightHeight = cur->_right != nullptr ? cur->_right->h : 0;//����� cur �����ĸ߶�
		if (abs(leftHeight - rightHeight) > 1) {//���ֲ�ƽ��
			if (leftHeight > rightHeight) {//�����������
				//�����������������ĸ߶��������ȽϿ���������߸߻����ұ߸�
				int leftLeftHeight = cur->_left != nullptr && cur->_left->_left != nullptr ? cur->_left->_left->h : 0;
				int leftRightHeight = cur->_left != nullptr && cur->_left->_right != nullptr ? cur->_left->_right->h : 0;
				if (leftLeftHeight >= leftRightHeight) {//ע�����ʱֻ������
					cur = rightRotate(cur);
				}
				else {//����˫��
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
				else {//����˫��
					cur->_right = rightRotate(cur->_right);
					cur = leftRotate(cur);
				}
			}
		}
		return cur;//���ص����õ���ͷ
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