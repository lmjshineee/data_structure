#include <iostream>
#include <vector>

using namespace std;
typedef int ElemType;

/* ��ֵ�� */
struct Pair {
  public:
    int key;
    string val;
    Pair(int key, string val) {
        this->key = key;
        this->val = val;
    }
};

/* ��������ʵ�ֵĹ�ϣ�� */
class ArrayHashMap {
  private:
    vector<Pair *> buckets;

  public:
    ArrayHashMap() {
        // ��ʼ�����飬���� 100 ��Ͱ
        buckets = vector<Pair *>(100);
    }

    ~ArrayHashMap() {
        // �ͷ��ڴ�
        for (const auto &bucket : buckets) {
            delete bucket;
        }
        buckets.clear();
    }

    /* ��ϣ����
       ��������
     */
    int hashFunc(int key) {
        int index = key % 100;
        return index;
    }
    
    /* ֱ�Ӷ�ַ�� */
    int hashFunc2(int key) {
        int index = 2 * key - 1;
        return index;
    }

    /* ���ַ����� */
    int hashFunc3(int key) {
        int index = key % 100;
        return index;
    }
    /* ƽ��ȡ�з� */
    int hashFunc4(int key) {
        int square = key * key;
        string str = to_string(square);
        int len = str.length();
        int index = stoi(str.substr(len / 2 - 2, 4));
        return index;
    }


    /* ����Ѱַ�� */
    void rehash() {
        vector<Pair *> oldBuckets = buckets;
        buckets = vector<Pair *>(buckets.size() * 2);
        for (const auto &bucket : oldBuckets) {
            if (bucket != nullptr) {
                int index = hashFunc(bucket->key);
                buckets[index] = bucket;
            }
        }
    }


    /* ��ѯ���� */
    string get(int key) {
        int index = hashFunc(key);
        Pair *pair = buckets[index];
        if (pair == nullptr)
            return "";
        return pair->val;
    }

    /* ��Ӳ��� */
    void put(int key, string val) {
        Pair *pair = new Pair(key, val);
        int index = hashFunc(key);
        buckets[index] = pair;
    }

    /* ɾ������ */
    void remove(int key) {
        int index = hashFunc(key);
        // �ͷ��ڴ沢��Ϊ nullptr
        delete buckets[index];
        buckets[index] = nullptr;
    }

    /* ��ȡ���м�ֵ�� */
    vector<Pair *> pairSet() {
        vector<Pair *> pairSet;
        for (Pair *pair : buckets) {
            if (pair != nullptr) {
                pairSet.push_back(pair);
            }
        }
        return pairSet;
    }

    /* ��ȡ���м� */
    vector<int> keySet() {
        vector<int> keySet;
        for (Pair *pair : buckets) {
            if (pair != nullptr) {
                keySet.push_back(pair->key);
            }
        }
        return keySet;
    }

    /* ��ȡ����ֵ */
    vector<string> valueSet() {
        vector<string> valueSet;
        for (Pair *pair : buckets) {
            if (pair != nullptr) {
                valueSet.push_back(pair->val);
            }
        }
        return valueSet;
    }

    /* ��ӡ��ϣ�� */
    void print() {
        for (Pair *kv : pairSet()) {
            cout << kv->key << " -> " << kv->val << endl;
        }
    }
};

int main(){
    ArrayHashMap map;
    map.put(1, "a");
    map.put(2, "b");
    map.put(3, "c");
    map.put(4, "d");
    map.put(5, "e");
    map.put(6, "f");
    map.put(7, "g");
    map.put(8, "h");
    map.put(9, "i");
    map.put(10, "j");
    map.print();
    map.remove(10);
    map.print();
    return 0;

}

