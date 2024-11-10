#include<iostream>
#include <cstring>
using namespace std;

int MAX_SIZE = 5000;
int MAX_MATRIX_CNT = 25;

class Matrix
{
private: 
    int n;
    int m;
    int** data;

public:
    char name;
    Matrix();
    Matrix(int n, int m);
    ~Matrix();

    friend ostream& operator << (ostream& out, const Matrix& mat);
    friend istream& operator >> (istream& in, Matrix& mat);
    Matrix operator + (const Matrix& mat);
    Matrix operator - (const Matrix& mat);
    Matrix operator * (const Matrix& mat);
    Matrix operator ! ();
    Matrix operator * (int num);
    bool isEmpty() const;

};

// constructor
Matrix::Matrix() : n(0), m(0), data(NULL) {}
Matrix::Matrix(int n, int m) : n(n), m(m) {
    this->data = new int*[n];
    for (int i = 0; i < n; i++) {
        this->data[i] = new int[m];
    }
}

// destructor
Matrix::~Matrix() {
    for (int i = 0; i < n; i++) {
        delete[] data[i];
    }
    delete[] data;
}

//加
Matrix Matrix::operator + (const Matrix& mat) {
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

//減
Matrix Matrix::operator - (const Matrix& mat) {
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

//與矩陣相乘
Matrix Matrix::operator * (const Matrix& mat) {
    if (m != mat.n) {
        return Matrix();
    }
    
    Matrix result(n, mat.m);  // 新矩陣的行數為 n，列數為 mat.m

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < mat.m; j++) {
            result.data[i][j] = 0;  // 初始化結果矩陣元素
            for (int k = 0; k < m; k++) {
                result.data[i][j] += this->data[i][k] * mat.data[k][j];
            }
        }
    }
    return result;
}

// 與數字相乘
Matrix Matrix::operator * (int num) {
    Matrix result(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result.data[i][j] = this->data[i][j] * num;
        }
    }
    return result;
}


//轉置
Matrix Matrix::operator ! () {
    Matrix result(m, n);  // 新矩陣的行數為 m，列數為 n

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result.data[j][i] = this->data[i][j];  // 行列互換
        }
    }

    return result;
}

//判斷為空
bool Matrix::isEmpty() const {
    return (n == 0 || m == 0 || data == nullptr);
}

int main()
{
    //輸入運算式
    char expression[MAX_SIZE];
    cin>>expression;

    //讀取運算式內的矩陣
    char matrix_list[MAX_MATRIX_CNT];
    int matrix_cnt = 0;
    int len = strlen(expression);

    for(int k=0;k<len;k++)
    {
        if(isdigit(expression[k]) && strchr(matrix_list, expression[k]) == nullptr) //是字母&&矩陣尚未被建立
        {
            matrix_list[matrix_cnt] = expression[k];
            matrix_cnt++;
        }
    }

    //輸入矩陣
    Matrix mat[matrix_cnt];
    for(int i=0;i<matrix_cnt;i++){
        cin >> mat[matrix_cnt];
    }

    //輸入向量
    Matrix vec;
    cin >> vec;

    //處理運算式(手刻stack)
    
    //先處理*和!
    
    //再處理+和-
    Matrix exp_res;

    //計算向量乘法
    Matrix result = exp_res*vec;

    //輸出結果
    if(result.isEmpty()) cout<<-1;
    else cout<<result;

    return 0;
}


//輸出矩陣
ostream& operator<<(ostream& out, const Matrix& mat)
{
    for (int i = 0; i < mat.m; i++) {
        for (int j = 0; j < mat.n; j++) {
            out << mat.data[i][j] << " ";
        }
        out << "\n";
    }

    return out;
}

// 輸入矩陣
istream& operator >> (istream& in, Matrix& mat) {

    // 釋放原本的記憶體
    for (int i = 0; i < mat.n; i++) {
            delete[] mat.data[i];
    }
    delete[] mat.data;

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

