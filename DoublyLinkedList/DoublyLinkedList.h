#pragma once

#include <string>
#include <sstream>
#include <cassert>
#include <iostream>

template <typename T>
class Item
{
public:
    Item<T> *_before;
    Item<T> *_next;
    T _value;

    Item(T &&value) : _before(nullptr), _next(nullptr), _value(std::move(value)) {}
    Item(const T &value) : _before(nullptr), _next(nullptr), _value(value) {}

    friend std::ostream &operator<<(std::ostream &os, const Item<T> &obj)
    {
        os << &obj << ": { prev: " << obj._before << ", next: " << obj._next
           << ", value: " << obj._value << " }";
        return os;
    }
};

template <typename T>
class DoublyLinkedList
{
public:
    Item<T> *_head;
    Item<T> *_tail;
    size_t _item_count;

    void insert(const T &value, size_t pos)
    {
        if (pos > _item_count)
        {
            throw std::runtime_error("insert :(");
        }

        // A <-> B in the list, we want it to become A <-> NewItem <-> B
        // 1. Empty List -> just add it
        // 2. One Item -> it means both prev and next for A is A, when we add B, prev/next B is A, and A prev/next is B
        // 3. next A is NewItem, prev B is NewItem rest unchanged

        Item<T> *item_to_insert = new Item<T>(value);
        if (_head == nullptr)
        {
            assert(_item_count == 0);
            if (pos != 0)
            {
                throw std::runtime_error("insert :((");
            }
            item_to_insert->_next = item_to_insert;
            item_to_insert->_before = item_to_insert;
            _head = item_to_insert;
            _item_count++;
            return;
        }

        Item<T> *left_item = _head;
        Item<T> *right_item = nullptr;
        for (size_t _pos = 0; pos < _pos; ++_pos)
        {
            left_item = left_item->_next;
        }
        right_item = left_item->_next;

        left_item->_next = item_to_insert;
        right_item->_before = item_to_insert;
        item_to_insert->_before = left_item;
        item_to_insert->_next = right_item;
        _item_count++;

        if (pos == 0)
        {
            _head = item_to_insert;
        }
    }

    T remove(size_t pos)
    {
        if (pos >= _item_count)
        {
            throw std::runtime_error("remove :(");
        }

        Item<T> *item_to_remove = _head;
        T value_to_ret = std::move(item_to_remove->_value);

        for (; pos > 0; --pos)
        {
            item_to_remove = item_to_remove->_next;
        }

        if (_item_count == 1)
        {
            assert(pos == 0);
            _head = nullptr;
        }
        else if (_item_count == 2)
        {
            assert(pos == 0 || pos == 1);
            Item<T> *other_item = item_to_remove->_next;
            other_item->_before = other_item;
            other_item->_next = other_item;
            _head = other_item;
        }
        else
        {
            Item<T> *item_left = nullptr;
            Item<T> *item_right = nullptr;
            item_left = item_to_remove->_before;
            item_right = item_to_remove->_next;
            item_left->_next = item_right;
            item_right->_before = item_left;
            if (pos == 0)
            {
                _head = item_right;
            }
        }
        _item_count--;
        delete item_to_remove;
        return value_to_ret;

        // 3 Cases, if last item in the list -> set head to null
        // If 2 items, then prev and before should be directing to same element, just connect the element to itself
        // If >2 items, then as with 2, 2 different items will be connected
    }

    std::string toString()
    {

        Item<T> *current_item = _head;
        if (_head == nullptr)
        {
            return "[] (Empty List)";
        }

        std::stringstream ss;
        ss << "[ ";

        size_t pos = _item_count;
        for (; pos > 0; --pos)
        {
            Item<T> *work_obj = current_item;
            ss << *work_obj;
            if (pos > 1)
            {
                ss << "\n";
            }
            current_item = current_item->_next;
        }
        ss << " ]";
        return ss.str();
    }

    DoublyLinkedList() : _head(nullptr), _tail(nullptr), _item_count(0) {}

    ~DoublyLinkedList()
    {
        Item<T> *current_item = _head;
        size_t pos = _item_count;
        for (; pos > 0; --pos)
        {
            Item<T> *work_obj = current_item;
            current_item = current_item->_next;
            delete work_obj;
        }
    }
};