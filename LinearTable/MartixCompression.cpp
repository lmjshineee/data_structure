#include <iostream>

using namespace std;

// 稀疏矩阵的三元组顺序表存储表示
const int MaxTerm = 100; // 最大非零元素个数
template <typename ElemType>
class SparseMatrix {
private:
    struct Triple {
        int row, col;
        ElemType value;
    };
    Triple data[MaxTerm];
    int rows, cols, count;
public:
    SparseMatrix(int rows, int cols, int count) {
        this->rows = rows;
        this->cols = cols;
        this->count = count;
        data = new Triple[count];
    }

    ~SparseMatrix() {}

    void Construction(Triple *data, int rows, int cols, int count) {
        this->rows = rows;
        this->cols = cols;
        this->count = count;
        for (int i = 0; i < count; i++) {
            this->data[i] = data[i];
        }
    }

    // 获取稀疏矩阵的行数
    int getRows() {
        return rows;
    }

    // 获取稀疏矩阵的列数
    int getCols() {
        return cols;
    }

    // 获取稀疏矩阵的非零元素个数
    int getCount() {
        return count;
    }

    // 获取稀疏矩阵的三元组表
    Triple *getData() {
        return data;
    }

    // 稀疏矩阵->普通矩阵
    void transfrom(SparseMatrix<int> sparseMatrix, ElemType result[cols][rows]) {
        int rows = sparseMatrix.getRows();
        int cols = sparseMatrix.getCols();
        int count = sparseMatrix.getCount();
        Triple *data = sparseMatrix.getData();
        for (int i = 0; i < count; i++) {
            result[data[i].row][data[i].col] = data[i].value; 
        }
    }

    // 矩阵乘法
    
};



int main() {
    SparseMatrix<int> sparseMatrix(3, 3, 3);
    SparseMatrix<int>::Triple data[3] = {{0, 0, 1}, {1, 1, 2}, {2, 2, 3}};
    sparseMatrix.Construction(data, 3, 3, 3);
    int result[3][3] = SparseMatrix<int>::transfrom(sparseMatrix);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;    
    }
    return 0;
}