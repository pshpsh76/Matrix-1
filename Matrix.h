#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <iostream>
#include <vector>

using namespace std;

template<typename T>

class Matrix {
    int n, m, cnt;
    vector<vector<T>> data;
    vector<vector<T>> identity_matrix;
public:
    void init_identity_matrix();
    Matrix(int _n, int _m);
    Matrix(vector<vector<T>>&);
    const Matrix operator+(const Matrix&) const;
    const Matrix operator*(T) const;
    const Matrix operator*(const Matrix&) const;
    const Matrix pow(int);
    const Matrix transpose() const;
    const T determinant();
    Matrix gauss(vector<vector<T>>&);
    vector<T>& operator[](int i) { return (data[i]); };
    const vector<T>& operator[](int i) const { return (data[i]); };
    template<typename Type> friend istream& operator>>(istream&, Matrix<Type>&);
    template<typename Type> friend ostream& operator<<(ostream&, const Matrix<Type>&);
};

template<typename T>

void Matrix<T>::init_identity_matrix() {
    identity_matrix.resize(n, vector<T>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i == j) {
                identity_matrix[i][j] = 1;
            }
        }
    }
}

template<typename T>
Matrix<T>::Matrix(int _n, int _m) {
    n = _n;
    m = _m;
    data.resize(n, vector<T>(m));
}

template<typename T>
const Matrix<T> Matrix<T>::operator+(const Matrix& a) const {
    if (a.m != this->m || a.n != this->n) {
        throw "Matrices are of different sizes";
    }
    vector<vector<T>> res(n, vector<T>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            res[i][j] = data[i][j] + a.data[i][j];
        }
    }
    return Matrix(res);
}

template<typename T>
const Matrix<T> Matrix<T>::operator*(T c) const {
    vector<vector<T>> res(n, vector<T>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            res[i][j] = data[i][j] * c;
        }
    }
    return Matrix(res);
}

template<typename T>
const Matrix<T> Matrix<T>::operator*(const Matrix& a) const {
    if (m != a.n) {
        throw "The product of matrices for the given sizes is undefined";
    }
    vector<vector<T>> res(n, vector<T>(a.m));
    int k = a.n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < a.m; ++j) {
            T sum = 0;
            for (int x = 0; x < k; ++x) {
                sum += data[i][x] * a.data[x][j];
            }
            res[i][j] = sum;
        }
    }
    return Matrix(res);
}

template<typename Type>
istream &operator>>(istream &in, Matrix<Type> &a) {
    for (int i = 0; i < a.n; ++i) {
        for (int j = 0; j < a.m; ++j) {
            in >> a[i][j];
        }
    }
    return in;
}

template<typename Type>
ostream &operator<<(ostream &out, const Matrix<Type> &a) {
    for (int i = 0; i < a.n; ++i) {
        for (int j = 0; j < a.m; ++j) {
            out << a[i][j] << '\t';
        }
        out << endl;
    }
    return out;
}

template<typename T>
const Matrix<T> Matrix<T>::pow(int k) {
    if (n != m) {
        throw "You can't exponentiate this matrix";
    }
    if (k == 0) {
        return Matrix(identity_matrix);
    }
    else if (k % 2 == 1) {
        return  this->pow(k - 1) * Matrix(data);
    }
    else {
        Matrix<T> temp = this->pow(k / 2);
        return temp * temp;
    }
}

template<typename T>
Matrix<T>::Matrix(vector<vector<T>>& vect) {

    data = vect;
    n = vect.size();
    if (n != 0) m = vect[0].size();
    else m = 0;
}

template<typename T>
const Matrix<T> Matrix<T>::transpose() const {
    vector<vector<T>> res(m, vector<T>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            res[j][i] = data[i][j];
        }
    }
    return Matrix(res);
}

template<typename T>
const T Matrix<T>::determinant() {
    if (n != m) {
        throw "You can't calc the determinant of a non-square matrix";
    }
    if (n == 1) {
        return data[0][0];
    }
    T sum = 0;
    for (int x = 0; x < n; ++x) {
        vector<vector<T>> copy = data;
        copy.erase(copy.begin());
        for (int y = 0; y < n - 1; ++y) {
            copy[y].erase(copy[y].begin() + x);
        }
        Matrix<T> add = Matrix(copy);
        T temp = add.determinant();
        if (x % 2 == 0) {
            sum += data[0][x] * temp;
        }
        else {
            sum -= data[0][x] * temp;
        }
    }
    return sum;
}

template<typename T>
Matrix<T> Matrix<T>::gauss(vector<vector<T>>& odds) {
    if (n != m) {
        throw "You can't use the gauss method to non-square matrix";
    }
    bool inverse = false;
    init_identity_matrix();
    if (odds == identity_matrix) {
        inverse = true;
    }
    for (int i = 0; i < n - 1; ++i) {
        if (data[i][i] == 0) {
            throw "The matrix is degenerate";
        }
        for (int j = i + 1; j < n; ++j) {
            double k = data[j][i] / data[i][i];
            for (int x = 0; x < n; ++x) {
                data[j][x] = data[j][x] - data[i][x] * k;
                if (inverse) {
                    odds[j][x] = odds[j][x] - odds[i][x] * k;
                }
            }
            if (!inverse) {
                odds[j][0] = odds[j][0] - odds[i][0] * k;
            }
        }
    }
    for (int i = n - 1; i > 0; --i) {
        if (data[i][i] == 0) {
            throw "The matrix is degenerate";
        }
        for (int j = i - 1; j > -1; --j) {
            double k = data[j][i] / data[i][i];
            for (int x = 0; x < n; ++x) {
                data[j][x] = data[j][x] - data[i][x] * k;
                if (inverse) {
                    odds[j][x] = odds[j][x] - odds[i][x] * k;
                }
            }
            if (!inverse) {
                odds[j][0] = odds[j][0] - odds[i][0] * k;
            }
        }
    }
    if (!inverse) {
        for (int i = 0; i < n; ++i) {
            odds[i][0] = odds[i][0] / data[i][i];
        }
        return Matrix(odds);
    } else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                odds[i][j] /= data[i][i];
            }
        }
        return Matrix(odds);
    }
}


#endif //MATRIX_MATRIX_H
