/*Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
Для каждого элемента массива B[i] найдите минимальный индекс k минимального элемента массива A, 
равного или превосходящего B[i]: A[k] >= B[i]. Если такого элемента нет, выведите n.
Время работы поиска k для каждого элемента B[i]: O(log(k)). n, m ≤ 10000. */

#include <iostream>
#include <cassert>
#include <cmath>

void find_interval_in(const int* A, int n, int el, int& left, int& right)
{
    while (right < n && el > A[right]) { // сначала размер, чтобы не запросить невыделенный элемент
        left = right;
        right *= 2;
    }

    if (right > n - 1) { // если перескочили размер
        right = n - 1;
    }
}

int* find_in_from(const int* A, int n, const int* B, int m) {
    int* result = new int[m];

    for (int i = 0; i < m; i++) {

        if (B[i] <= A[0]) { // если элемент слева
            result[i] = 0;
            continue;
        }
        if (B[i] > A[n - 1]) { // если элемент больше всех

            result[i] = n;
            continue;
        }

        int left = 0;
        int right = 1;
        int mid = 0;
        // находим интервал степени двойки в котором находится B[i]
        find_interval_in(A, n, B[i], left, right);

        // бинарный поиск по интервалу left; right
        while (right - left > 1) { // пока они не будут рядом
            mid = (right + left) / 2;
            if (B[i] <= A[mid]) {
                right = mid;
            }
            else {
                left = mid;
            }
        }
        if (B[i] == A[left])
            result[i] = left;
        else
            result[i] = right;
    }
    return result;
}

void print_result(const int* res, int size)
{
    for (int i = 0; i < size; i++) {
        std::cout << res[i] << ' ';
    }
    std::cout << std::endl;
}
int main()
{
    int n = 0;
    int m = 0;
    std::cin >> n >> m;

    assert(n > 0 && m > 0 && n < 10000 && m < 10000);

    int *A = new int[n];
    int *B = new int[m];

    for (int i = 0; i < n; i++) {
        std::cin >> A[i];
    }

    for (int i = 0; i < m; i++) {
        std::cin >> B[i];
    }
    
    auto result = find_in_from(A, n, B, m);
    print_result(result, m);
    
    delete[] result;
    delete[] B;
    delete[] A;
    system("pause");
    return 0;
}