#include <iostream>
#include "Matrix.h"

using namespace std;

int main() {
    int n, m;
    cout << "Input the dimensions of the first matrix "
            "(first the number of rows, then the number of columns): "<< endl;
    cin >> n >> m;
    Matrix<int> a(n, m);
    cout << "Input elements of the first matrix: " << endl;
    cin >> a;
    cout << "Input the dimensions of the second matrix "
            "(first the number of rows, then the number of columns): " << endl;
    cin >> n >> m;
    Matrix<int> b(n, m);
    cout << "Input elements of the second matrix: " << endl;
    cin >> b;
    int c;
    cout << "Input an integer for multiplication:" << endl;
    cin >> c;
    cout << "Input the degree to which you want to raise the first matrix" << endl;
    int k;
    cin >> k;
    try {
        cout << "Sum of two matrices: " << endl << (a + b);
    }
    catch (const char* msg) {
        cout << msg << endl;
    }
    cout << "First matrix multiplied by " << c << ':' << endl;
    cout << a * c;
    try {
        cout << "Multiplication of two matrices:" << endl << a * b;
    }
    catch  (const char* msg) {
        cout << msg << endl;
    }
    cout << "Transposed first matrix:" << endl << a.transpose();
    a.init_identity_matrix();
    try {
        cout << "First raised matrix:" << endl << a.pow(k);
    }
    catch (const char* msg) {
        cout << msg << endl;
    }
}
