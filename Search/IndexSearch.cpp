#include <iostream>
#include <vector>
#include <unordered_map>

class IndexedArray {
private:
    std::vector<int> array; // ˳���
    std::unordered_map<int, int> indexMap; // ������

public:
    // ���캯��
    IndexedArray(const std::vector<int>& input) {
        array = input;
        buildIndex();
    }

    // ����������
    void buildIndex() {
        for (size_t i = 0; i < array.size(); ++i) {
            indexMap[array[i]] = i; // �洢�ؼ��ּ���λ��
        }
    }

    // ��������
    int indexedSearch(int key) {
        if (indexMap.find(key) != indexMap.end()) {
            return indexMap[key]; // ���عؼ�����˳����е�λ��
        }
        return -1; // δ�ҵ�
    }

    // ��ӡ˳���
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

    std::cout << "˳���";
    indexedArray.printArray();

    int key = 30;
    int position = indexedArray.indexedSearch(key);
    
    if (position != -1) {
        std::cout << "�ؼ��� " << key << " ��˳����е�λ�ã�" << position << std::endl;
    } else {
        std::cout << "�ؼ��� " << key << " δ�ҵ���" << std::endl;
    }

    return 0;
}
