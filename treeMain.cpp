// omer.apter@msmail.ariel.ac.il
#include "Tree.hpp"
#include "Node.hpp"
#include "Complex.hpp"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace ex4;

int main()
{
    Node<Complex> root_node = Node<Complex>(Complex(1.1, 1.8));
    Tree<Complex> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);
    Node<Complex> n1 = Node<Complex>(Complex(0.5, 0.9));
    Node<Complex> n2 = Node<Complex>(Complex(1.0, -1.4));
    Node<Complex> n3 = Node<Complex>(Complex(1.9, 1.7));
    Node<Complex> n4 = Node<Complex>(Complex(0.3, -0.5));
    Node<Complex> n5 = Node<Complex>(Complex(0.5, 0.7));
    Node<Complex> n6 = Node<Complex>(Complex(1.2, 1.1));

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    tree.add_sub_node(n5, n6);

    // The tree should look like:
    /**
     *           root = 1.1+1.8i
     *         /            \
     *        0.5+0.9i       1.0-1.4i
     *       /      \         /
     *  1.9+1.7i  0.3-0.5i  0.5+0.7i
     *                      /
     *                  1.2+1.1i
     */
    
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        cout << node->get_value() << endl;
    } 
    cout << "//3" << endl;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        cout << node->get_value() << endl;
    } 
}