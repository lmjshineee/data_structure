#include <iostream>
using namespace std;	
typedef int ElemType;	// ���� ElemType ����Ϊ int

typedef struct LNode {
    ElemType data;
    struct LNode* next;
}LNode, *LinkList;

