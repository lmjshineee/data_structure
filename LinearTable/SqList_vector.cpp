#include <iostream>
#include <cstdlib>  // ���� malloc, realloc, free
#include <stdexcept>  // �����쳣����

// ���嶯̬����Ľṹ��
struct DynamicArray {
    int* data;      // ָ��洢Ԫ�ص�����
    int size;       // ��ǰ������ʵ�ʴ洢��Ԫ������
    int capacity;   // ���������������������ʱ��Ҫ��չ��

    // ��ʼ������
    void init(int initial_capacity) {
        data = (int*)malloc(initial_capacity * sizeof(int));
        if (!data) throw std::bad_alloc();
        size = 0;
        capacity = initial_capacity;
    }

    // ���Ԫ�غ���������������˾���չ
    void add(int value) {
        if (size == capacity) {
            reserve(capacity * 2);
        }
        data[size++] = value;
    }

    // �ֶ���չ����
    void reserve(int new_capacity) {
        if (new_capacity > capacity) {
            data = (int*)realloc(data, new_capacity * sizeof(int));
            if (!data) throw std::bad_alloc();
            capacity = new_capacity;
        }
    }

    // ͨ���±����Ԫ��
    int& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // �����������
    void print() const {
        for (int i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    // ɾ�����һ��Ԫ��
    void pop_back() {
        if (size > 0) {
            size--;
        }
    }

    // �ͷ��ڴ�
    void freeMemory() {
        free(data);
    }
};

int main() {
    DynamicArray arr;
    arr.init(5);

    // ���Ԫ��
    for (int i = 1; i <= 10; ++i) {
        arr.add(i);
    }

    // �����������
    arr.print();

    // ʹ�� operator[] ����Ԫ��
    try {
        std::cout << "Element at index 2: " << arr[2] << std::endl;
        std::cout << "Element at index 20: " << arr[20] << std::endl;  // �⽫�׳��쳣
    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << std::endl;
    }

    // ɾ�����һ��Ԫ��
    arr.pop_back();
    arr.print();

    // �ͷ��ڴ�
    arr.freeMemory();

    return 0;
}
