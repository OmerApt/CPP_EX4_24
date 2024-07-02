#include <vector>
#include "Node.hpp"
#include <map>
#include <deque>
#include <functional>
#include <bits/stdc++.h>
#pragma once
namespace ex4
{
    using namespace std;
    template <typename T>
    class Tree
    {
    private:
        Node<T> *root;
        int child_limit;

    public:
        Tree()
        {
            child_limit = 2;
            root = nullptr;
        }
        Tree(int limit)
        {
            child_limit = limit;
            root = nullptr;
        }
        ~Tree()
        {
        }

    public:
        void add_root(Node<T> &n)
        {
            this->root = &n;
        }
        void add_sub_node(Node<T> &node, Node<T> &child)
        {
            if (node.num_of_children < child_limit)
            {
                if (!node.first_child)
                {
                    node.first_child = &child;
                }
                else
                {
                    Node<T> *p_node = node.first_child;
                    while (p_node->next_sibling)
                    {
                        p_node = p_node->next_sibling;
                    }
                    p_node->next_sibling = &child;
                    child.prev_sibling = p_node;
                    node.last_child = &child;
                }
                child.parent = &node;
                node.num_of_children++;
            }
        }
        // start of iterators
        class ForNonBinaryTreesIterator
        {
        protected:
            deque<Node<T> *> ite_next_queue;

        public:
            ForNonBinaryTreesIterator(Node<T> *root = nullptr)
            {
                ite_next_queue = deque<Node<T> *>();
                ite_next_queue.emplace_front(root);
            }
            ~ForNonBinaryTreesIterator()
            {
                ite_next_queue.clear();
            }

            Node<T> *altNext()
            {
                if (ite_next_queue.size() > 0)
                {
                    Node<T> *current = ite_next_queue.front();
                    ite_next_queue.pop_front();

                    Node<T> *child = current->first_child;
                    while (child)
                    {
                        ite_next_queue.emplace_front(child);
                        child = child->next_sibling;
                    }
                    return current;
                }
                return NULL;
            }
        };

        class BFSIterator
        {
        private:
            deque<Node<T> *> ite_next_queue;
            Node<T> *current;

        public:
            BFSIterator(Node<T> *root = nullptr) : ite_next_queue()
            {
                current = root;
            }
            ~BFSIterator()
            {
                ite_next_queue.clear();
            }
            Node<T> &operator*() const
            {
                // return *pointer_to_current_node;
                return current;
            }

            Node<T> *operator->() const
            {
                return current;
            }

            // ++i;
            BFSIterator &operator++()
            {
                //++pointer_to_current_node;
                // pointer_to_current_node = pointer_to_current_node->m_next;
                next();
                return *this;
            }

            // i++;
            // Usually iterators are passed by value and not by const& as they are small.
            const BFSIterator operator++(int)
            {
                InOrderIterator tmp = *this;
                next();
                return tmp;
            }

            bool operator==(const BFSIterator &rhs) const
            {
                return current == rhs.current;
            }

            bool operator!=(const BFSIterator &rhs) const
            {
                return current != rhs.current;
            }

            void next()
            {
                Node<T> *child = current->first_child;
                while (child)
                {
                    ite_next_queue.emplace_front(child);
                    child = child->next_sibling;
                }
                current = ite_next_queue.back();
                ite_next_queue.pop_back();
            }
        };

        class DFSIterator
        {
        private:
            deque<Node<T> *> ite_next_queue;
            Node<T> *current;

        public:
            DFSIterator(Node<T> *root = nullptr) : ite_next_queue()
            {
                current = root;
            }
            ~DFSIterator()
            {
                ite_next_queue.clear();
            }
            Node<T> &operator*() const
            {
                // return *pointer_to_current_node;
                return current;
            }

            Node<T> *operator->() const
            {
                return current;
            }

            // ++i;
            DFSIterator &operator++()
            {
                //++pointer_to_current_node;
                // pointer_to_current_node = pointer_to_current_node->m_next;
                next();
                return *this;
            }

            // i++;
            // Usually iterators are passed by value and not by const& as they are small.
            const DFSIterator operator++(int)
            {
                InOrderIterator tmp = *this;
                next();
                return tmp;
            }

            bool operator==(const DFSIterator &rhs) const
            {
                return current == rhs.current;
            }

            bool operator!=(const DFSIterator &rhs) const
            {
                return current != rhs.current;
            }

            void next()
            {
                Node<T> *child = current->first_child;
                while (child && child->first_child)
                {
                    ite_next_queue.emplace_front(child);
                    child = child->first_child;
                }
                while (child)
                {
                    ite_next_queue.emplace_front(child);
                    child = child->next_sibling;
                }

                current = ite_next_queue.front();
                ite_next_queue.pop_front();
            }
        };

        class InOrderIterator
        {

        private:
            Node<T> *current_node;
            Node<T> *show_next;
            Node<T> *right_most;
            bool is_binary;
            ForNonBinaryTreesIterator alt_iterator;

        public:
            InOrderIterator(Node<T> *ptr = nullptr, bool binary = true)
                : current_node(ptr)
            {
                right_most = NULL;
                is_binary = binary;
                alt_iterator = ForNonBinaryTreesIterator(current_node);
                show_next = next();
            }
            Node<T> &operator*() const
            {
                // return *pointer_to_current_node;
                return show_next;
            }

            Node<T> *operator->() const
            {
                return show_next;
            }

            // ++i;
            InOrderIterator &operator++()
            {
                //++pointer_to_current_node;
                // pointer_to_current_node = pointer_to_current_node->m_next;
                this->show_next = next();
                return *this;
            }

            // i++;
            // Usually iterators are passed by value and not by const& as they are small.
            const InOrderIterator operator++(int)
            {
                InOrderIterator tmp = *this;
                this->show_next = next();
                return tmp;
            }

            bool operator==(const InOrderIterator &rhs) const
            {
                return show_next == rhs.show_next;
            }

            bool operator!=(const InOrderIterator &rhs) const
            {
                return show_next != rhs.show_next;
            }

            bool hasinOrderNext() { return current_node != NULL; }

            Node<T> *inOrderNext()
            {
                if (!hasinOrderNext())
                {
                    // std::cout << "No such element exists" << std::endl;
                    return NULL;
                }

                if (current_node->first_child == NULL)
                {
                    Node<T> *temp = current_node;
                    current_node = current_node->last_child;
                    return temp;
                }

                right_most = current_node->first_child;

                while (right_most->last_child != NULL && right_most->last_child != current_node)
                {
                    right_most = right_most->last_child;
                }

                if (right_most->last_child == NULL)
                {
                    right_most->last_child = current_node;
                    current_node = current_node->first_child;
                }
                else
                {
                    right_most->last_child = NULL;
                    Node<T> *temp = current_node;
                    current_node = current_node->last_child;
                    return temp;
                }

                return inOrderNext();
            }

            Node<T> *next()
            {
                if (is_binary)
                {
                    return inOrderNext();
                }
                else
                {
                    return alt_iterator.altNext();
                }
            }
        };

        class PreOrderIterator
        {

        private:
            Node<T> *current_node;
            bool is_binary;
            ForNonBinaryTreesIterator alt_iterator;
            deque<Node<T> *> next_queue;

        public:
            PreOrderIterator(Node<T> *ptr = nullptr, bool binary = true)
            {
                next_queue.emplace_front(ptr);
                this->is_binary = binary;
                alt_iterator = ForNonBinaryTreesIterator(current_node);
                current_node = next();
            }
            Node<T> &operator*() const
            {
                // return *pointer_to_current_node;
                return current_node;
            }

            Node<T> *operator->() const
            {
                return current_node;
            }

            // ++i;
            PreOrderIterator &operator++()
            {
                //++pointer_to_current_node;
                // pointer_to_current_node = pointer_to_current_node->m_next;
                this->current_node = next();
                return *this;
            }

            // i++;
            // Usually iterators are passed by value and not by const& as they are small.
            const PreOrderIterator operator++(int)
            {
                PreOrderIterator tmp = *this;
                this->current_node = next();
                return tmp;
            }

            bool operator==(const PreOrderIterator &rhs) const
            {
                return current_node == rhs.current_node;
            }

            bool operator!=(const PreOrderIterator &rhs) const
            {
                return current_node != rhs.current_node;
            }

            bool hasPreOrderNext() { return current_node != NULL; }

            Node<T> *preOrderNext()
            {
                if (next_queue.size() > 0)
                {
                    Node<T> *curr = next_queue.back();
                    next_queue.pop_back();
                    if (curr)
                    {
                        if (curr->last_child)
                            next_queue.emplace_back(curr->last_child);
                        if (curr->first_child)
                            next_queue.emplace_back(curr->first_child);
                        return curr;
                    }
                }
                return NULL;
            }

            Node<T> *next()
            {
                if (is_binary)
                {
                    return preOrderNext();
                }
                else
                {
                    return alt_iterator.altNext();
                }
            }
        };

        class PostOrderIterator
        {

        private:
            Node<T> *current_node;
            Node<T> *show;
            Node<T> *prev;
            bool is_binary;
            ForNonBinaryTreesIterator alt_iterator;

        public:
            PostOrderIterator(Node<T> *ptr = nullptr, bool binary = true)
            {
                current_node = ptr;
                this->is_binary = binary;
                if (current_node != nullptr)
                {
                    alt_iterator = ForNonBinaryTreesIterator(current_node);
                    if (is_binary)
                    {
                        init(current_node);
                        show = current_node;
                    }
                    else
                        show = next();
                }
            }
            Node<T> &operator*() const
            {
                // return *pointer_to_current_node;
                return current_node;
            }

            Node<T> *operator->() const
            {
                return current_node;
            }

            // ++i;
            PostOrderIterator &operator++()
            {
                //++pointer_to_current_node;
                // pointer_to_current_node = pointer_to_current_node->m_next;
                this->show = next();
                return *this;
            }

            // i++;
            // Usually iterators are passed by value and not by const& as they are small.
            const PostOrderIterator operator++(int)
            {
                PostOrderIterator tmp = *this;
                this->show = next();
                return tmp;
            }

            bool operator==(const PostOrderIterator &rhs) const
            {
                return current_node == rhs.current_node;
            }

            bool operator!=(const PostOrderIterator &rhs) const
            {
                return current_node != rhs.current_node;
            }

            bool hasPostOrderNext() { return current_node != NULL; }

            void init(Node<T> *root)
            {
                while (root->first_child)
                {
                    prev = root;
                    root = root->first_child;
                }
                current_node = root;
            }

            Node<T> *PostOrderNext()
            {
                if (prev == NULL)
                {
                    return prev;
                }
                if (current_node == NULL)
                {
                    auto tmp = prev;
                    prev = NULL;
                    return tmp;
                }

                if (prev == current_node->last_child || prev == current_node->first_child)
                {
                    prev = current_node;
                    if (current_node->next_sibling)
                    {
                        // gets to left most leaf in this sub tree
                        init(current_node->next_sibling);
                    }
                    else
                    {
                        current_node = current_node->parent;
                    }
                }
                else if (prev == current_node->prev_sibling)
                {
                    prev = current_node;
                    if (current_node->first_child)
                        while (current_node && current_node->first_child)
                        {
                            current_node = current_node->first_child;
                        }
                    else
                        current_node = current_node->parent;
                }
                else
                {
                    prev = current_node;
                    if (current_node->last_child)
                        current_node = current_node->last_child;
                    else if (current_node->next_sibling)
                        current_node = current_node->next_sibling;
                    else
                        current_node = current_node->parent;
                }
                return current_node;
            }

            Node<T> *next()
            {
                if (is_binary)
                {
                    return PostOrderNext();
                }
                else
                {
                    return alt_iterator.altNext();
                }
            }
        };
        class MinHeapIterator
        {

        private:
            Node<T> *current_node;
            Node<T> *show;
            bool is_binary;
            ForNonBinaryTreesIterator alt_iterator;
            priority_queue<Node<T> *, vector<Node<T> *>, greater<Node<T> *>> min_heap;

        public:
            MinHeapIterator(Node<T> *ptr = nullptr, bool binary = true)
            {
                if (current_node != nullptr)
                {
                    alt_iterator = ForNonBinaryTreesIterator(current_node);
                    if (is_binary)
                        init(current_node);
                    show = next();
                }
            }
            Node<T> &operator*() const
            {
                // return *pointer_to_current_node;
                return current_node;
            }

            Node<T> *operator->() const
            {
                return current_node;
            }

            // ++i;
            MinHeapIterator &operator++()
            {
                //++pointer_to_current_node;
                // pointer_to_current_node = pointer_to_current_node->m_next;
                this->show = next();
                return *this;
            }

            // i++;
            // Usually iterators are passed by value and not by const& as they are small.
            const MinHeapIterator operator++(int)
            {
                PostOrderIterator tmp = *this;
                this->show = next();
                return tmp;
            }

            bool operator==(const MinHeapIterator &rhs) const
            {
                return show == rhs.show;
            }

            bool operator!=(const MinHeapIterator &rhs) const
            {
                return show != rhs.show;
            }

            void init(Node<T> *root)
            {
                addToHeap(root);
            }

            void addToHeap(Node<T> *root)
            {
                if (root != NULL)
                {
                    min_heap.push(root);
                    Node<T> *child = root->first_child;
                    while (child)
                    {
                        addToHeap(child);
                        child = child->next_sibling;
                    }
                }
            }

            Node<T> *minHeapNext()
            {
                if (!min_heap.empty())
                {
                    Node<T> *tmp = min_heap.top();
                    min_heap.pop();
                    return tmp;
                }
                return NULL;
            }

            Node<T> *next()
            {
                if (is_binary)
                {
                    return minHeapNext();
                }
                else
                {
                    return alt_iterator.altNext();
                }
            }
        };
        // iterator calls
        // in order
        InOrderIterator begin_in_order()
        {
            if (child_limit == 2) // binary tree
            {
                InOrderIterator tmp = InOrderIterator(root);
                return tmp;
            }
            return InOrderIterator(root, false);
        }
        InOrderIterator end_in_order()
        {
            if (child_limit == 2) // binary tree
            {
                return this->root->parent;
            }
            return this->root->parent;
        }
        // pre order
        PreOrderIterator begin_pre_order()
        {
            if (child_limit == 2) // binary tree
            {
                PreOrderIterator tmp = PreOrderIterator(root);
                return tmp;
            }
            return PreOrderIterator(root, false);
        }
        PreOrderIterator end_pre_order()
        {
            if (child_limit == 2) // binary tree
            {
                return this->root->parent;
            }
            return this->root->parent;
        }
        // post order
        PostOrderIterator begin_post_order()
        {
            if (child_limit == 2) // binary tree
            {
                PostOrderIterator tmp = PostOrderIterator(root);
                return tmp;
            }
            else
                return PostOrderIterator(root, false);
        }

        PostOrderIterator end_post_order()
        {
            if (child_limit == 2) // binary tree
            {
                return this->root->parent;
            }
            return this->root->parent;
        }

        // bfs
        BFSIterator begin_bfs_scan()
        {
            BFSIterator tmp = BFSIterator(root);
            return tmp;
        }
        BFSIterator end_bfs_scan()
        {
            return this->root->parent;
        }
        // dfs
        DFSIterator begin_dfs_scan()
        {
            DFSIterator tmp = DFSIterator(root);
            return tmp;
        }
        DFSIterator end_dfs_scan()
        {
            return this->root->parent;
        }
        // min heap
        MinHeapIterator begin_min_heap()
        {
            MinHeapIterator tmp = MinHeapIterator(root);
            return tmp;
        }
        MinHeapIterator end_min_heap()
        {
            return this->root->parent;
        }

        //
    };

} // namespace ex4
