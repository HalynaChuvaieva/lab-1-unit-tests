#define CATCH_CONFIG_MAIN
#include <iostream>
#include "catch.hpp"
#include "BinarySearchTree.h"
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
