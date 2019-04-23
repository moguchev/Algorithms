/*
Ќа числовой пр€мой окрасили N отрезков.
»звестны координаты левого и правого концов каждого отрезка (Li и Ri).
Ќайти сумму длин частей числовой пр€мой, окрашенных ровно в один слой.
*/
#include <algorithm>
#include <cassert>
#include <functional> 
#include <iostream>
#include <iterator>
#include <type_traits>

class Point {
public:
    enum class status {
        BEGIN = 1,
        END,
        NONE
    };

    Point();

    Point(int x, status s);

    virtual ~Point() = default;

    int get_x() const;

    bool is_begin() const;

    bool is_end()  const;
private:
    int coordinate_;
    status type_;
};

struct cmpPoint {
    bool operator()(const Point& left, const Point& right) {
        return left.get_x() < right.get_x();
    }
};

template <class It, class Out, class Compare = std::less<int>>
Out merge_sort(It first, It last, Out out, Compare cmp = Compare{});

int len_one_layer(const Point* points, size_t size);

int main() {
    int n = 0;
    std::cin >> n;
    assert(n > 0);

    Point* points = new Point[2 * n];
    for (int i = 0; i < 2 * n; i++) {
        int coordinate = 0;
        std::cin >> coordinate;

        if (i % 2 == 0)
            points[i] = Point(coordinate, Point::status::BEGIN);
        else
            points[i] = Point(coordinate, Point::status::END);
    }

    cmpPoint gr;
    Point* sorted_points = new Point[2 * n];
    merge_sort(&points[0], &points[2 * n], &sorted_points[0], gr);

    std::cout << len_one_layer(sorted_points, 2 * n) << std::endl;
    delete[] points;
    delete[] sorted_points;
    system("pause");
    return 0;
}

int len_one_layer(const Point* points, size_t size) {
    int res = 0;
    int layer = 1;
    Point prev_point = points[0];

    for (size_t i = 1; i < size; i++) {
        if (layer == 1) {
            res += points[i].get_x() - prev_point.get_x();
        }

        if (points[i].is_begin()) {
            layer++;
        }

        if (points[i].is_end()) {
            layer--;
        }

        prev_point = points[i];
    }

    return res;
}

Point::Point() : coordinate_(0), type_(status::NONE) {};

Point::Point(int x, status s) : coordinate_(x), type_(s) {};

int Point::get_x() const {
    return coordinate_;
}

bool Point::is_begin() const {
    return type_ == status::BEGIN;
}

bool Point::is_end()  const {
    return type_ == status::END;
}

template <class It, class Out, class Compare = std::less<int>>
Out merge(It first1, It last1, It first2, It last2, Out out, Compare cmp = Compare{}) {
    It i = first1;
    It j = first2;
    size_t k = 0;

    while (i != last1 && j != last2)  {
        if (cmp(*i, *j))
            out[k++] = *i++;
        else
            out[k++] = *j++;
    }

    while (i != last1) {
        out[k++] = *i++;
    }

    while (j != last2) {
        out[k++] = *j++;
    }
    return out;
}

template <class It, class Out, class Compare = std::less<int>>
Out merge_sort(It first, It last, Out out, Compare cmp)
{
    if (std::distance(first, last) == 1) {
        *out = *first;
    }

    else if (std::distance(first, last) > 1) {
        It mid = first + std::distance(first, last) / 2;
        out = merge_sort(first, mid, out, cmp);
        out = merge_sort(mid, last, out, cmp);
        out = merge(first, mid, mid, last, out, cmp);

        size_t i = 0;
        for (It curr = first; curr != last; ++curr)
            *curr = out[i++];
    }
    return out;
}
