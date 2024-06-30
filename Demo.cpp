/**
 * Demo app for Ex4
 */
#include <iostream>
#include <string>
#include "Node.hpp"
#include "Tree.hpp"

using namespace std;
using namespace ex4;

int main()
{

    Node<double> root_node = Node<double>(1.1);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);
    Node<double> n1 = Node<double>(1.2);
    Node<double> n2 = Node<double>(1.3);
    Node<double> n3 = Node<double>(1.4);
    Node<double> n4 = Node<double>(1.5);
    Node<double> n5 = Node<double>(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    // The tree should look like:
    /**
     *       root = 1.1
     *     /       \
     *    1.2      1.3
     *   /  \      /
     *  1.4  1.5  1.6
     */

    // for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    // {
    //     cout << node->get_value() << endl;
    // } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6

    // for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    // {
    //     cout << node->get_value() << endl;
    // } // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1

    // for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    // {
    //     cout << node->get_value() << endl;
    // } // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3

    // for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    // {
    //     cout << node->get_value() << endl;
    // } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    // for (auto node : tree)
    // {
    //     cout << node.get_value() << endl;
    // } // same as BFS: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    // cout << tree; // Should print the graph using GUI.
    root_node = Node<double>(1.1);
    n1 = Node<double>(1.2);
    n2 = Node<double>(1.3);
    n3 = Node<double>(1.4);
    n4 = Node<double>(1.5);
    n5 = Node<double>(1.6);

    Tree<double> three_ary_tree(3); // 3-ary tree.
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);

    cout << "3_ary_tree" << endl;

    for (auto node = three_ary_tree.begin_in_order(); node != three_ary_tree.end_in_order(); ++node)
    {
        cout << node->get_value() << endl;
    } // prints: 1.1, 1.5, 1.2, 1.6, 1.3, 1.4
    // The tree should look like:
    /**
     *       root = 1.1
     *     /      |     \
     *    1.2    1.3    1.4
     *   /        |
     *  1.5      1.6
     */
}
