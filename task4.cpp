#include <iostream>
#include <vector>

using namespace std;

void makePattern(vector<vector<int>>& pattern, int N, int M, int start) {
    pattern = vector<vector<int>>(N, vector<int>(M)); // создаем пустой рисунок NxM
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (i == 0 || i == N - 1 || j == 0 || j == N - 1) { // если является границей справа, слева, сверху или снизу (рамка)
                pattern[i][j] = start;
            }
            else { // если находится внутри
                pattern[i][j] = (start + 1) % 2;
            }
        }
    }
}

int countMoves(vector<vector<int>> board, vector<vector<int>>& target, int N, int M) {
    int moves = 0; // счетчик ходов

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (board[i][j] != target[i][j]) { // если текущая клетка не совпадает с шаблоном
                moves++; // увеличиваем счетчик ходов
                board[i][j] = 1 - board[i][j]; // переворачиваем текущую клетку

                // переворачиваем соседнюю клетку справа, если она существует и не совпадает с шаблоном
                if (j + 1 < M && board[i][j + 1] != target[i][j + 1])
                    board[i][j + 1] = 1 - board[i][j + 1];
                // иначе переворачиваем соседнюю клетку снизу, если она существует и не совпадает с шаблоном
                else if (i + 1 < N && board[i + 1][j] != target[i + 1][j])
                    board[i + 1][j] = 1 - board[i + 1][j];
                // иначе переворачиваем клетку справа (даже если она уже совпадает с шаблоном)
                else if (j + 1 < M)
                    board[i][j + 1] = 1 - board[i][j + 1];
                else { // если нет доступных соседей для переворота
                    return 999999; // возвращаем большое число (невозможно)
                }
            }
        }
    }

    // проверяем, совпадает ли итоговая доска с шаблоном
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (board[i][j] != target[i][j])
                return 999999; // если не совпадает с шаблоном - невозможно

    return moves; // возвращаем количество ходов
}

void printBoard(vector<vector<int>>& board, int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << board[i][j];
            if (j < M - 1) cout << " "; // выводим пробел между элементами, кроме последнего
        }
        cout << endl; // переходим на новую строку после каждой строки доски
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    int N, M;

    cout << "Введите размеры доски (N M): ";
    cin >> N >> M;

    vector<vector<int>> board(N, vector<int>(M));
    cout << "Введите доску: " << endl;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> board[i][j]; // считываем начальное состояние доски

    // создаем два паттерна: начинающийся с 0 и с 1
    vector<vector<int>> pattern1, pattern2;
    makePattern(pattern1, N, M, 0); // паттерн, где рамка начинается с 0
    makePattern(pattern2, N, M, 1); // паттерн, где рамка начинается с 1

    // считаем минимальное количество ходов для каждого паттерна
    int moves1 = countMoves(board, pattern1, N, M);
    int moves2 = countMoves(board, pattern2, N, M);

    cout << "паттерн (начинается с 0):" << endl;
    printBoard(pattern1, N, M); // выводим первый паттерн

    cout << "Нужно ходов: ";
    if (moves1 >= 999999)
        cout << "невозможно" << endl; // если moves1 большое - невозможно
    else
        cout << moves1 << endl; // иначе выводим количество ходов

    cout << "паттерн (начинается с 1):" << endl;
    printBoard(pattern2, N, M); // выводим второй паттерн
    cout << "Нужно ходов: ";
    if (moves2 >= 999999)
        cout << "невозможно" << endl;
    else
        cout << moves2 << endl;

    cout << "Минимальное количество ходов: ";
    int minMoves = min(moves1, moves2); // выбираем минимальное из двух
    if (minMoves >= 999999)
        cout << "невозможно" << endl; // если оба невозможны
    else
        cout << minMoves << endl; // выводим минимальное количество ходов

    return 0;
}
