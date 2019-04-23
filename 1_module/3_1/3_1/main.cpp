 /*Реализовать очередь с динамическим зацикленным буфером. 
Обрабатывать команды push back и pop front.*/

#include <iostream>
#include <cassert>
#include "queue.hpp"

int main() {
    int n = 0;
    std::cin >> n;
    assert(n > 0 && n < 1000000);

    queue<int> my_q;
    for (int i = 0; i < n; ++i) {
        int command = 0;
        int control = 0;
        std::cin >> command;

        int temp = 0;
        switch (command)
        {
        case 2: {
            temp = my_q.pop_back();
            std::cin >> control;
            if (temp == control)  {
                std::cout << "YES" << std::endl;
            }
            else {
                std::cout << "NO" << std::endl;
            }
            break;
        }
        case 3: {
            std::cin >> control;
            my_q.push_front(control);
        }
        default:
            break;
        }
    }
    return 0;
}