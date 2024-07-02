//omer.apter@msmail.ariel.ac.il
#include <vector>
#pragma once
namespace ex4
{
    template <typename T>
    class Node
    {
    private:
        T value;

    public:
        Node<T> *parent;
        Node<T> *prev_sibling, *next_sibling;
        Node<T> *first_child, *last_child;
        int num_of_children;
        Node(T val)
        {
            value = val;
            parent = nullptr;
            prev_sibling = nullptr;
            next_sibling = nullptr;
            first_child = nullptr;
            last_child = nullptr;
            num_of_children = 0;
        }
        T get_value()
        {
            return value;
        }
        bool operator<(Node<T> &rhs)
        {
            return this->get_value() < rhs.get_value();
        }
        bool operator>(Node<T> &rhs)
        {
            return this->get_value() > rhs.get_value();
        }

        bool operator==(Node<T> &rhs)
        {
            return !(this < rhs || this > rhs);
        }
        bool operator!=(Node<T> &rhs)
        {
            return (this < rhs || this > rhs);
        }
    };
} // namespace ex4
