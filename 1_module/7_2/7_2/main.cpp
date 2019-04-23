#include <iostream>
#include <algorithm>


const size_t LL_BIT = 256;

// сортировка LSD
void LSDSort(int64_t *data, size_t size);
// сортировка подсчетом массива чисел по n-ому байту
void counting_sort(int64_t *data, size_t size, const size_t n_byte);
// получает n-тый байт числа
int get_byte(int64_t number, size_t n);

int main() {
    size_t n = 0;
    std::cin >> n;

    int64_t *data = new int64_t[n];
    for (size_t i = 0; i < n; i++) {
        std::cin >> data[i];
    }

    LSDSort(data, n);

    for (size_t i = 0; i < n; i++) {
        std::cout << data[i] << " ";
    }

    
    delete[] data;
    system("pause");
    return 0;
}


void LSDSort(int64_t *data, size_t size) {
    size_t totalBytes = sizeof(int64_t);

    for (size_t byte = 0; byte < totalBytes; byte++) {
        counting_sort(data, size, byte);
    }
}

// получаем n-тый байт числа
int get_byte(int64_t number, size_t n) {
    return number >> (sizeof(int64_t) * n) & 255;
}

// сортировка подсчетом массива чисел по n-ому байту
void counting_sort(int64_t *data, size_t size, const size_t n_byte) {
    size_t counters[LL_BIT];
    std::fill_n(counters, LL_BIT, 0);

    // считаем количество чисел с разными значениями байта (от 0 до 255)
    for (size_t i = 0; i < size; i++) {
        counters[get_byte(data[i], n_byte)]++;
    }

    // расчитываем первые индексы для вставки чисел
    for (size_t i = 1; i < LL_BIT; i++) {
        counters[i] += counters[i - 1];
    }

    // массив для результатов
    int64_t *tmp = new int64_t[size];

    // создаем отсортированный массив результатов
    for (int i = size - 1; i >= 0; i--) {
        tmp[--counters[get_byte(data[i], n_byte)]] = data[i];
    }

    // переписываем отсортированный массив в исходный
    std::memcpy(data, tmp, size * sizeof(int64_t));
    delete[] tmp;
}