#define CATCH_CONFIG_MAIN
#include <iostream>
#include "catch.hpp"
#include "BinarySearchTree.h"
#include "BalancedBST.h"
#include "TestBalancedBST.h"
#include "Graph.h"
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

template <typename Func>
std::string captureCout(Func func)
{
    std::ostringstream output;
    std::streambuf *oldCout = std::cout.rdbuf(output.rdbuf());
    func();
    std::cout.rdbuf(oldCout);
    return output.str();
}
std::vector<int> parseOutputToVector(const std::string &output)
{
    std::vector<int> result;
    size_t start = output.find(':');

    if (start == std::string::npos)
    {
        start = 0;
    }
    else
    {
        start += 1;
    }

    std::stringstream ss(output.substr(start));
    int value;

    while (ss >> value)
    {
        result.push_back(value);
    }
    return result;
}

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

    std::string output = captureCout([&]()
                                     { bst.display(); });
    std::vector<int> actual = parseOutputToVector(output);
    std::vector<int> expected = {20, 30, 40, 50, 60, 70, 80};
    REQUIRE(actual == expected);
}
TEST_CASE("BinarySearchTree minValue returns smallest node", "[BST][minValue]")
{
    class BSTTester : public BinarySearchTree<int>
    {
    public:
        using Node = typename BinarySearchTree<int>::Node;

        Node *getMin(Node *node) { return this->minValue(node); }
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
    std::string output1 = captureCout([&]()
                                      { bst.display(); });
    REQUIRE(parseOutputToVector(output1) == std::vector<int>{30, 40, 50, 60, 70, 80});
    bst.remove(30);
    std::string output2 = captureCout([&]()
                                      { bst.display(); });
    REQUIRE(parseOutputToVector(output2) == std::vector<int>{40, 50, 60, 70, 80});
    bst.remove(50);
    std::string output3 = captureCout([&]()
                                      { bst.display(); });
    REQUIRE(parseOutputToVector(output3) == std::vector<int>{40, 60, 70, 80});
}
TEST_CASE("BinarySearchTree handles empty tree correctly", "[BST][empty]")
{
    BinarySearchTree<int> bst;
    REQUIRE_NOTHROW(bst.remove(10));
    std::string output = captureCout([&]()
                                     { bst.display(); });

    REQUIRE(parseOutputToVector(output).empty());
}

TEST_CASE("BinarySearchTree ignores duplicate insertions", "[BST][duplicates]")
{
    BinarySearchTree<int> bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(10);
    bst.insert(15);

    std::string output = captureCout([&]()
                                     { bst.display(); });
    REQUIRE(parseOutputToVector(output) == std::vector<int>{5, 10, 15});
}

TEST_CASE("BinarySearchTree delete single element", "[BST][single]")
{
    BinarySearchTree<int> bst;
    bst.insert(42);
    bst.remove(42);
    std::string output = captureCout([&]()
                                     { bst.display(); });
    REQUIRE(parseOutputToVector(output).empty());
}

TEST_CASE("BinarySearchTree remove non-existent key leaves tree unchanged", "[BST][remove][non-existent]")
{
    BinarySearchTree<int> bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);

    REQUIRE_NOTHROW(bst.remove(99));
    std::string output = captureCout([&]()
                                     { bst.display(); });
    std::vector<int> actual = parseOutputToVector(output);
    std::vector<int> expected = {5, 10, 15};

    REQUIRE(actual == expected);
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

    std::vector<int> adj1 = g.adj[1];
    std::vector<int> adj2 = g.adj[2];
    std::vector<int> adj3 = g.adj[3];

    std::sort(adj1.begin(), adj1.end());
    std::sort(adj2.begin(), adj2.end());
    std::sort(adj3.begin(), adj3.end());

    REQUIRE(g.adj[1] == std::vector<int>{2, 3});
    REQUIRE(g.adj[2] == std::vector<int>{1});
    REQUIRE(g.adj[3] == std::vector<int>{1});
}g

TEST_CASE("Graph buildSpanningTree returns correct DFS edges", "[Graph][spanningTree]")
{
    Graph<int> g;
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    std::vector<std::pair<int, int>> actualEdges = g.buildSpanningTree(1);
    std::vector<std::pair<int, int>> expectedEdges = {
        {1, 2},
        {2, 4},
        {1, 3},
        {3, 5}};
    std::sort(actualEdges.begin(), actualEdges.end());
    std::sort(expectedEdges.begin(), expectedEdges.end());

    REQUIRE(actualEdges.size() == 4);
    REQUIRE(actualEdges == expectedEdges);
}

TEST_CASE("Graph bfs traverses in correct order", "[Graph][bfs]")
{
    Graph<int> g;
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    std::string output = captureCout([&]()
                                     { g.bfs(1); });
    std::vector<int> actualTraversal = parseOutputToVector(output);
    std::vector<int> expectedTraversal = {1, 2, 3, 4, 5};
    REQUIRE(output.find("BFS traversal starting from 1:") != std::string::npos);
    REQUIRE(actualTraversal == expectedTraversal);
}

TEST_CASE("Graph bfs handles isolated vertex", "[Graph][bfs][isolated]")
{
    Graph<int> g;
    g.addEdge(1, 2);
    g.addEdge(3, 4);
    std::string output = captureCout([&]()
                                     { g.bfs(3); });
    std::vector<int> actualTraversal = parseOutputToVector(output);
    std::vector<int> expectedTraversal = {3, 4};

    REQUIRE(output.find("BFS traversal starting from 3:") != std::string::npos);
    REQUIRE(actualTraversal == expectedTraversal);
}
