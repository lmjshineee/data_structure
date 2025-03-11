#include <iostream>
#include <vector>
#include <unordered_map>

class IndexedArray {
private:
    std::vector<int> array; // 顺序表
    std::unordered_map<int, int> indexMap; // 索引表

public:
    // 构造函数
    IndexedArray(const std::vector<int>& input) {
        array = input;
        buildIndex();
    }

    // 构建索引表
    void buildIndex() {
        for (size_t i = 0; i < array.size(); ++i) {
            indexMap[array[i]] = i; // 存储关键字及其位置
        }
    }

    // 索引查找
    int indexedSearch(int key) {
        if (indexMap.find(key) != indexMap.end()) {
            return indexMap[key]; // 返回关键字在顺序表中的位置
        }
        return -1; // 未找到
    }

    // 打印顺序表
    void printArray() {
        for (int value : array) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    std::vector<int> inputArray = {10, 20, 30, 40, 50};
    IndexedArray indexedArray(inputArray);

    std::cout << "顺序表：";
    indexedArray.printArray();

    int key = 30;
    int position = indexedArray.indexedSearch(key);
    
    if (position != -1) {
        std::cout << "关键字 " << key << " 在顺序表中的位置：" << position << std::endl;
    } else {
        std::cout << "关键字 " << key << " 未找到。" << std::endl;
    }

    return 0;
}
