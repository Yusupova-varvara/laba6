#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void task1() {
    cout << "Задание 1" << endl << endl;
    int M, N;
    cout << "Введите M: ";
    cin >> M;
    cout << endl << "Введите N: ";
    cin >> N;
    cout << endl;

    vector<vector<int>> matrix(M, vector<int>(N));
    srand(time(0));

    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            matrix[i][j] = rand() % 101;

    cout << "Полученная матрица:" << endl;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j)
            cout << matrix[i][j] << " ";
        cout << endl;
    }

    vector<int> localMax;

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            int val = matrix[i][j];
            bool isMax = true;

            if (i > 0 && matrix[i - 1][j] >= val)
                isMax = false;
            if (i < M - 1 && matrix[i + 1][j] >= val)
                isMax = false;
            if (j > 0 && matrix[i][j - 1] >= val)
                isMax = false;
            if (j < N - 1 && matrix[i][j + 1] >= val)
                isMax = false;

            if (isMax)
                localMax.push_back(val);
        }
    }

    cout << "Локальные максимумы: " << endl;
    if (localMax.empty()) {
        cout << "Локальных максимумов нет ";
    }
    else {
        double sum = 0;
        for (int v : localMax) {
            sum += v;
            cout << v << " ";
        }
        cout << endl << "Среднее значение: " << sum / localMax.size() << endl << endl;
    }
}

void task2() {
    cout << "Задание 2" << endl << endl;
    int N;
    cout << "Введите N: ";
    cin >> N;
    cout << endl;

    vector<vector<int>> matrix(N, vector<int>(N));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i == j) {
                matrix[i][j] = 0;  // главная диагональ
            }
            else if (i == 0) {
                // Первая строка: убывание от N-1 к 0
                matrix[i][j] = 100 + (N - j);
            }
            else if (j == N - 1) {
                // Последний столбец: все 100
                matrix[i][j] = 100;
            }
            else if (i > j) {
                // Нижняя треугольная часть
                matrix[i][j] = 100 + j + (i > j + 1 ? 0 : 1);
            }
            else {
                // Верхняя треугольная часть (i < j)
                matrix[i][j] = 100 + (N - j);
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i > j && j > 0 && i > j + 1) {
                matrix[i][j] = 100 + j;
            }
            if (i == N - 1 && j == N - 2) {
                matrix[i][j] = 100 + (N - 2);
            }
        }
    }

    cout << "Результат:" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (matrix[i][j] == 0)
                cout << "000 ";
            else
                cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
}

void task3() {
    cout << "Задание 3" << endl << endl;
    int N;
    cout << "Введите N (3-10): " << endl;
    do {
        cin >> N;
        if (N < 3 || N > 10) {
            cout << "Ошибка число может быть от 3 до 10" << endl;
        }
    } while (N < 3 || N > 10);

    vector<vector<int>> spiral(N, vector<int>(N, 0));

    int value = 1;
    int top = 0, bottom = N - 1, left = 0, right = N - 1;

    while (value <= N * N) {
        for (int i = left; i <= right; ++i)
            spiral[top][i] = value++;
        top++;

        for (int i = top; i <= bottom; ++i)
            spiral[i][right] = value++;
        right--;

        for (int i = right; i >= left; --i)
            spiral[bottom][i] = value++;
        bottom--;

        for (int i = bottom; i >= top; --i)
            spiral[i][left] = value++;
        left++;
    }

    cout << "Полученная спираль: " << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            cout << spiral[i][j] << "\t";
        cout << endl;
    }
}

int main() {
    task1();
    task2();
    task3();
    return 0;
}
