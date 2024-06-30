#include <vector>
#include "Node.hpp"
#include <map>
#include <deque>
#include <functional>
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
                    node.last_child = &child;
                }
                child.parent = &node;
                node.num_of_children++;
            }
        }
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

        // start of iterators
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

        // iterator calls
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
        BFSIterator begin_bfs_scan()
        {
            if (child_limit == 2) // binary tree
            {
                BFSIterator tmp = BFSIterator(root);
                return tmp;
            }
            return BFSIterator();
        }
        BFSIterator end_bfs_scan()
        {
            return this->root->parent;
        }
        DFSIterator begin_dfs_scan()
        {
            DFSIterator tmp = DFSIterator(root);
            return tmp;
        }
        DFSIterator end_dfs_scan()
        {
            return this->root->parent;
        }
        //
    };

} // namespace ex4
