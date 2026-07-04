/*
File: AVLTree.h
Author: Adrian Jimenez
Description: AVLTree class implementation derived from BinaryTree class and lecture code.
All code in header to avoid linking errors related to Template use. Comments provided below for reasoning behind
implementation and methods. 

Rotation code is also derived from lecture.

Added getNode for periodicTable class and getRoot for ElementLookup BFS functionality.
Date: November 21, 2025
*/

#pragma once

#include <iostream>
#include <algorithm>
#include <stdexcept>

#ifndef AVLTREE
#define AVLTREE

template<class T>
struct AvlNode
{
	T Data;
	AvlNode<T>* left;
	AvlNode<T>* right;
	int height;

	AvlNode(const T& theData, AvlNode<T>* lt, AvlNode<T>* rt, int h = 0)
		: Data(theData), left(lt), right(rt), height(h) {
	} //AvlNode constructor
 	template <class U>
	friend class AVLTree; //friend class with the AVLTree
};

template<class T>
class AVLTree {
private:
	AvlNode<T>* Root;

	void insert(T data, AvlNode<T>*& root); //Insert a node into the proper location of the tree
	void remove(T data, AvlNode<T>*& root);	//Remove a specific node from the tree
	bool contains(T data, AvlNode<T>* n); //Report if the tree contains a specific piece of data
	AvlNode<T>* findMin(AvlNode<T>* n); //Find and return the smallest value in the tree
	AvlNode<T>*  findMax(AvlNode<T>* n); //Find and return the largest value in the tree

	void printTree(AvlNode<T>* n); //Visit each node in the tree and print the data to the screen.

public:
	AVLTree();
	bool isEmpty();	//Determine if the tree is empty

	//User friendly public interface methods (repeated)
	AvlNode<T>* findMin();
	AvlNode<T>* findMax();
	void insert(T data);
	void remove(T data);
	bool contains(T data);
	void printTree();

	int height(AvlNode<T>* root) const;

	//periodicTable functionality 
	AvlNode<T>* getNode(const T& data, AvlNode<T>* n);
	AvlNode<T>* getNode(const T& data);
	AvlNode<T>* getRoot() const; //for ElementLookup.cpp number BFS functionality

	void rotateWithLeftChild(AvlNode<T>*& k2) const; //rotation functions
	void rotateWithRightChild(AvlNode<T>*& k1) const;
	void doubleWithLeftChild(AvlNode<T>*& k3) const;
	void doubleWithRightChild(AvlNode<T>*& k1) const;
};

template<class T>
inline void AVLTree<T>::insert(T data, AvlNode<T>*& root)
{
	if (root == nullptr) //if node is empty, return tree where node is root
	{
		root = new AvlNode<T>(data, nullptr, nullptr, 0); //root without left/right child at height 0
		return;
	}
	else if (data < root->Data) //case where insert data is less than root data
	{
		insert(data, root->left); //recursive call, insert on corresponding side
		if (height(root->left) - height(root->right) == 2) //if height difference or balance factor of lh - rh is 2, Tree is left-heavy
		{
			if (data < root->left->Data)
				rotateWithLeftChild(root); //single left rotation
			else
				doubleWithLeftChild(root); //double rotation starting with left child
		}
	}
	else if (data > root->Data) //case where insert data is greater than root data
	{
		insert(data, root->right); //recursive call, insert on corresponding side
		if (height(root->right) - height(root->left) == 2) //if height difference or balance factor of rh - lh is 2
		{
			if (data > root->right->Data) //Check if tree is right-heavy or left-heavy
				rotateWithRightChild(root); //single right rotation
			else
				doubleWithRightChild(root); //double rotation starting with right child
		}
	}
	else
	{
		return;
	}

	root->height = std::max(height(root->left), height(root->right)) + 1; //decide which child is bigger and calculate the height
}

template<class T>
inline void AVLTree<T>::remove(T data, AvlNode<T>*& root)
{
	if (root == nullptr) //if tree is empty, nothing to remove
		return;

	if (data < root->Data) //case where removed data is less than root data
	{
		remove(data, root->left); //recursive call

		if (height(root->right) - height(root->left) > 1) //case where height difference violates ATLTree rule. 
		{
			if (height(root->right->right) >= height(root->right->left)) //check if right or left heavy
				rotateWithRightChild(root); //single right rotation
			else
				doubleWithRightChild(root); //double rotation with right child
		}
	}
	else if (data > root->Data)  //case where removed data is greater than root data
	{
		remove(data, root->right); //recursive call

		if (height(root->left) - height(root->right) > 1) // case where height difference violates ATLTree rule.
		{
			if (height(root->left->left) >= height(root->left->right)) //check if right or left heavy
				rotateWithLeftChild(root); //single left rotation
			else
				doubleWithLeftChild(root); //double rotation with left child
		}
	}
	else //when node is found
	{
		if (root->left == nullptr || root->right == nullptr) //case where root's left or right child are null
		{
			AvlNode<T>* temp = root->left ? root->left : root->right; //if left child exists and not empty, make it temp. otherwise make right child temp

			if (temp == nullptr) //case where temp (child) is null
			{
				temp = root;
				root = nullptr; //make root nullptr
			}
			else //if child exists
			{
				*root = *temp; //copy child into root
			}

			delete temp;
		}
		else
		{
			AvlNode<T>* temp = findMin(root->right); //copy minimum of right node to copy into root
			root->Data = temp->Data;
			remove(temp->Data, root->right); //remove original temp (right minimum) data
		}

		if (root != nullptr)
			root->height = std::max(height(root->left), height(root->right)) + 1; //recalculate height

		return; //return to end recursion
	}

	if (root != nullptr)
		root->height = std::max(height(root->left), height(root->right)) + 1; //recalculate height
}

template<class T>
inline bool AVLTree<T>::contains(T data, AvlNode<T>* n)
{
	if (n == NULL)
		return false;
	else if (data < n->Data)
		return contains(data, n->left); //recursive call on left child
	else if (data > n->Data)
		return contains(data, n->right); //recursive call on rignt child
	else
		return true; //if not found, last node will be null and be false, otherwise true
}

template<class T>
inline AvlNode<T>* AVLTree<T>::findMin(AvlNode<T>* n)
{
	if (n == NULL)
		throw std::runtime_error("Tree does not exist");

	if (n->left == NULL)
		return n; //return node if following node is null
	else
		return findMin(n->left); //recursive call
}

template<class T>
inline AvlNode<T>* AVLTree<T>::findMax(AvlNode<T>* n)
{
	if (n == NULL)
		throw std::runtime_error("Tree does not exist");

	if (n->right == NULL)
		return n; //return node if following node is null
	else
		return findMax(n->right); //recursive call
}

template<class T>
inline void AVLTree<T>::printTree(AvlNode<T>* n)
{
	if (n != NULL)
	{
		std::cout << n->Data << std::endl;
		this->printTree(n->left);
		this->printTree(n->right);
		//print each value at each level
	}
}

template<class T>
inline AVLTree<T>::AVLTree()
{
	this->Root = NULL; //defaly constructor null
}

template<class T>
inline bool AVLTree<T>::isEmpty()
{
	return this->Root == NULL; //check if empty
}

template<class T>
inline AvlNode<T>* AVLTree<T>::findMin()
{
	return this->findMin(this->Root); //user-friendly functionality
}

template<class T>
inline AvlNode<T>* AVLTree<T>::findMax()
{
	return this->findMax(this->Root); //user-friendly functionality
}

template<class T>
inline void AVLTree<T>::insert(T data)
{
	this->insert(data, this->Root); //user-friendly functionality
}

template<class T>
inline void AVLTree<T>::remove(T data)
{
	this->remove(data, this->Root); //user-friendly functionality
}

template<class T>
inline bool AVLTree<T>::contains(T data)
{
	return this->contains(data, this->Root); //user-friendly functionality
}

template<class T>
inline void AVLTree<T>::printTree()
{
	this->printTree(this->Root); //user-friendly functionality
}

template<class T>
inline int AVLTree<T>::height(AvlNode<T>* root) const
{
	return root == NULL ? -1 : root->height; //if null, height is -1. Otherwise is root height
}

template<class T>
inline void AVLTree<T>::rotateWithLeftChild(AvlNode<T>*& k2) const
{
	AvlNode<T>* k1 = k2->left; //code from lecture, case 1 single left rotation: updates heights, and changes root
	k2->left = k1->right;
	k1->right = k2;
	k2->height = std::max(height(k2->left), height(k2->right)) + 1;
	k1->height = std::max(height(k1->left), k2->height) + 1;
	k2 = k1;
}

template<class T>
inline void AVLTree<T>::rotateWithRightChild(AvlNode<T>*& k1) const
{
	AvlNode<T>* k2 = k1->right; //code from lecture, case 2 single right rotation: updates heights, and changes root
	k1->right = k2->left;
	k2->left = k1;
	k1->height = std::max(height(k1->left), height(k1->right)) + 1;
	k2->height = std::max(height(k2->right), k1->height) + 1;
	k1 = k2;
}

template<class T>
inline void AVLTree<T>::doubleWithLeftChild(AvlNode<T>*& k3) const
{
	rotateWithRightChild(k3->left); //code from lecture, case 3 double left rotation
	rotateWithLeftChild(k3);
}

template<class T>
inline void AVLTree<T>::doubleWithRightChild(AvlNode<T>*& k1) const
{
	rotateWithLeftChild(k1->right); //code from lecture, case 4 double right rotation
	rotateWithRightChild(k1);
}

template<class T>
inline AvlNode<T>* AVLTree<T>::getNode(const T& data, AvlNode<T>* n)
{
	if (n == nullptr)
		return nullptr; //if node null, return null
	if (data < n->Data)
		return getNode(data, n->left); //if data less than node, travel down left tree
	else if (data > n->Data)
		return getNode(data, n->right); //if data greater than node, travel down right tree
	else
		return n; //return node if not greater or less than
}

template<class T>
inline AvlNode<T>* AVLTree<T>::getNode(const T& data)
{
	return getNode(data, this->Root); //user friendly getNode function
}

template<class T>
inline AvlNode<T>* AVLTree<T>::getRoot() const
{
	return this->Root;
}


#endif
