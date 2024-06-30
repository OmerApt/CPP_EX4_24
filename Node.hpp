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
            int num_of_children = 0;
        }
        T get_value()
        {
            return value;
        }
    };
} // namespace ex4
