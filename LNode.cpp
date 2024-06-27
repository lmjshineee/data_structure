#include <iostream>
using namespace std;	
typedef int ElemType;	// 定义 ElemType 类型为 int

typedef struct LNode {
    ElemType data;
    struct LNode* next;
}LNode, *LinkList;

