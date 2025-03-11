#include <iostream>
#include <cstdlib>  // 包含 malloc, realloc, free
#include <stdexcept>  // 包含异常处理

// 定义动态数组的结构体
struct DynamicArray {
    int* data;      // 指向存储元素的数组
    int size;       // 当前数组中实际存储的元素数量
    int capacity;   // 数组的总容量（容量不足时需要扩展）

    // 初始化函数
    void init(int initial_capacity) {
        data = (int*)malloc(initial_capacity * sizeof(int));
        if (!data) throw std::bad_alloc();
        size = 0;
        capacity = initial_capacity;
    }

    // 添加元素函数，如果数组满了就扩展
    void add(int value) {
        if (size == capacity) {
            reserve(capacity * 2);
        }
        data[size++] = value;
    }

    // 手动扩展容量
    void reserve(int new_capacity) {
        if (new_capacity > capacity) {
            data = (int*)realloc(data, new_capacity * sizeof(int));
            if (!data) throw std::bad_alloc();
            capacity = new_capacity;
        }
    }

    // 通过下标访问元素
    int& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // 输出数组内容
    void print() const {
        for (int i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    // 删除最后一个元素
    void pop_back() {
        if (size > 0) {
            size--;
        }
    }

    // 释放内存
    void freeMemory() {
        free(data);
    }
};

int main() {
    DynamicArray arr;
    arr.init(5);

    // 添加元素
    for (int i = 1; i <= 10; ++i) {
        arr.add(i);
    }

    // 输出数组内容
    arr.print();

    // 使用 operator[] 访问元素
    try {
        std::cout << "Element at index 2: " << arr[2] << std::endl;
        std::cout << "Element at index 20: " << arr[20] << std::endl;  // 这将抛出异常
    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << std::endl;
    }

    // 删除最后一个元素
    arr.pop_back();
    arr.print();

    // 释放内存
    arr.freeMemory();

    return 0;
}
