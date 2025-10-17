#define CATCH_CONFIG_MAIN
#include <iostream>
#include "catch.hpp"
#include "BinarySearchTree.h"
#include "BalancedBST.h"
#include "TestBalancedBST.h"
#include "Graph.h"
#include <sstream>

TEST_CASE("BinarySearchTree Insert works correctly", "[BST][insert]")
{
    BinarySearchTree<int> bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);
    std::ostringstream output;
    std::streambuf *oldCout = std::cout.rdbuf(output.rdbuf());
    bst.display();
    std::cout.rdbuf(oldCout);
    REQUIRE(output.str() == "20 30 40 50 60 70 80 \n");
}
TEST_CASE("BinarySearchTree minValue returns smallest node", "[BST][minValue]")
{
    class BSTTester : public BinarySearchTree<int>
    {
    public:
        Node *getMin(Node *node) { return minValue(node); }
        Node *getRoot() { return this->root; }
    };
    BSTTester tester;
    tester.insert(10);
    tester.insert(5);
    tester.insert(15);
    tester.insert(3);
    auto minNode = tester.getMin(tester.getRoot());
    REQUIRE(minNode != nullptr);
    REQUIRE(minNode->key == 3);
}
TEST_CASE("BinarySearchTree deleteNode removes elements correctly", "[BST][delete]")
{
    BinarySearchTree<int> bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);
    bst.remove(20);
    std::ostringstream output1;
    std::streambuf *oldCout1 = std::cout.rdbuf(output1.rdbuf());
    bst.display();
    std::cout.rdbuf(oldCout1);
    REQUIRE(output1.str() == "30 40 50 60 70 80 \n");
    bst.remove(30);
    std::ostringstream output2;
    std::streambuf *oldCout2 = std::cout.rdbuf(output2.rdbuf());
    bst.display();
    std::cout.rdbuf(oldCout2);
    REQUIRE(output2.str() == "40 50 60 70 80 \n");
    bst.remove(50);
    std::ostringstream output3;
    std::streambuf *oldCout3 = std::cout.rdbuf(output3.rdbuf());
    bst.display();
    std::cout.rdbuf(oldCout3);
    REQUIRE(output3.str() == "40 60 70 80 \n");
}
TEST_CASE("BinarySearchTree handles empty tree correctly", "[BST][empty]")
{
    BinarySearchTree<int> bst;
    REQUIRE_NOTHROW(bst.remove(10));
    std::ostringstream output;
    std::streambuf *oldCout = std::cout.rdbuf(output.rdbuf());
    bst.display();
    std::cout.rdbuf(oldCout);
    REQUIRE(output.str() == "\n");
}
TEST_CASE("BinarySearchTree ignores duplicate insertions", "[BST][duplicates]")
{
    BinarySearchTree<int> bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(10);
    bst.insert(15);
    std::ostringstream output;
    std::streambuf *oldCout = std::cout.rdbuf(output.rdbuf());
    bst.display();
    std::cout.rdbuf(oldCout);
    REQUIRE(output.str() == "5 10 15 \n");
}
TEST_CASE("BinarySearchTree delete single element", "[BST][single]")
{
    BinarySearchTree<int> bst;
    bst.insert(42);
    bst.remove(42);
    std::ostringstream output;
    std::streambuf *oldCout = std::cout.rdbuf(output.rdbuf());
    bst.display();
    std::cout.rdbuf(oldCout);
    REQUIRE(output.str() == "\n");
}

TEST_CASE("BalancedBST getHeight returns 0 for empty tree", "[BalancedBST][height][empty]")
{
    TestBalancedBST<int> tree;
    REQUIRE(tree.getHeight() == 0);
}

TEST_CASE("BalancedBST getHeight returns 1 for single node", "[BalancedBST][height][single]")
{
    TestBalancedBST<int> tree;
    tree.insert(10);
    REQUIRE(tree.getHeight() == 1);
}

TEST_CASE("BalancedBST getHeight for balanced tree", "[BalancedBST][height][balanced]")
{
    TestBalancedBST<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);
    REQUIRE(tree.getHeight() == 3);
}

TEST_CASE("BalancedBST getHeight for left-skewed tree", "[BalancedBST][height][left]")
{
    TestBalancedBST<int> tree;
    tree.insert(5);
    tree.insert(4);
    tree.insert(3);
    tree.insert(2);
    tree.insert(1);
    REQUIRE(tree.getHeight() == 5);
}

TEST_CASE("BalancedBST getHeight for right-skewed tree", "[BalancedBST][height][right]")
{
    TestBalancedBST<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    REQUIRE(tree.getHeight() == 5);
}

TEST_CASE("Graph addEdge adds edges in both directions", "[Graph][addEdge]")
{
    Graph<int> g;
    g.addEdge(1, 2);
    g.addEdge(1, 3);

    REQUIRE(g.adj[1] == std::vector<int>{2, 3});
    REQUIRE(g.adj[2] == std::vector<int>{1});
    REQUIRE(g.adj[3] == std::vector<int>{1});
}

TEST_CASE("Graph buildSpanningTree builds a correct DFS tree", "[Graph][spanningTree]")
{
    Graph<int> g;
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 5);

    std::ostringstream output;
    std::streambuf *oldCout = std::cout.rdbuf(output.rdbuf());
    g.buildSpanningTree(1);
    std::cout.rdbuf(oldCout);

    std::string out = output.str();
    REQUIRE(out.find("Spanning tree consists of edges:") != std::string::npos);

    REQUIRE(
        (out.find("1 - 2") != std::string::npos &&
         out.find("1 - 3") != std::string::npos));
}

TEST_CASE("Graph bfs traverses in correct order", "[Graph][bfs]")
{
    Graph<int> g;
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 5);

    std::ostringstream output;
    std::streambuf *oldCout = std::cout.rdbuf(output.rdbuf());
    g.bfs(1);
    std::cout.rdbuf(oldCout);

    std::string expectedPrefix = "BFS traversal starting from 1: ";
    REQUIRE(output.str().find(expectedPrefix) == 0);

    REQUIRE(output.str().find("1 2 3 4 5") != std::string::npos);
}

TEST_CASE("Graph bfs handles isolated vertex", "[Graph][bfs][isolated]")
{
    Graph<int> g;
    g.addEdge(1, 2);
    g.addEdge(3, 4);

    std::ostringstream output;
    std::streambuf *oldCout = std::cout.rdbuf(output.rdbuf());
    g.bfs(3);
    std::cout.rdbuf(oldCout);

    REQUIRE(output.str().find("BFS traversal starting from 3: 3 4") != std::string::npos);
}
