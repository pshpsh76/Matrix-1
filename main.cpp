#include <iostream>
#include <vector>
#include "Matrix.h"

using namespace std;

int main() {
    int choice;
    cout << "If you want to solve system of n linear equations with n unknowns enter '1'\n";
    cout << "If you want to calc inverse matrix enter '2'\n";
    cin >> choice;
    if (choice == 1) {
        int n;
        cout << "Enter num of equations\n";
        cin >> n;
        cout << "Enter equations\n";
        cout << "The first n terms in are the coefficients, then the value of the free term\n";
        vector<vector<double>> odds(n, vector<double>(1));
        Matrix<double> a(n, n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; i <= n; ++j) {
                if (j == n) {
                    cin >> odds[i][0];
                } else {
                    cin >> a[i][j];
                }
            }
        }
        Matrix<double> res = a.gauss(odds);
        cout << res;
    }
    if (choice == 2) {
        int n;
        cout << "Enter dimension of the Matrix\n";
        cin >> n;
        cout << "Enter elements of the Matrix\n";
        Matrix<double> a(n, n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> a[i][j];
            }
        }
        vector<vector<double>> odds(n, vector<double>(n));
        for (int i = 0; i < n; ++i) {
            odds[i][i] = 1;
        }
        Matrix<double> res = a.gauss(odds);
        cout << res;
    }
}
