#include <cstring>
#include <iostream>
using namespace std;

int MAX_SIZE = 5000;
int MAX_MATRIX_CNT = 25;

class Matrix {
private:
    int n;
    int m;
    int** data;

public:
    char name;
    Matrix();
    Matrix(int n, int m);
    Matrix(const Matrix& mat);
    ~Matrix();

    friend ostream& operator<<(ostream& out, const Matrix& mat);
    friend istream& operator>>(istream& in, Matrix& mat);
    Matrix& operator=(const Matrix& mat);
    Matrix operator+(const Matrix& mat) const;
    Matrix operator-(const Matrix& mat) const;
    Matrix operator*(const Matrix& mat) const;
    Matrix operator*(int num) const;
    Matrix operator!() const;
    bool isEmpty() const;
};

// constructor
Matrix::Matrix() : n(0), m(0), data(nullptr) {}
Matrix::Matrix(int n, int m) : n(n), m(m) {
    this->data = new int*[n];
    for (int i = 0; i < n; i++) {
        this->data[i] = new int[m];
    }
}

// destructor
Matrix::~Matrix() {
    if (data) {
        for (int i = 0; i < n; i++) {
            if (data[i])
                delete[] data[i];
        }
        delete[] data;
    }
}

// copy constructor
Matrix::Matrix(const Matrix& mat) {
    n = mat.n;
    m = mat.m;
    data = new int*[n];
    for (int i = 0; i < n; i++) {
        data[i] = new int[m];
        for (int j = 0; j < m; j++) {
            data[i][j] = mat.data[i][j];
        }
    }
}

// copy assignment
Matrix& Matrix::operator=(const Matrix& mat) {
    if (this == &mat)
        return *this;

    // 釋放原本的記憶體
    if (data) {
        for (int i = 0; i < n; i++) {
            if (data[i])
                delete[] data[i];
        }
        delete[] data;
    }

    // 複製新的記憶體
    n = mat.n;
    m = mat.m;
    data = new int*[n];
    for (int i = 0; i < n; i++) {
        data[i] = new int[m];
        for (int j = 0; j < m; j++) {
            data[i][j] = mat.data[i][j];
        }
    }

    return *this;
}

// 加
Matrix Matrix::operator+(const Matrix& mat) const {
    if (n != mat.n || m != mat.m) {
        return Matrix();
    }
    Matrix result(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result.data[i][j] = this->data[i][j] + mat.data[i][j];
        }
    }
    return result;
}

// 減
Matrix Matrix::operator-(const Matrix& mat) const {
    if (n != mat.n || m != mat.m) {
        return Matrix();
    }
    Matrix result(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result.data[i][j] = this->data[i][j] - mat.data[i][j];
        }
    }
    return result;
}

// 與矩陣相乘
Matrix Matrix::operator*(const Matrix& mat) const {
    if (m != mat.n) {
        return Matrix();
    }

    Matrix result(n, mat.m); // 新矩陣的行數為 n，列數為 mat.m

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < mat.m; j++) {
            result.data[i][j] = 0; // 初始化結果矩陣元素
            for (int k = 0; k < m; k++) {
                result.data[i][j] += this->data[i][k] * mat.data[k][j];
            }
        }
    }
    return result;
}

// 與數字相乘
Matrix Matrix::operator*(int num) const {
    Matrix result(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result.data[i][j] = this->data[i][j] * num;
        }
    }
    return result;
}

// 轉置
Matrix Matrix::operator!() const {
    Matrix result(m, n); // 新矩陣的行數為 m，列數為 n

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result.data[j][i] = this->data[i][j]; // 行列互換
        }
    }

    return result;
}

// 判斷為空
bool Matrix::isEmpty() const { return (n == 0 || m == 0 || data == nullptr); }

int main() {

    // 輸入運算式
    char expression[MAX_SIZE];
    cin >> expression;

    // 讀取運算式內的矩陣
    char matrix_list[MAX_MATRIX_CNT];
    int matrix_index[256] = {0};
    int matrix_cnt = 0;
    int len = strlen(expression);

    for (int k = 0; k < len; k++) {
        if (isalpha(expression[k]) && strchr(matrix_list, expression[k]) ==
                                          nullptr) { // 是字母 && 矩陣尚未被建立
            matrix_list[matrix_cnt] = expression[k];
            matrix_index[expression[k]] = matrix_cnt;
            matrix_cnt++;
        }
    }

    // 輸入矩陣
    Matrix mat[matrix_cnt];
    for (int i = 0; i < matrix_cnt; i++) {
        cin >> mat[i];
    }

    // 輸入向量
    Matrix vec;
    cin >> vec;

    // 處理運算式
    // 先處理*和!
    int product_cnt = 0;
    Matrix product_terms[len];
    int multiply_const = 1;

    for (int i = 0; i < len; i++) {
        if (isdigit(expression[i])) {
            multiply_const *= expression[i] - '0';
        } else if (expression[i] == '+') {
            product_terms[product_cnt] =
                product_terms[product_cnt] * multiply_const;
            product_cnt++;
            multiply_const = 1;
        } else if (expression[i] == '-') {
            product_terms[product_cnt] =
                product_terms[product_cnt] * multiply_const;
            product_cnt++;
            multiply_const = -1;
        } else if (expression[i] == '!') {
            continue;
        } else {
            Matrix temp = mat[matrix_index[expression[i]]];

            if (i != len - 1 && expression[i + 1] == '!') {
                temp = !mat[matrix_index[expression[i]]];
            }

            if (product_terms[product_cnt].isEmpty()) {
                product_terms[product_cnt] = temp;
            } else {
                product_terms[product_cnt] = product_terms[product_cnt] * temp;
            }
        }
    }

    product_terms[product_cnt] = product_terms[product_cnt] * multiply_const;

    // 加起來
    Matrix exp_res = product_terms[0];
    for (int i = 1; i <= product_cnt; i++) {
        exp_res = exp_res + product_terms[i];
    }

    // 計算向量乘法
    Matrix result = exp_res * vec;

    // 輸出結果
    if (result.isEmpty())
        cout << -1 << endl;
    else
        cout << result;

    return 0;
}

// 輸出矩陣
ostream& operator<<(ostream& out, const Matrix& mat) {
    for (int i = 0; i < mat.n; i++) {
        for (int j = 0; j < mat.m - 1; j++) {
            out << mat.data[i][j] << " ";
        }
        out << mat.data[i][mat.m - 1];
        out << "\n";
    }

    return out;
}

// 輸入矩陣
istream& operator>>(istream& in, Matrix& mat) {

    // 釋放原本的記憶體
    if (mat.data) {
        for (int i = 0; i < mat.n; i++) {
            if (mat.data[i])
                delete[] mat.data[i];
        }
        delete[] mat.data;
    }

    in >> mat.name >> mat.n >> mat.m;

    // 建立新的記憶體
    mat.data = new int*[mat.n];
    for (int i = 0; i < mat.n; i++) {
        mat.data[i] = new int[mat.m];
    }

    // 輸入矩陣
    for (int i = 0; i < mat.n; i++) {
        for (int j = 0; j < mat.m; j++) {
            in >> mat.data[i][j];
        }
    }

    return in;
}