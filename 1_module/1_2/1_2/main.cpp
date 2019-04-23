/*
��������� ������� ��������� n-���������, ��������� ������������ ����� ������.
������� �������� ���������� ������, ����� ��������������� ������������� ���������� ���� ������ � ������� ������ ������ ������� �������.
n < 1000, ���������� < 10000.
��������. ��� ���������� ������� n-��������� ����� ��������� ����� ��������������� �������� �������� ��� ������ �������� ��������������. 
*/
#include <cassert>
#include <cmath>
#include <iostream>

double calculate(const int *x, const int *y, const int n) {
    double square = 0;
    for (int i = 0; i < n - 1; i++) {
        square += (double)((x[i + 1] - x[i]) * (y[i + 1] + y[i])) / 2;
    }
    square += (double)((x[0] - x[n-1]) * (y[0] + y[n-1])) / 2;
    square = std::abs(square);
    return square;
}

int main()
{
    int n = 0;
    std::cin >> n;

    assert(n > 2 && n < 1000);

    int *X = new int[n];
    int *Y = new int[n];

    for (int i = 0; i < n; i++) {
        std::cin >> X[i] >> Y[i];
    }

    auto result = calculate(X, Y, n);
    delete[] X;
    delete[] Y;

    std::cout << result << std::endl;

    system("pause");
    return 0;
}