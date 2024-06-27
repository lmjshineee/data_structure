#include<iostream>
using namespace std;	
int *p = 0;
void fun1(int *p){//对指针 p 指向的地址的内存单元进行操作，
	*p = 1;
}
void fun2(int *&p){//似乎和指针一样，都是对 p 指向的地址的内存单元进行操作
	*p = 2;
}
void fun3(int p){//传过来的是 p 的值，而不是 p 本身，
//这里的 p 是局部变量不会影响到主函数中 p 的值
	p = 3;
}
void fun4(int &p2){//传过来的是地址（&为取地址运算符），也可以理解为 p 的引用
//为方便区分这里将 p 的别名改为 p2，或者说 p2 是主函数中 p 的引用，对 p2 的操作就是对 p 的操作
	p2 = 4; 
} 
int main(){
	int tmp = 0;
	p = &tmp;
	cout<<"*p = "<<*p<<",tmp = "<<tmp<<endl;//*p = 0,tmp = 0
	
	tmp = 0,p = &tmp;//指针 p 指向的是 tmp 的地址，也就是 *p == tmp(*取内容)
	fun1(p);
	cout<<"*p = "<<*p<<",tmp = "<<tmp<<endl;//*p = 1,tmp = 1
	
	tmp = 0,p = &tmp;
	fun2(p);
	cout<<"*p = "<<*p<<",tmp = "<<tmp<<endl;//*p = 2,tmp = 2
	
	tmp = 0,p = &tmp;
	fun3(*p);
	cout<<"*p = "<<*p<<",tmp = "<<tmp<<endl;//*p = 0,tmp = 0
	
	tmp = 0,p = &tmp;
	fun4(*p);
	cout<<"*p = "<<*p<<",tmp = "<<tmp<<endl;//*p = 4,tmp = 4

}
