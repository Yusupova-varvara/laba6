package main

import (
	"fmt"
)

func makePattern(pattern [][]int, N, M, start int) {
	for i := 0; i < N; i++ {
		for j := 0; j < M; j++ {
			if i == 0 || i == N-1 || j == 0 || j == M-1 { // если является границей (рамка)
				pattern[i][j] = start
			} else { // если находится внутри
				pattern[i][j] = (start + 1) % 2
			}
		}
	}
}

func countMoves(board [][]int, target [][]int, N, M int) int {
	moves := 0 // счетчик ходов

	// создаем копию доски, чтобы не изменять оригинал
	temp := make([][]int, N)
	for i := 0; i < N; i++ {
		temp[i] = make([]int, M)
		for j := 0; j < M; j++ {
			temp[i][j] = board[i][j]
		}
	}

	for i := 0; i < N; i++ {
		for j := 0; j < M; j++ {
			if temp[i][j] != target[i][j] { // если текущая клетка не совпадает с шаблоном
				moves++ // увеличиваем счетчик ходов
				temp[i][j] = 1 - temp[i][j] // переворачиваем текущую клетку

				// переворачиваем соседнюю клетку справа, если она существует и не совпадает с шаблоном
				if j+1 < M && temp[i][j+1] != target[i][j+1] {
					temp[i][j+1] = 1 - temp[i][j+1]
				} else if i+1 < N && temp[i+1][j] != target[i+1][j] {
					// иначе переворачиваем соседнюю клетку снизу, если она существует и не совпадает с шаблоном
					temp[i+1][j] = 1 - temp[i+1][j]
				} else if j+1 < M {
					// иначе переворачиваем клетку справа (даже если она уже совпадает с шаблоном)
					temp[i][j+1] = 1 - temp[i][j+1]
				} else {
					// если нет доступных соседей для переворота
					return 999999 // возвращаем большое число (невозможно)
				}
			}
		}
	}

	// проверяем, совпадает ли итоговая доска с шаблоном
	for i := 0; i < N; i++ {
		for j := 0; j < M; j++ {
			if temp[i][j] != target[i][j] {
				return 999999 // если не совпадает - невозможно
			}
		}
	}

	return moves // возвращаем количество ходов
}

func printBoard(board [][]int, N, M int) {
	for i := 0; i < N; i++ {
		for j := 0; j < M; j++ {
			fmt.Printf("%d", board[i][j])
			if j < M-1 {
				fmt.Print(" ") // выводим пробел между элементами, кроме последнего
			}
		}
		fmt.Println() // переходим на новую строку после каждой строки доски
	}
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func main() {
	var N, M int

	fmt.Print("Введите размеры доски (N M): ")
	fmt.Scan(&N, &M)

	// Создаем и считываем доску
	board := make([][]int, N)
	fmt.Println("Введите доску (0 - орёл, 1 - решка):")
	for i := 0; i < N; i++ {
		board[i] = make([]int, M)
		for j := 0; j < M; j++ {
			fmt.Scan(&board[i][j])
		}
	}

	// создаем два паттерна: начинающийся с 0 и с 1
	pattern1 := make([][]int, N)
	pattern2 := make([][]int, N)
	for i := 0; i < N; i++ {
		pattern1[i] = make([]int, M)
		pattern2[i] = make([]int, M)
	}
	makePattern(pattern1, N, M, 0) // паттерн, где рамка начинается с 0
	makePattern(pattern2, N, M, 1) // паттерн, где рамка начинается с 1

	// считаем минимальное количество ходов для каждого паттерна
	moves1 := countMoves(board, pattern1, N, M)
	moves2 := countMoves(board, pattern2, N, M)

	fmt.Println("\nПаттерн (начинается с 0):")
	printBoard(pattern1, N, M)
	fmt.Print("Нужно ходов: ")
	if moves1 >= 999999 {
		fmt.Println("невозможно")
	} else {
		fmt.Println(moves1)
	}

	fmt.Println("\nПаттерн (начинается с 1):")
	printBoard(pattern2, N, M)
	fmt.Print("Нужно ходов: ")
	if moves2 >= 999999 {
		fmt.Println("невозможно")
	} else {
		fmt.Println(moves2)
	}

	fmt.Print("\nМинимальное количество ходов: ")
	minMoves := min(moves1, moves2)
	if minMoves >= 999999 {
		fmt.Println("невозможно")
	} else {
		fmt.Println(minMoves)
	}
}
