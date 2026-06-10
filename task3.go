package main

import (
	"fmt"
	"math"
	"os"
	"text/tabwriter"
)

const size = 4
const eps = 1e-3

// Вывод матрицы
func printMatrix(A [size][size]float64, b [size]float64) {
	for i := 0; i < size; i++ {
		for j := 0; j < size; j++ {
			fmt.Printf("%10.5f ", A[i][j])
		}
		fmt.Printf("| %10.5f\n", b[i])
	}
	fmt.Println()
}

// Метод Гаусса с выбором главного элемента
func gaussMethod(A [size][size]float64, b [size]float64) {
	// Создаём копии
	var mA [size][size]float64
	var mb [size]float64

	for i := 0; i < size; i++ {
		mb[i] = b[i]
		for j := 0; j < size; j++ {
			mA[i][j] = A[i][j]
		}
	}

	var x [size]float64
	fmt.Println("МЕТОД ГАУССА С ВЫБОРОМ ГЛАВНОГО ЭЛЕМЕНТА")

	for i := 0; i < size; i++ {
		// Выбор главного элемента
		maxRow := i
		maxVal := math.Abs(mA[i][i])
		for k := i + 1; k < size; k++ {
			if math.Abs(mA[k][i]) > maxVal {
				maxVal = math.Abs(mA[k][i])
				maxRow = k
			}
		}

		// Перестановка строк
		if maxRow != i {
			for k := i; k < size; k++ {
				mA[i][k], mA[maxRow][k] = mA[maxRow][k], mA[i][k]
			}
			mb[i], mb[maxRow] = mb[maxRow], mb[i]
		}

		fmt.Printf("Шаг %d (после выбора главного элемента):\n", i+1)

		// Прямой ход
		for j := i + 1; j < size; j++ {
			factor := mA[j][i] / mA[i][i]
			for k := i; k < size; k++ {
				mA[j][k] -= factor * mA[i][k]
			}
			mb[j] -= factor * mb[i]
		}
		printMatrix(mA, mb)
	}

	// Обратный ход
	for i := size - 1; i >= 0; i-- {
		x[i] = mb[i]
		for j := i + 1; j < size; j++ {
			x[i] -= mA[i][j] * x[j]
		}
		x[i] /= mA[i][i]
	}

	fmt.Println("Решение методом Гаусса:")
	for i := 0; i < size; i++ {
		fmt.Printf("x%d = %.6f\n", i+1, x[i])
	}
	fmt.Println()
}

// Метод простых итераций
func simpleIterationMethod(A [size][size]float64, b [size]float64) {
	fmt.Println("МЕТОД ПРОСТЫХ ИТЕРАЦИЙ")

	// Проверка диагонального преобладания
	fmt.Println("Проверка диагонального преобладания:")
	for i := 0; i < size; i++ {
		sum := 0.0
		for j := 0; j < size; j++ {
			if i != j {
				sum += math.Abs(A[i][j])
			}
		}
		if math.Abs(A[i][i]) <= sum {
			fmt.Printf("Строка %d: |%.2f| <= %.2f - диагональное преобладание НЕ выполняется\n", i+1, A[i][i], sum)
		} else {
			fmt.Printf("Строка %d: |%.2f| > %.2f - OK\n", i+1, A[i][i], sum)
		}
	}
	fmt.Println()

	// Приводим систему к виду x = C*x + d
	var C [size][size]float64
	var d [size]float64

	for i := 0; i < size; i++ {
		for j := 0; j < size; j++ {
			if i != j {
				C[i][j] = -A[i][j] / A[i][i]
			}
		}
		d[i] = b[i] / A[i][i]
	}

	var x [size]float64
	var newX [size]float64
	iteration := 0

	// Создаём форматированный вывод
	w := tabwriter.NewWriter(os.Stdout, 0, 0, 2, ' ', 0)
	fmt.Fprintln(w, "N\tx1\tx2\tx3\tx4\teps")

	for {
		for i := 0; i < size; i++ {
			sum := d[i]
			for j := 0; j < size; j++ {
				sum += C[i][j] * x[j]
			}
			newX[i] = sum
		}

		error := 0.0
		for i := 0; i < size; i++ {
			err := math.Abs(newX[i] - x[i])
			if err > error {
				error = err
			}
		}

		iteration++

		fmt.Fprintf(w, "%d\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\n",
			iteration, newX[0], newX[1], newX[2], newX[3], error)

		for i := 0; i < size; i++ {
			x[i] = newX[i]
		}

		if error < eps {
			break
		}

		if iteration > 1000 {
			fmt.Println("Метод не сошёлся за 1000 итераций")
			break
		}
	}
	w.Flush()

	fmt.Println("\nРешение методом простых итераций:")
	for i := 0; i < size; i++ {
		fmt.Printf("x%d = %.6f\n", i+1, x[i])
	}
}

func main() {
	// Вариант 16 (32 mod 16 = 0)
	M := 1.08
	N := 0.22
	P := -1.16

	A := [size][size]float64{
		{M, -0.4, 0.21, -1.16},
		{0.25, -1.23, N, -0.09},
		{-0.21, N, 0.8, -0.13},
		{0.15, -1.31, 0.06, P},
	}

	b := [size]float64{-1.24, P, 2.56, M}

	fmt.Println("========================================")
	fmt.Printf("Вариант 16 (M = %.2f, N = %.2f, P = %.2f)\n", M, N, P)
	fmt.Println("========================================")
	fmt.Println()

	fmt.Println("Исходная система:")
	printMatrix(A, b)

	gaussMethod(A, b)
	simpleIterationMethod(A, b)
}
