#include<iostream>
using namespace std;	
int *p = 0;
void fun1(int *p){//��ָ�� p ָ��ĵ�ַ���ڴ浥Ԫ���в�����
	*p = 1;
}
void fun2(int *&p){//�ƺ���ָ��һ�������Ƕ� p ָ��ĵ�ַ���ڴ浥Ԫ���в���
	*p = 2;
}
void fun3(int p){//���������� p ��ֵ�������� p ����
//����� p �Ǿֲ���������Ӱ�쵽�������� p ��ֵ
	p = 3;
}
void fun4(int &p2){//���������ǵ�ַ��&Ϊȡ��ַ���������Ҳ�������Ϊ p ������
//Ϊ�����������ｫ p �ı�����Ϊ p2������˵ p2 ���������� p �����ã��� p2 �Ĳ������Ƕ� p �Ĳ���
	p2 = 4; 
} 
int main(){
	int tmp = 0;
	p = &tmp;
	cout<<"*p = "<<*p<<",tmp = "<<tmp<<endl;//*p = 0,tmp = 0
	
	tmp = 0,p = &tmp;//ָ�� p ָ����� tmp �ĵ�ַ��Ҳ���� *p == tmp(*ȡ����)
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
