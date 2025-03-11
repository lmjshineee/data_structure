#include <iostream>

using namespace std;

// ϡ��������Ԫ��˳���洢��ʾ
const int MaxTerm = 100; // ������Ԫ�ظ���
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

    // ��ȡϡ����������
    int getRows() {
        return rows;
    }

    // ��ȡϡ����������
    int getCols() {
        return cols;
    }

    // ��ȡϡ�����ķ���Ԫ�ظ���
    int getCount() {
        return count;
    }

    // ��ȡϡ��������Ԫ���
    Triple *getData() {
        return data;
    }

    // ϡ�����->��ͨ����
    void transfrom(SparseMatrix<int> sparseMatrix, ElemType result[cols][rows]) {
        int rows = sparseMatrix.getRows();
        int cols = sparseMatrix.getCols();
        int count = sparseMatrix.getCount();
        Triple *data = sparseMatrix.getData();
        for (int i = 0; i < count; i++) {
            result[data[i].row][data[i].col] = data[i].value; 
        }
    }

    // ����˷�
    
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