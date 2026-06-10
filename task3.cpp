#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

const int SIZE = 4;
const double EPS = 1e-3;

// Вывод матрицы
void printMatrix(double A[SIZE][SIZE], double b[SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            cout << setw(10) << fixed << setprecision(5) << A[i][j] << " ";
        }
        cout << " | " << setw(10) << b[i] << endl;
    }
    cout << endl;
}

// Метод Гаусса с выбором главного элемента
void gaussMethod(double A[SIZE][SIZE], double b[SIZE])
{
    // Создаём копии, чтобы не изменять оригинал
    double mA[SIZE][SIZE];
    double mb[SIZE];
    
    for (int i = 0; i < SIZE; i++) {
        mb[i] = b[i];
        for (int j = 0; j < SIZE; j++) {
            mA[i][j] = A[i][j];
        }
    }
    
    double x[SIZE];
    cout << "МЕТОД ГАУССА С ВЫБОРОМ ГЛАВНОГО ЭЛЕМЕНТА" << endl;
    
    for (int i = 0; i < SIZE; i++)
    {
        // Выбор главного элемента (поиск максимального по модулю в столбце)
        int maxRow = i;
        double maxVal = fabs(mA[i][i]);
        for (int k = i + 1; k < SIZE; k++)
        {
            if (fabs(mA[k][i]) > maxVal)
            {
                maxVal = fabs(mA[k][i]);
                maxRow = k;
            }
        }
        
        // Перестановка строк
        if (maxRow != i)
        {
            for (int k = i; k < SIZE; k++)
            {
                swap(mA[i][k], mA[maxRow][k]);
            }
            swap(mb[i], mb[maxRow]);
        }
        
        cout << "Шаг " << i + 1 << " (после выбора главного элемента):" << endl;
        
        // Прямой ход (обнуление под главной диагональю)
        for (int j = i + 1; j < SIZE; j++)
        {
            double factor = mA[j][i] / mA[i][i];
            for (int k = i; k < SIZE; k++)
            {
                mA[j][k] -= factor * mA[i][k];
            }
            mb[j] -= factor * mb[i];
        }
        printMatrix(mA, mb);
    }
    
    // Обратный ход
    for (int i = SIZE - 1; i >= 0; i--)
    {
        x[i] = mb[i];
        for (int j = i + 1; j < SIZE; j++)
        {
            x[i] -= mA[i][j] * x[j];
        }
        x[i] /= mA[i][i];
    }
    
    cout << "Решение методом Гаусса:" << endl;
    for (int i = 0; i < SIZE; i++)
    {
        cout << "x" << i + 1 << " = " << fixed << setprecision(6) << x[i] << endl;
    }
    cout << endl;
}

// Метод простых итераций
void simpleIterationMethod(double A[SIZE][SIZE], double b[SIZE])
{
    cout << "МЕТОД ПРОСТЫХ ИТЕРАЦИЙ" << endl;
    
    // Проверка диагонального преобладания
    cout << "Проверка диагонального преобладания:" << endl;
    bool hasDiagonalDominance = true;
    for (int i = 0; i < SIZE; i++)
    {
        double sum = 0;
        for (int j = 0; j < SIZE; j++)
        {
            if (i != j)
                sum += fabs(A[i][j]);
        }
        if (fabs(A[i][i]) <= sum)
        {
            hasDiagonalDominance = false;
            cout << "Строка " << i + 1 << ": |" << A[i][i] << "| <= " << sum << " - диагональное преобладание НЕ выполняется" << endl;
        }
        else
        {
            cout << "Строка " << i + 1 << ": |" << A[i][i] << "| > " << sum << " - OK" << endl;
        }
    }
    cout << endl;
    
    // Приводим систему к виду x = C*x + d
    double C[SIZE][SIZE] = {0};
    double d[SIZE] = {0};
    
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (i != j)
            {
                C[i][j] = -A[i][j] / A[i][i];
            }
        }
        d[i] = b[i] / A[i][i];
    }
    
    double x[SIZE] = {0, 0, 0, 0};
    double newX[SIZE];
    int iteration = 0;
    
    cout << setw(5) << "N"
         << setw(12) << "x1"
         << setw(12) << "x2"
         << setw(12) << "x3"
         << setw(12) << "x4"
         << setw(12) << "eps" << endl;
    
    while (true)
    {
        for (int i = 0; i < SIZE; i++)
        {
            double sum = d[i];
            for (int j = 0; j < SIZE; j++)
            {
                sum += C[i][j] * x[j];
            }
            newX[i] = sum;
        }
        
        double error = 0;
        for (int i = 0; i < SIZE; i++)
        {
            error = max(error, fabs(newX[i] - x[i]));
        }
        
        iteration++;
        cout << setw(5) << iteration
             << setw(12) << fixed << setprecision(6) << newX[0]
             << setw(12) << newX[1]
             << setw(12) << newX[2]
             << setw(12) << newX[3]
             << setw(12) << error << endl;
        
        for (int i = 0; i < SIZE; i++)
        {
            x[i] = newX[i];
        }
        
        if (error < EPS)
        {
            break;
        }
        
        if (iteration > 1000)
        {
            cout << "Метод не сошёлся за 1000 итераций" << endl;
            break;
        }
    }
    
    cout << endl;
    cout << "Решение методом простых итераций:" << endl;
    for (int i = 0; i < SIZE; i++)
    {
        cout << "x" << i + 1 << " = " << fixed << setprecision(6) << x[i] << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    
    double M = 1.08;
    double N = 0.22;
    double P = -1.16;
    
    double A[SIZE][SIZE] = {
        {M, -0.4, 0.21, -1.16},
        {0.25, -1.23, N, -0.09},
        {-0.21, N, 0.8, -0.13},
        {0.15, -1.31, 0.06, P}
    };
    
    double b[SIZE] = {-1.24, P, 2.56, M};
    
    cout << "========================================" << endl;
    cout << "Вариант 16 (M = " << M << ", N = " << N << ", P = " << P << ")" << endl;
    cout << "========================================" << endl << endl;
    
    cout << "Исходная система:" << endl;
    printMatrix(A, b);
    
    gaussMethod(A, b);
    simpleIterationMethod(A, b);
    
    return 0;
}
