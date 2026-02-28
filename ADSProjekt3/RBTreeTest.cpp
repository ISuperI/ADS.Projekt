#define TEST_FILE test_RedBlackBST

#include "gip_mini_catch.h"
#include <vector>
#include "RedBlackBST.h"
#include <iostream>
using namespace std;

TEST_CASE("Pruefung der Methoden RedBlackBST::insert() - Simple")
{

	int numbers[8] = {30, 20, 40, 10, 25, 50, 22, 28};
	RedBlackBST tree;
	for (int i = 0; i < 8; i++)
	{
		tree.insert(numbers[i]);
	}

	REQUIRE(tree.getRoot()->val == 30);
	REQUIRE(tree.getRoot()->left->val == 20);
	REQUIRE(tree.getRoot()->left->left->val == 10);
	REQUIRE(tree.getRoot()->left->right->val == 25);
	REQUIRE(tree.getRoot()->left->right->left->val == 22);
	REQUIRE(tree.getRoot()->left->right->right->val == 28);
	REQUIRE(tree.getRoot()->right->val == 40);
	REQUIRE(tree.getRoot()->right->right->val == 50);
}

TEST_CASE("Pruefung der Methoden RedBlackBST::insert() - Doppelrotation")
{
	int numbers[9] = {30, 20, 40, 10, 25, 50, 22, 28, 26};
	RedBlackBST tree;
	for (int i = 0; i < 9; i++)
	{
		tree.insert(numbers[i]);
	}

	REQUIRE(tree.getRoot()->val == 25);
	REQUIRE(tree.getRoot()->left->val == 20);
	REQUIRE(tree.getRoot()->left->left->val == 10);
	REQUIRE(tree.getRoot()->left->right->val == 22);
	REQUIRE(tree.getRoot()->right->val == 30);
	REQUIRE(tree.getRoot()->right->left->val == 28);
	REQUIRE(tree.getRoot()->right->left->left->val == 26);
	REQUIRE(tree.getRoot()->right->right->val == 40);
	REQUIRE(tree.getRoot()->right->right->right->val == 50);
}

TEST_CASE("Pruefung der Methoden RedBlackBST::insert() - Doppelrotation2")
{
	int numbers[9] = {20, 10, 30, 25, 40, 22, 28, 50, 26};
	RedBlackBST tree;
	for (int i = 0; i < 9; i++)
	{
		tree.insert(numbers[i]);
	}

	REQUIRE(tree.getRoot()->val == 25);
	REQUIRE(tree.getRoot()->left->val == 20);
	REQUIRE(tree.getRoot()->left->left->val == 10);
	REQUIRE(tree.getRoot()->left->right->val == 22);
	REQUIRE(tree.getRoot()->right->val == 30);
	REQUIRE(tree.getRoot()->right->left->val == 28);
	REQUIRE(tree.getRoot()->right->left->left->val == 26);
	REQUIRE(tree.getRoot()->right->right->val == 40);
	REQUIRE(tree.getRoot()->right->right->right->val == 50);
}
