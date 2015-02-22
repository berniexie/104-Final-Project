/*
 * rbbst.h
 *
 *  Created on: Apr 14, 2014
 *      Author: kempe
 */

#include <iostream>
#include <exception>
#include <cstdlib>
#include "bst.h"
using namespace std;
/* -----------------------------------------------------
 * Red-Black Nodes 
 ------------------------------------------------------*/

enum Color {red, black};

template <class KeyType, class ValueType>
class RedBlackNode : public Node<KeyType, ValueType>
{
public:
	RedBlackNode (KeyType k, ValueType v, RedBlackNode<KeyType, ValueType> *p)
	: Node<KeyType, ValueType> (k, v, p)
	  { color = red; }
	
	RedBlackNode (Node<KeyType, ValueType> *p)//used only in the case of converting root to a redblacknode
	: Node<KeyType, ValueType>(p->getKey(), p->getValue(), NULL)
	{ color = red;}
	virtual ~RedBlackNode () {}

	Color getColor () const
	{ return color; }

	void setColor (Color c)
	{ color = c; }

        /* The type casting allows us to treat getParent, getLeft, getRight
           as returning RedBlackNode instead of Node */
	virtual RedBlackNode<KeyType, ValueType> *getParent () const
	{ return (RedBlackNode<KeyType,ValueType>*) this->_parent; }

	virtual RedBlackNode<KeyType, ValueType> *getLeft () const
	{ return (RedBlackNode<KeyType,ValueType>*) this->_left; }

	virtual RedBlackNode<KeyType, ValueType> *getRight () const
	{ return (RedBlackNode<KeyType,ValueType>*) this->_right; }

protected:
	Color color;
};

/* -----------------------------------------------------
 * Red-Black Search Tree
 ------------------------------------          */
template <class KeyType, class ValueType>
class RedBlackTree : public BinarySearchTree<KeyType, ValueType>
{

public:
RedBlackTree() { rb_root = NULL; }
RedBlackNode<KeyType, ValueType>* rb_root;

  RedBlackNode<KeyType, ValueType>* check_node(KeyType key, ValueType value, RedBlackNode<KeyType, ValueType> *curr, bool &left, bool &right)//returns the parent while inserting the node
  {
	if (key==curr->getKey())//if key already in tree, replace value with new value
	{
		curr->getValue()=value;
	}
	if (key < curr->getKey() && curr->getLeft()==NULL)
	{
		RedBlackNode<KeyType,ValueType> *add_Node= new RedBlackNode<KeyType,ValueType>(key,value,curr);//the node to be added with the given key and value
		curr->setLeft(add_Node);
		left=1;
		return curr;//return parent of the node you just added
	}
	else if (key > curr->getKey() && curr->getRight()==NULL)
	{
		RedBlackNode<KeyType,ValueType> *add_Node= new RedBlackNode<KeyType,ValueType>(key,value,curr);
		curr->setRight(add_Node);
		right=1;
		return curr;//return parent of the node you just added
	}
	else if (key < curr->getKey() && curr->getLeft()!=NULL)
	{
		return check_node(key,value, curr->getLeft(),left,right);
	}
	else if (key > curr->getKey() && curr->getRight()!=NULL)
	{
		return check_node(key, value ,curr->getRight(),left,right);
	}
	
  }
  
void add(KeyType key, ValueType value)
{
	//cout<<"adding"<<key<<endl;
  	bool left=0;
	bool right=0;
	//STEP ONE OF THE INSERTION ALGORITHM, INSERT NODE INTO NORMAL BST LOCATION
	if (rb_root==NULL)//if empty tree no root
	{
		//cout<<"i'm at empty tree"<<endl;
		RedBlackNode<KeyType,ValueType> *add_Node= new RedBlackNode<KeyType,ValueType>(key, value ,NULL);//the node to be added with the given key and value
		add_Node->setColor(black);//case 3
		if (add_Node->getParent()==NULL)
		{
			//cout<<"root has no parent"<<endl;
		}
	
		rb_root=add_Node;
		BinarySearchTree<KeyType, ValueType>::root=rb_root;
	}
	else//if has at least root
	{
		if(BinarySearchTree<KeyType, ValueType>::root->getParent()==NULL)
		{
			//cout<<"root still has no parent"<<endl;
		}
		if (BinarySearchTree<KeyType, ValueType>::root->getParent()!=NULL)
		{
			//cout<<"now he has a parent..."<<endl;
		}
		//RedBlackNode<KeyType,ValueType> *root1 = new RedBlackNode<KeyType, ValueType>(BinarySearchTree<KeyType, ValueType>::root);
		RedBlackNode<KeyType,ValueType> *parent = check_node(key, value,rb_root, left, right);
		//STEP TWO, CHECK COLOR OF NODE PARENT
		
		
				fixTree(parent,left,right);
				

	
	}
}
  
  void fixTree(RedBlackNode<KeyType, ValueType> *parent, bool left, bool right)
  {
  
			RedBlackNode<KeyType, ValueType>* uncle;
			if (parent->getParent()==NULL && parent->getColor()==red)//checking if parent is a root and red
			{
				parent->setColor(black);//if parent is a root or case 3
			}
			
			else if(parent->getParent()!=NULL)//sets grandparent if parent is not root
			{
				RedBlackNode<KeyType, ValueType>*   grandparent=parent->getParent();
					
					
				
				bool n_uncle=0;
					if (parent==(grandparent->getLeft()))//if parent is left child
					{
						if(grandparent->getRight()!=NULL)//making sure there is an uncle
						{
							 uncle=grandparent->getRight();//sets uncle to right child
						}
						else
						{
							n_uncle=1;
						}
					}
					else if (parent==(grandparent->getRight()))//if parent is right child
					{
						if (grandparent->getLeft()!=NULL)// if parent has sibling (uncle)
						{
							uncle=grandparent->getLeft();//sets uncle to left child
						}
							
						else
						{
							n_uncle=1;
						}
					}
						
						
				if (parent->getColor()==red)//if two consecutive reds
				{
						if(n_uncle==1 || (uncle->getColor()==black))// checking for cases 4 and 5, if uncle is black or if no uncle
						{
							if (parent==(grandparent->getLeft()) && left==1)//case 4
							{
								//cout<<"doing case 4"<<endl;
								rightRotation(parent, grandparent);
							}
							else if (parent==(grandparent->getRight()) && right==1)//case 5 - straight line to the right
							{
								leftRotation(parent, grandparent);
							}
							else if (parent==(grandparent->getLeft()) && right==1)//case 5 - zigzag parent left child then inserted node is right child 
							{
								leftRotation(parent->getRight(), parent);
								rightRotation(parent->getParent(), grandparent);//I do getParent here because after the left rotation, the old "parent" is now the child of the previous "child"
							}
							else if (parent==(grandparent->getRight()) && left==1)//case 5 - zigzag parent right child then inserted node is left child 
							{
									rightRotation(parent->getLeft(), parent);
									leftRotation(parent->getParent(), grandparent);
							}
						}
						else if (uncle->getColor()==red)//cases 1 and 2, if uncle is red
						{
							//cout<<"DOING RECOLOR"<<endl;
								parent->setColor(black);
								uncle->setColor(black);
								grandparent->setColor(red);
								
								if (grandparent->getParent()==NULL)//grandparent is root
								{
									grandparent->setColor(black);//case three
								}
								//setting up grandparent for calling fixTree again
								else if(grandparent->getParent()!=NULL)//recusively calls fixtree on the grandparent now
								{
									//cout<<"recursively calling fixtree"<<endl;
									bool left2=false;
									bool right2=false;
											if(grandparent==(grandparent->getParent())->getLeft())//setting up if grandparent is a left or right child
											{
												left2=true;
											}
											else
											{
												right2=true;
											}
											//cout<<left2<<right2<<endl;
												fixTree(grandparent->getParent(),left2,right2);
												
											
								}
									
							
						
								
						}
				}
			}
			
  }
  
  void rightRotation(RedBlackNode<KeyType, ValueType>* one_node, RedBlackNode<KeyType, ValueType> * two_node)//two_node is the parent of one_node
  {
	//cout<<"performing right rotation"<<endl;
	//cout<<"one node is: "<<one_node->getKey()<<"color is :"<<one_node->getColor()<<endl;
	//cout<<"two node is: "<<two_node->getKey()<<"color is :"<<two_node->getColor()<<endl;
		if(two_node->getParent()==NULL)//if top node was already root
		{
			//cout<<"grandparent was root"<<endl;
			one_node->setColor(black);
			two_node->setLeft(one_node->getRight());
			
			if ((one_node->getRight())!=NULL)//if there is a child node whose parent i have to switch, then i switch its parents
			(one_node->getRight())->setParent(two_node);//setting parent correctly
			
			one_node->setRight(two_node);
			one_node->setParent(NULL);
			two_node->setParent(one_node);
			two_node->setColor(red);
			rb_root=one_node;//new root
			BinarySearchTree<KeyType, ValueType>::root=rb_root;
		//	cout<<"one node is: "<<one_node->getKey()<<"color is :"<<one_node->getColor()<<endl;
	//cout<<"two node is: "<<two_node->getKey()<<"color is :"<<two_node->getColor()<<endl;
		}
		else
		{
			
			one_node->setColor(black);
			two_node->setLeft(one_node->getRight());
			
			if ((one_node->getRight())!=NULL)
			(one_node->getRight())->setParent(two_node);//setting parent correctly
			
			one_node->setRight(two_node);
			one_node->setParent(two_node->getParent());
			//wo_node->setParent(one_node);
			two_node->setColor(red);
			
			if (two_node==(two_node->getParent())->getLeft())//if left child
			{
				(two_node->getParent())->setLeft(one_node);
			}
			else//right child
			{
			
				(two_node->getParent())->setRight(one_node);
			}
			
			two_node->setParent(one_node);
		}
  }
  void leftRotation(RedBlackNode<KeyType, ValueType>* one_node, RedBlackNode<KeyType, ValueType> * two_node)//two_node is the parent of one_node
  {
	//	cout<<"performing left rotation"<<endl;
		//cout<<one_node->getKey()<<"color is :"<<one_node->getColor()<<endl;
		//cout<<two_node->getKey()<<"color is :"<<two_node->getColor()<<endl;
	if(two_node->getParent()==NULL)//if top node was already root
		{
			
			one_node->setColor(black);
			two_node->setRight(one_node->getLeft());
			
			if ((one_node->getLeft())!=NULL)//if there is a child node whose parent i have to switch, then i switch its parents
			(one_node->getLeft())->setParent(two_node);//setting parent correctly
			
			one_node->setLeft(two_node);
			one_node->setParent(NULL);
			two_node->setParent(one_node);
			two_node->setColor(red);
			rb_root=one_node;//new root
			BinarySearchTree<KeyType, ValueType>::root=rb_root;
		}
	else
		{
			
			one_node->setColor(black);
			two_node->setRight(one_node->getLeft());
			
			if ((one_node->getLeft())!=NULL)//if there is a child node whose parent i have to switch, then i switch its parents
			(one_node->getLeft())->setParent(two_node);//setting parent correctly
			
			one_node->setLeft(two_node);
			one_node->setParent(two_node->getParent());
		
			two_node->setColor(red);
			if (two_node==(two_node->getParent())->getLeft())//if left child
			{
				(two_node->getParent())->setLeft(one_node);
			}
			else//right child
			{
			
				(two_node->getParent())->setRight(one_node);
			}
				two_node->setParent(one_node);
		}
		
  }
  
  

  
  /* This one is yours to implement.
     It should add the (key, value) pair to the tree, 
     making sure that it remains a valid Red-Black Tree.
     If the key is already in the tree (with a possibly different associated value),
     then it should overwrite the value with the new one.
     We strongly recommend defining suitable (private) helper functions. */
};


















