#include <iostream>
#include <cstdlib>  // 包含 malloc, realloc, free

// 定义动态数组的结构体
struct DynamicArray {
    int* data;      // 指向存储元素的数组
    int size;       // 当前数组中实际存储的元素数量
    int capacity;   // 数组的总容量（容量不足时需要扩展）

    // 初始化函数
    void init(int initial_capacity) {
        data = (int*)malloc(initial_capacity * sizeof(int));
        size = 0;
        capacity = initial_capacity;
    }

    // 添加元素（在最后加）函数，如果数组满了就扩展
    void add(int value) {
        insert(size, value);
    }

    // 输出数组内容
    void print() {
        for (int i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    // 查找元素函数 (按值查找)，返回元素的下标，如果不存在则返回 -1
    int find(int value) {
        for (int i = 0; i < size; ++i) {
            if (data[i] == value) {
                return i;
            }
        }
        return -1;
    }

    // 删除元素函数 (按值删除)，返回是否删除成功
    bool remove(int value) {
        int pos = find(value);
        if (pos == -1) {
            return false;
        }
        for (int i = pos; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        size--;
        return true;
    }

    // 插入元素函数 (按位置插入)，返回是否插入成功
    bool insert(int pos, int value) {
        if (pos < 0 || pos > size) {
            return false;
        }
        if (size == capacity) {
            capacity *= 2;
            data = (int*)realloc(data, capacity * sizeof(int));
        }
        for (int i = size; i > pos; --i) {
            data[i] = data[i - 1];
        }
        data[pos] = value;
        size++;
        return true;
    }

    // 释放内存
    void freeMemory() {
        free(data);
    }
};

int main() {
    // 创建一个动态数组，初始容量为 5
    DynamicArray arr;
    arr.init(5);

    // 添加元素
    for (int i = 1; i <= 10; ++i) {
        arr.add(i);
    }

    arr.find(5) != -1 ? std::cout << "5 is found\n" : std::cout << "5 is not found\n";
    arr.remove(5);

    // 输出当前数组的内容
    arr.print();

    // 释放内存
    arr.freeMemory();

    return 0;
}
