#include <iostream>
#include <cstdlib>  // ���� malloc, realloc, free

// ���嶯̬����Ľṹ��
struct DynamicArray {
    int* data;      // ָ��洢Ԫ�ص�����
    int size;       // ��ǰ������ʵ�ʴ洢��Ԫ������
    int capacity;   // ���������������������ʱ��Ҫ��չ��

    // ��ʼ������
    void init(int initial_capacity) {
        data = (int*)malloc(initial_capacity * sizeof(int));
        size = 0;
        capacity = initial_capacity;
    }

    // ���Ԫ�أ������ӣ�����������������˾���չ
    void add(int value) {
        insert(size, value);
    }

    // �����������
    void print() {
        for (int i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    // ����Ԫ�غ��� (��ֵ����)������Ԫ�ص��±꣬����������򷵻� -1
    int find(int value) {
        for (int i = 0; i < size; ++i) {
            if (data[i] == value) {
                return i;
            }
        }
        return -1;
    }

    // ɾ��Ԫ�غ��� (��ֵɾ��)�������Ƿ�ɾ���ɹ�
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

    // ����Ԫ�غ��� (��λ�ò���)�������Ƿ����ɹ�
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

    // �ͷ��ڴ�
    void freeMemory() {
        free(data);
    }
};

int main() {
    // ����һ����̬���飬��ʼ����Ϊ 5
    DynamicArray arr;
    arr.init(5);

    // ���Ԫ��
    for (int i = 1; i <= 10; ++i) {
        arr.add(i);
    }

    arr.find(5) != -1 ? std::cout << "5 is found\n" : std::cout << "5 is not found\n";
    arr.remove(5);

    // �����ǰ���������
    arr.print();

    // �ͷ��ڴ�
    arr.freeMemory();

    return 0;
}
