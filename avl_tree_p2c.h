// Ali Faiyaz
// AVL Tree Class for Assignment 2
// Implementation of the AVL Tree and its member functions
// Double rotation has been changed and dont call single rotation functions in it anymore. It was implemented directly in the double rotation function.

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream>
using namespace std;

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
public:
	AvlTree( ) : root{ nullptr }
	{ }

	AvlTree( const AvlTree & rhs ) : root{ nullptr }
	{
		root = clone( rhs.root );
	}

	AvlTree( AvlTree && rhs ) : root{ rhs.root }
	{
		rhs.root = nullptr;
	}

	~AvlTree( )
	{
		makeEmpty( );
	}

	/**
	 * Deep copy.
	 */
	AvlTree & operator=( const AvlTree & rhs )
	{
		AvlTree copy = rhs;
		std::swap( *this, copy );
		return *this;
	}

	/**
	 * Move.
	 */
	AvlTree & operator=( AvlTree && rhs )
	{
		std::swap( root, rhs.root );

		return *this;
	}

	/**
	 * Find the smallest item in the tree.
	 * Throw UnderflowException if empty.
	 */
	const Comparable & findMin( ) const
	{
		if( isEmpty( ) )
			throw UnderflowException{ };
		return findMin( root )->element;
	}

	/**
	 * Find the largest item in the tree.
	 * Throw UnderflowException if empty.
	 */
	const Comparable & findMax( ) const
	{
		if( isEmpty( ) )
			throw UnderflowException{ };
		return findMax( root )->element;
	}

	/**
	 * Returns true if x is found in the tree.
	 */
	bool contains( const Comparable & x ) const
	{
		return contains( x, root );
	}

	/**
	 * Test if the tree is logically empty.
	 * Return true if empty, false otherwise.
	 */
	bool isEmpty( ) const
	{
		return root == nullptr;
	}

	/**
	 * Print the tree contents in sorted order.
	 */
	void printTree( ) const
	{
		if( isEmpty( ) )
			cout << "Empty tree" << endl;
		else
			printTree( root );
	}

	/**
	 * Make the tree logically empty.
	 */
	void makeEmpty( )
	{
		makeEmpty( root );
	}

	/**
	 * Insert x into the tree; duplicates are ignored.
	 */
	void insert( const Comparable & x )
	{
		insert( x, root );
	}

	/**
	 * Insert x into the tree; duplicates are ignored.
	 */
	void insert( Comparable && x )
	{
		insert( std::move( x ), root );
	}

	/**
	 * Remove x from the tree. Nothing is done if x is not found.
	 */
	void remove( const std::string & x )
	{
		remove( x, root );
	}
	int getSuccessRemove(){
		return success_remove; // return number of removed successfully
	}
	int getRemoveCalls(){
		return calls_remove; // return number of call removed
	}
	void setRemoveCalls(){
		calls_remove = 0; // set number of call removed to 0
	}
	
	std::string find( const std::string & x ) 
	{
		return find( x, root ); 
	}
	int getPassCounter() const{
		return pass_counter; // return number of successful find calls
	}
	int getFindCounter()const{
		return find_counter; // return number of find calls
	}
	void setFindCounter(){
		find_counter = 0;
	}
	
	int internal(){
		return internal(root,0); // returns the internal length of the tree
	}
	int nodeCount(){
		return nodeCount(root); // returns the number of nodes in the tree
	}


private:
	struct AvlNode
	{
		Comparable element;
		AvlNode   *left;
		AvlNode   *right;
		int       height;

		AvlNode( const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0 )
			: element{ ele }, left{ lt }, right{ rt }, height{ h } { }

		AvlNode( Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0 )
			: element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h } { }
	};

	AvlNode *root;


	/**
	 * Internal method to insert into a subtree.
	 * x is the item to insert.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
	void insert( const Comparable & x, AvlNode * & t )
	{
		if( t == nullptr )
			t = new AvlNode{ x, nullptr, nullptr };
		else if( x < t->element )
			insert( x, t->left );
		else if( t->element < x )
			insert( x, t->right );
		else {
			t->element.Merge(x); // merge the two elements (this was added)
		}

		balance( t );
	}

	/**
	 * Internal method to insert into a subtree.
	 * x is the item to insert.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
	void insert( Comparable && x, AvlNode * & t )
	{
		if( t == nullptr )
			t = new AvlNode{ std::move( x ), nullptr, nullptr };
		else if( x < t->element )
			insert( std::move( x ), t->left );
		else if( t->element < x )
			insert( std::move( x ), t->right );
		else{
			t->element.Merge(std::move(x)); // merge the two elements (this was added)
		}

		balance( t );
	}

	/**
	 * Internal method to remove from a subtree.
	 * x is the item to remove.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
	int success_remove = 0; // removed successfully
	int calls_remove = 0; // calls removed 
	void remove( const std:: string & x, AvlNode * & t )
	{
		calls_remove++; // increment the number remove calls (counter)
		if( t == nullptr )
			return;   // Item not found; do nothing

		if( x < t->element.getRecSequence() ) 
		{
			remove( x, t->left );
		}
		else if( t->element.getRecSequence()< x )
		{
			remove( x, t->right );
		}
			
		else if( t->left != nullptr && t->right != nullptr ) // Two children
		{
			//calls_remove++;
			t->element = findMin( t->right )->element;
			remove( t->element.getRecSequence(), t->right );
		}
		else
		{
			success_remove++;
			AvlNode *oldNode = t;
			t = ( t->left != nullptr ) ? t->left : t->right;
			delete oldNode;
		}

		balance( t );
	}

	static const int ALLOWED_IMBALANCE = 1;

	// Assume t is balanced or within one of being balanced
	void balance( AvlNode * & t )
	{
		if( t == nullptr )
			return;

		if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE ) {
			if( height( t->left->left ) >= height( t->left->right ) )
				rotateWithLeftChild( t );
			else
				doubleWithLeftChild( t );
		} else if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE ) {
			if( height( t->right->right ) >= height( t->right->left ) )
				rotateWithRightChild( t );
			else
				doubleWithRightChild( t );
		}
		t->height = max( height( t->left ), height( t->right ) ) + 1;
	}

	/**
	 * Internal method to find the smallest item in a subtree t.
	 * Return node containing the smallest item.
	 */
	AvlNode * findMin( AvlNode *t ) const
	{
		if( t == nullptr )
			return nullptr;
		if( t->left == nullptr )
			return t;
		return findMin( t->left );
	}

	/**
	 * Internal method to find the largest item in a subtree t.
	 * Return node containing the largest item.
	 */
	AvlNode * findMax( AvlNode *t ) const
	{
		if( t != nullptr )
			while( t->right != nullptr )
				t = t->right;
		return t;
	}

	/**
	 * Internal method to test if an item is in a subtree.
	 * x is item to search for.
	 * t is the node that roots the tree.
	 */
	bool contains( const Comparable & x, AvlNode *t ) const
	{
		if( t == nullptr )
			return false;
		else if( x < t->element )
			return contains( x, t->left );
		else if( t->element < x )
			return contains( x, t->right );
		else
			return true;    // Match
	}
	/****** NONRECURSIVE VERSION*************************
	    bool contains( const Comparable & x, AvlNode *t ) const
	    {
	        while( t != nullptr )
	            if( x < t->element )
	                t = t->left;
	            else if( t->element < x )
	                t = t->right;
	            else
	                return true;    // Match
	        return false;   // No match
	    }
	*****************************************************/

	int pass_counter = 0; // when passed through,increment
	int find_counter = 0; // everytime, anything is found in the tree it is incremented

	// used to locate each locate each node of its rec and enzymes
	std::string find( const std::string & x, AvlNode *t ){ 
		if( t == nullptr )
			return "Not Found"; // if not found return not found
		else if( x < t->element.getRecSequence()){
			find_counter++; 
			return find( x, t->left ); 
		}
		else if( t->element.getRecSequence() < x ){
			find_counter++;
			return find( x, t->right ); 
		}
		else{
			pass_counter++;
			return t->element.getEnzymeAcro(); // returns the enzyme acrocynm with the string passed in
		}
	}
	/**
	 * Internal method to make subtree empty.
	 */
	void makeEmpty( AvlNode * & t )
	{
		if( t != nullptr )
		{
			makeEmpty( t->left );
			makeEmpty( t->right );
			delete t;
		}
		t = nullptr;
	}

	/**
	 * Internal method to print a subtree rooted at t in sorted order.
	 */
	void printTree( AvlNode *t ) const
	{
		if( t != nullptr )
		{
			printTree( t->left );
			cout << t->element << endl;
			printTree( t->right );
		}
	}

	/**
	 * Internal method to clone subtree.
	 */
	AvlNode * clone( AvlNode *t ) const
	{
		if( t == nullptr )
			return nullptr;
		else
			return new AvlNode{ t->element, clone( t->left ), clone( t->right ), t->height };
	}
	// Avl manipulations
	/**
	 * Return the height of node t or -1 if nullptr.
	 */
	int height( AvlNode *t ) const
	{
		return t == nullptr ? -1 : t->height;
	}

	int max( int lhs, int rhs ) const
	{
		return lhs > rhs ? lhs : rhs;
	}

	/**
	 * Rotate binary tree node with left child.
	 * For AVL trees, this is a single rotation for case 1.
	 * Update heights, then set new root.
	 */
	void rotateWithLeftChild( AvlNode * & k2 )
	{
		AvlNode *k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
		k1->height = max( height( k1->left ), k2->height ) + 1;
		k2 = k1;
	}

	/**
	 * Rotate binary tree node with right child.
	 * For AVL trees, this is a single rotation for case 4.
	 * Update heights, then set new root.
	 */
	void rotateWithRightChild( AvlNode * & k1 )
	{
		AvlNode *k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;
		k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
		k2->height = max( height( k2->right ), k1->height ) + 1;
		k1 = k2;
	}

	    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild( AvlNode * & k3 )
    {
        AvlNode *k1 = k3->left;
        AvlNode *k2 = k1->right;
        //Rotate k2 with k1 (first rotation)
        k1->right = k2->left;
        k2->left = k1;
        //Rotate k3 with k2 (second rotation)
        k3->left = k2->right;
        k2->right = k3;
        //Adjusted heights
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k3->height = max( height( k3->left ), height( k3->right ) ) + 1;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k3 = k2;
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( AvlNode * & k1 )
    {
        AvlNode *k3 = k1->right;
        AvlNode *k2 = k3->left;
        //Rotate k2 with k1 (first rotation)
        k3->left = k2->right;
        k2->right = k3;
        //Rotate k3 with k2 (second rotation)
        k1->right = k2->left;
        k2->left = k1;
        //Adjusted heights
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k3->height = max( height( k3->left ), height( k3->right ) ) + 1;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1 = k2;
    
    }

	// function that calculates the number of nodes in the tree (helper function)
	int nodeCount(AvlNode * & t)const{
		if(t == nullptr){
			return 0;
		}
		return 1 + nodeCount(t->left) + nodeCount(t->right); // returns the number of nodes in the tree
	}

	// finds the internal depth of the tree (helper function)
	int internal(AvlNode * & t, int depth = 0)const{
		if(t == nullptr){
			return 0; 
		}
		return depth + internal(t->left, depth+1) + internal(t->right, depth+1); // depth + left + right
	}

};

#endif