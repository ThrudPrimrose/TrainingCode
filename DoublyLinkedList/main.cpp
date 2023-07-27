#include "DoublyLinkedList.h"
#include <iostream>

int main()
{
    DoublyLinkedList<int> list;
    std::cout << list.toString() << std::endl;
    list.insert(0, 0);
    std::cout << list.toString() << std::endl;
    list.insert(1, 0);
    std::cout << list.toString() << std::endl;
    list.insert(2, 1);
    std::cout << list.toString() << std::endl;
    list.insert(3, 2);
    std::cout << list.toString() << std::endl;
    list.insert(4, 0);
    std::cout << list.toString() << std::endl;
    list.remove(3);
    std::cout << list.toString() << std::endl;
    list.remove(0);
    std::cout << list.toString() << std::endl;
    list.remove(1);
    std::cout << list.toString() << std::endl;
    list.remove(0);
    std::cout << list.toString() << std::endl;
    list.remove(0);
    std::cout << list.toString() << std::endl;
    return 0;
}