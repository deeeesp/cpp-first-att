#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
    cout << "Введите размер массива \t";
    int n;
    int m;
    cin >> n;
    cin >> m;
    int A[n][m];
    int vector[n];
    for (int i = 0; i < n; ++i) {
        int sum = 0;
        for (int j = 0; j < m; ++j) {
            A[i][j] = rand() % 100;
            sum += A[i][j];
            cout << A[i][j] << " ";
        }
        vector[i] = sum;
        cout << endl;
    }
    for (int i = 0; i < n; ++i) {
        cout << vector[i] << " ";
    }
}
