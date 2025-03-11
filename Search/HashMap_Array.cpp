#include <iostream>
#include <vector>

using namespace std;
typedef int ElemType;

/* 键值对 */
struct Pair {
  public:
    int key;
    string val;
    Pair(int key, string val) {
        this->key = key;
        this->val = val;
    }
};

/* 基于数组实现的哈希表 */
class ArrayHashMap {
  private:
    vector<Pair *> buckets;

  public:
    ArrayHashMap() {
        // 初始化数组，包含 100 个桶
        buckets = vector<Pair *>(100);
    }

    ~ArrayHashMap() {
        // 释放内存
        for (const auto &bucket : buckets) {
            delete bucket;
        }
        buckets.clear();
    }

    /* 哈希函数
       除留余数
     */
    int hashFunc(int key) {
        int index = key % 100;
        return index;
    }
    
    /* 直接定址法 */
    int hashFunc2(int key) {
        int index = 2 * key - 1;
        return index;
    }

    /* 数字分析法 */
    int hashFunc3(int key) {
        int index = key % 100;
        return index;
    }
    /* 平方取中法 */
    int hashFunc4(int key) {
        int square = key * key;
        string str = to_string(square);
        int len = str.length();
        int index = stoi(str.substr(len / 2 - 2, 4));
        return index;
    }


    /* 开放寻址法 */
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


    /* 查询操作 */
    string get(int key) {
        int index = hashFunc(key);
        Pair *pair = buckets[index];
        if (pair == nullptr)
            return "";
        return pair->val;
    }

    /* 添加操作 */
    void put(int key, string val) {
        Pair *pair = new Pair(key, val);
        int index = hashFunc(key);
        buckets[index] = pair;
    }

    /* 删除操作 */
    void remove(int key) {
        int index = hashFunc(key);
        // 释放内存并置为 nullptr
        delete buckets[index];
        buckets[index] = nullptr;
    }

    /* 获取所有键值对 */
    vector<Pair *> pairSet() {
        vector<Pair *> pairSet;
        for (Pair *pair : buckets) {
            if (pair != nullptr) {
                pairSet.push_back(pair);
            }
        }
        return pairSet;
    }

    /* 获取所有键 */
    vector<int> keySet() {
        vector<int> keySet;
        for (Pair *pair : buckets) {
            if (pair != nullptr) {
                keySet.push_back(pair->key);
            }
        }
        return keySet;
    }

    /* 获取所有值 */
    vector<string> valueSet() {
        vector<string> valueSet;
        for (Pair *pair : buckets) {
            if (pair != nullptr) {
                valueSet.push_back(pair->val);
            }
        }
        return valueSet;
    }

    /* 打印哈希表 */
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

