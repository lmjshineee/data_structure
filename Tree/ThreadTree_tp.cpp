#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
//#include <vld.h> //�����ڴ�й¶���
#include <list>
using namespace std;
 
template <typename T>
struct TreeNode
{
	T data;
	TreeNode* pleft, * pright;
	int ltag, rtag;
	TreeNode(const T& data = 0) 
		:data(data), pleft(nullptr), pright(nullptr),rtag(0),ltag(0) {}
	TreeNode(const T& data, TreeNode* pleft, TreeNode* pright, int ltag, int rtag)
		:data(data), pleft(pleft), pright(pright), ltag(ltag), rtag(rtag) {}
};
 
template <typename T = int>
class Tree
{
public:
	Tree();
	~Tree();
	void CreateTree(const T& val);
	//�����������
	void MidTravel();
	//�������������
	void rMidTravel();
	void CreateThreadTree();
	void destroyThreadTree();
	void destroyTree();
 
	//������������ĵ�һ���ڵ�
	TreeNode<T>* FindMidFirst();
	//�õ�������������һ���ڵ�
	TreeNode<T>* FindMidLast();
private:
	//�� P �ڵ������ǰ���ڵ�
	TreeNode<T>* PreNode(TreeNode<T>* p);
	//�� P �ڵ�������̽ڵ�
	TreeNode<T>* NextNode(TreeNode<T>* p);
	void _destroyTree(TreeNode<T>*& bt);
	void _midtavel();
	void _rmidtravel();
	void _createTree(TreeNode<T>*& root,const T& val);
	TreeNode<T>* _createThread_Tree(TreeNode<T>* bt);
	void _Thread(TreeNode<T>*& bt);
	void _destroyTH(TreeNode<T>*& bt);
private:
	TreeNode<T>* root;
	TreeNode<T>* pre;
};
 
int main()
{
	Tree<> a;
	int arr[]{ 1,2,5,4,1,9 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		a.CreateTree(arr[i]);
	}
	a.CreateThreadTree();
	auto beg =  a.FindMidFirst();
	auto end = a.FindMidLast();
	a.MidTravel();
	a.rMidTravel();
	return 0;
}
 
template<typename T>
Tree<T>::Tree()
{
	root = nullptr;
	pre = nullptr;
}
 
template<typename T>
Tree<T>::~Tree()
{
	if (pre == nullptr)
	{
		destroyTree();
	}
	else
	{
		destroyThreadTree();
	}
}
 
template<typename T>
void Tree<T>::CreateTree(const T&val)
{
	_createTree(root, val);
}
 
template<typename T>
void Tree<T>::MidTravel() 
{
	_midtavel();
}
 
template<typename T>
void Tree<T>::rMidTravel()
{
	_rmidtravel();
}
 
template<typename T>
void Tree<T>::CreateThreadTree()
{
	root = _createThread_Tree(root);
}
 
template<typename T>
void Tree<T>::destroyThreadTree()
{
	auto pNode = root->pleft;		//������һ���ڵ��λ��
	delete root;	//ɾ��ͷ�ڵ���ڴ�
	root = nullptr;
	_destroyTH(pNode);
	pre = nullptr;
}
 
template<typename T>
void Tree<T>::destroyTree()
{
	_destroyTree(root);
	root = nullptr;
}
 
template<typename T>
TreeNode<T>* Tree<T>::FindMidFirst()
{
	TreeNode<T>* begnode = root->pleft;
	while (begnode->ltag == 0)
	{
		begnode = begnode->pleft;
	}
	return begnode;
}
 
template<typename T>
TreeNode<T>* Tree<T>::FindMidLast()
{
	return root->pright;
}
 
template<typename T>
TreeNode<T>* Tree<T>::PreNode(TreeNode<T>* p)
{
	auto find = p->pleft;
	if (p->ltag != 1)
	{
		while (find->rtag == 0)
		{
			find = find->pright;
		}
	}
	return find;
}
 
template<typename T>
TreeNode<T>* Tree<T>::NextNode(TreeNode<T>* p)
{
	auto find = p->pright;
	if (p->rtag != 1)
	{
		while (find->ltag == 0)
		{
			find = find->pleft;
		}
	}
	return find;
}
 
template<typename T>
void Tree<T>::_destroyTree(TreeNode<T>*& bt)
{
	if (bt != nullptr)
	{
		_destroyTree(bt->pleft);
		_destroyTree(bt->pright);
		delete bt;
	}
}
 
template<typename T>
void Tree<T>::_midtavel()
{
	TreeNode<T>* node;
	node = FindMidFirst();
	while (node != root)
	{
		cout << node->data << " ";
		node = NextNode(node);
	}
	cout << endl;
}
 
template<typename T>
void Tree<T>::_rmidtravel()
{
	auto node = FindMidLast();
	while (node != root)
	{
		cout << node->data << " ";
		node = PreNode(node);
	}
	cout << endl;
}
 
template<typename T>
void Tree<T>::_createTree(TreeNode<T>*& root, const T& val)
{
	if (root == nullptr)
	{
		root = new TreeNode<T>{ val };
		return;
	}
	if (val <= root->data)
	{
		_createTree(root->pleft, val);
	}
	else
	{
		_createTree(root->pright, val);
	}
}
 
template<typename T>
TreeNode<T>* Tree<T>::_createThread_Tree(TreeNode<T>* bt)
{
	//����һ��ͷ�ڵ�
	TreeNode<T>* pHead = new TreeNode<T>{ 0,nullptr,bt,0,1 };
	if (bt == nullptr)
	{
		pHead->ltag = 0;
		pHead->pleft = pHead;
		pHead->rtag = 1;
		pHead->pright = nullptr;
	}
	else
	{
		//bt ��Ϊ����
		pHead->pleft = bt;
		pre = pHead;			//ǰ���ڵ�Ĭ��Ϊͷ�ڵ�
		_Thread(bt);	//��������
		//������pre ָ����ڵ�  ����ͷ�ڵ���ڵ������
		pHead->pright = pre;	
		pre->pright = pHead;
		pre->rtag = 1;				
	}
	//����ͷ�ڵ�
	return pHead;
}
 
template<typename T>
void Tree<T>::_Thread(TreeNode<T>*& bt)
{	
	if (bt != nullptr)
	{
		_Thread(bt->pleft);	//�ݹ��������������ʼ������
		//������
		if (bt->pleft == nullptr)
		{
			bt->pleft = pre;
			bt->ltag = 1;
		}
		else
		{
			bt->ltag = 0;
		}
		if (pre->pright == nullptr)
		{
			pre->pright = bt;
			pre->rtag = 1;
		}
		else
		{
			pre->rtag = 0;
		}
		//node.emplace_back(bt);
		pre = bt;
		_Thread(bt->pright);	//�ݹ��������������ʼ������
	}
}
 
template<typename T>
void Tree<T>::_destroyTH(TreeNode<T>*& bt)
{
	//��������Ϊ�գ��ݹ鵽���һ��������Ҷ�ӽڵ�
	if (bt->ltag == 0)
	{
		_destroyTH(bt->pleft);
	}
	//��������Ϊ�գ��ݹ鵽���һ��������Ҷ�ӽڵ�
	if (bt->rtag == 0)
	{
		_destroyTH(bt->pright);
	}
	delete bt;
	bt = nullptr;
}