#ifndef QUEUE_HPP

#include <iostream>
const int START_BUFFER_SIZE = 8;

template <class T>
class queue {
public:
    queue();
    ~queue();
    T pop_back();
    
    void push_front(T element);

private:
    int bufferSize_;
    int size_;
    int begin_;
    int end_;
    T* buffer_;
    void reabase();
};

template <class T>
queue<T>::queue() :
    bufferSize_(START_BUFFER_SIZE),
    size_(0),
    begin_(0),
    end_(0)
{
    buffer_ = new T[bufferSize_];
}

template <class T>
queue<T>::~queue() {
    delete[] buffer_;
}

template <class T>
void queue<T>::push_front(T el) {
    if (size_ == bufferSize_) {
        reabase();
    }

    if (size_ != 0)
        end_ = (end_ + 1) % bufferSize_;

    buffer_[end_] = el;
    size_++;
}

template <class T>
T queue<T>::pop_back() {
    if (size_ != 0)
    {
        T val = buffer_[begin_];

        if (size_ != 1)
            begin_ = (begin_ + 1) % bufferSize_;

        size_--;

        return val;
    }
    return -1;
}


template <class T>
void queue<T>::reabase() {
    T* tmp = buffer_;

    bufferSize_ *= 2;
    buffer_ = new T[bufferSize_];

    for (int i = begin_; i < size_; i++)
        buffer_[i - begin_] = tmp[i];

    if (begin_ != 0)
        for (int i = 0; i < end_ + 1; i++)
            buffer_[i + size_ - begin_] = tmp[i];

    begin_ = 0;
    end_ = size_ - 1;
    delete[] tmp;
}
#define QUEUE_HPP
#endif // !QUEUE_HPP

