/*Для сложения чисел используется старый компьютер. 
/*Время, затрачиваемое на нахождение суммы двух чисел равно их сумме. 
Таким образом для нахождения суммы чисел 1,2,3 может потребоваться разное время, в зависимости от порядка вычислений. 
((1+2)+3) -> 1+2 + 3+3 = 9 ((1+3)+2) -> 1+3 + 4+2 = 10 ((2+3)+1) -> 2+3 + 5+1 = 11 
Требуется написать программу, которая определяет минимальное время, 
достаточное для вычисления суммы заданного набора чисел. */

#include <algorithm>
#include <iostream>
#include <cassert>
#include <stdexcept>

template<class T>
class min_heap {
public:
    min_heap();

    min_heap(const min_heap &other);

    min_heap(min_heap &&other) noexcept;

    min_heap(const T* array, size_t num);
        
    virtual ~min_heap() noexcept;

    void push(const T &value);

    void push(T &&value);

    const T &top();

    const T &pop();

    bool empty() const;

    size_t size() const;
private:
    const size_t INIT_HEAP_CAPACITY = 8;
    // Проталкивание элемента вниз.
    void sift_down(size_t i);
    // Проталкивание элемента наверх.
    void sift_up(size_t index);

    void resize();

    size_t capacity_;
    T* data_;
    size_t size_;
};

int calulate_min(int* arr, size_t n);

int main()
{
    int n = 0;
    std::cin >> n;
    assert(n > 0 && n < 100);

    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    std::cout << calulate_min(arr, n) << std::endl;
    delete[] arr;

    return 0;
}

int calulate_min(int* arr, size_t n)
{
    min_heap<int> h(arr, n);
    int count = 0;
    while (h.size() != 1) {
        int min_sum = h.pop() + h.pop();
        count += min_sum;
        h.push(min_sum);
    }
    return count;
}

template<class T>
min_heap<T>::min_heap() :
    capacity_(INIT_HEAP_CAPACITY),
    data_(new T[capacity_]),
    size_(0)
{}

template<class T>
min_heap<T>::min_heap(const min_heap &other) :
    capacity_(other.capacity_),
    data_(new T[capacity_]),
    size_(other.size_) {
    std::copy(other.data_, other.data_ + size_, data_);
}

template<class T>
min_heap<T>::min_heap(min_heap &&other) noexcept {
    std::swap(other.data_, data_);
    std::swap(other.capacity_, capacity_);
    std::swap(other.size_, size_);
}

template<class T>
min_heap<T>::min_heap(const T* array, size_t size) :
    capacity_(size),
    data_(new T[capacity_]),
    size_(size) {
    std::copy(array, array + size, data_);
    for (int i = size_ / 2; i >= 0; i--) {
        sift_down(i);
    }
}

template<class T>
min_heap<T>::~min_heap() noexcept {
    delete[] data_;
}

template<class T>
void min_heap<T>::push(const T &value) {
    if (size_ == capacity_) {
        resize();
    }

    data_[size_] = value;
    sift_up(size_);
    size_++;
}

template<class T>
void min_heap<T>::push(T &&value) {
    if (size_ == capacity_) {
        resize();
    }

    data_[size_] = std::move(value);
    sift_up(size_);
    size_++;
}

template<class T>
const T& min_heap<T>::top() {
    if (size_ == 0)
        throw std::out_of_range("heap is empty");

    return data_[0];
}

template<class T>
const T& min_heap<T>::pop() {
    if (size_ == 0)
        throw std::out_of_range("heap is empty");

    std::swap(data_[0], data_[--size_]);
    sift_down(0);
    return data_[size_];
}

template<class T>
bool min_heap<T>::empty() const {
    return size_ == 0;
}

template<class T>
size_t min_heap<T>::size() const {
    return size_;
}

template<class T>
void min_heap<T>::sift_down(size_t i) {
    size_t  left = 2 * i + 1;
    size_t  right = 2 * i + 2;
    // Ищем меньшего сына, если такой есть.
    size_t  smallest = i;
    if (left < size_ && data_[left] < data_[i])
        smallest = left;
    if (right < size_ && data_[right] < data_[smallest])
        smallest = right;
    // Если меньший сын есть, то проталкиваем корень в него.
    if (smallest != i) {
        std::swap(data_[i], data_[smallest]);
        sift_down(smallest);
    }
}

template<class T>
void min_heap<T>::sift_up(size_t index) {
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (data_[index] >= data_[parent])
            return;
        std::swap(data_[index], data_[parent]);
        index = parent;
    }
}

template<class T>
void min_heap<T>::resize() {
    T *new_data = new T[capacity_ * 2];
    for (size_t i = 0; size_; i++) {
        new_data[i] = data_[i];
    }
}

