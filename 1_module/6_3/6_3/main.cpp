#include <iostream>
#include <random>
#include <cassert>
#include <algorithm>

template <class It>
size_t get_random_pivot(It first, It last) {
    size_t size = std::distance(first, last);
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<size_t> dist(0, size - 1);
    return dist(mt);
}

template <class _FwdIt, class Compare = std::less_equal<int>>
size_t Partition(_FwdIt first, _FwdIt last, Compare comp = Compare{}) {
    if (first == last)
        return 0;

    size_t pivot = get_random_pivot(first, last);
    std::swap(*std::next(first, pivot), *std::prev(last));
   
    auto i = first;
    auto j = first;

    while (j != std::prev(last)) {
        if (comp(*std::prev(last), *j)) {
            j++;
        }
        else {
            std::swap(*i++, *j++);
        }
    }

    pivot = std::distance(first,i);
    std::swap(*std::prev(last), *i);
    return pivot;
}

template <class T, class _FwdIt, class Compare = std::less_equal<int>>
T ord_statistic(_FwdIt first, _FwdIt last, _FwdIt dist, size_t stat, Compare comp = Compare{}) {
    if (first == last)
        throw std::runtime_error("last = first");

    size_t size = std::distance(first, last);
    std::copy(first, last, dist);

    auto it = dist;

    size_t pivot = Partition(it, std::next(it,size), comp);
    while (pivot != stat) {
        if (stat < pivot) {
            size = pivot;
        }
        else {
            it += (pivot + 1);
            size -= (pivot + 1);
            stat -= (pivot + 1);
        }
        pivot = Partition(it, std::next(it, size), comp);
    }

    T result = *(it + pivot);
    return result;
}

int main() {
    int n = 0;
    size_t k = 0;

    std::cin >> n;
    std::cin >> k;
    assert(n > 0 && k >= 0);

    std::vector<int> v(n);
    for (int i = 0; i < n; i++) {
        std::cin >> v[i];
    }

    std::vector<int> buffer(v.size());

    int result = ord_statistic<int>(v.begin(), v.end(), buffer.begin(), k);

    std::cout << result << std::endl;
    
    system("pause");
    return 0;
}