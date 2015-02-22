/*
 * bst.h
 *
 *  Created on: Apr 14, 2014
 *      Author: kempe and redekopp
 */

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/* -----------------------------------------------------
 * Exceptions
 ------------------------------------------------------*/

 
class KeyNotFoundException : public std::exception
{ // thrown when the user searches for a non-existing key
public:
   	KeyNotFoundException () throw () {}
	~KeyNotFoundException () throw () {}
};

/* -----------------------------------------------------
 * Regular Binary Tree Nodes
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class Node {
public:
	Node (const KeyType & k, const ValueType & v, Node<KeyType, ValueType> *p)
        // the default is to create new nodes as leaves
	{ _item.first = k; _item.second = v; _parent = p; _left = _right = NULL; }

	const std::pair<KeyType, ValueType> & getItem () const
	{ return _item; }

	//	std::pair<KeyType, ValueType> & getItem ()
	//	{ Return; }

	const KeyType & getKey () const
	{ return _item.first; }

	ValueType & getValue ()
	{ return _item.second; }

        /* the next three functions are virtual because for Red-Black-Trees,
           we'll want to use Red-Black nodes, and for those, the 
           getParent, getLeft, and getRight functions should return 
           Red-Black nodes, not just ordinary nodes.
           That's an advantage of using getters/setters rather than a struct. */

	virtual Node<KeyType, ValueType> *getParent () const
	{ return _parent; }

	virtual Node<KeyType, ValueType> *getLeft () const
	{ return _left; }

	virtual Node<KeyType, ValueType> *getRight () const
	{ return _right; }


	void setParent (Node<KeyType, ValueType> *p)
	{ _parent = p; }

	void setLeft (Node<KeyType, ValueType> *l)
	{ _left = l; }

	void setRight (Node<KeyType, ValueType> *r)
	{ _right = r; }

	virtual ~Node ()
	{ }

protected:
	std::pair<KeyType, ValueType> _item;
	Node <KeyType, ValueType> *_left, *_right, *_parent;
};

/* -----------------------------------------------------
 * Regular Binary Search Tree
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class BinarySearchTree {
public:
	BinarySearchTree () { root = NULL; }
	~BinarySearchTree () { deleteAll (root); }

	
	
	 ValueType & lookup (const KeyType & k) 
	{
		ValueType *value=new ValueType;
		try
		{
			if (find(root, k, value)==false)
			{	

				throw KeyNotFoundException();
			}
		
	
			else 
			{
				
				return *value;
			}
		}
		
			catch (KeyNotFoundException &error)
		{
			std::cout<<"Key not found in Tree"<<std::endl;
		}
		
	}
	  /* you need to implement the lookup function.
             It should throw a KeyNotFoundException if k is not in the tree.
             You are allowed/encouraged to create private helper functions.	   */  

	void print () const
	{ 
	/* prints the entire tree structure in a nice format, denoting subtrees in [] brackets.
	This could be helpful if you want to debug your functions. */
	     printRoot (root);
	     std::cout << "\n";
	}

	/*-------------------------------------
         * An In-Order Const iterator
	 *-------------------------------------*/
	class iterator {
	public:
	  iterator(Node<KeyType,ValueType>* root) 
	    {
	      curr = root;
	      if(curr){
		while(curr->getLeft()){
		  curr = curr->getLeft();
		}
	      }
	    }

	  const std::pair<KeyType,ValueType>& operator*() const
	    { return curr->getItem(); }

	  const std::pair<KeyType,ValueType>* operator->() const
	    { return &(curr->getItem()); }

	  bool operator==(const iterator& rhs) const
	  {
	    return curr == rhs.curr; 
	  }

	  bool operator!=(const iterator& rhs) const
	  {
	    return curr != rhs.curr;
	  }

	  iterator& operator++()
	  {
		/*std::cout<<"here"<<std::endl;
		
		std::cout<<"curr is "<<curr->getKey()<<std::endl;
			if(curr->getLeft())
			std::cout<<"left child is "<<curr->getLeft()->getKey()<<std::endl;
			else
			std::cout<<"left child is NULL"<<std::endl;
			if(curr->getRight())
			/std::cout<<"right child is "<<curr->getRight()->getKey()<<std::endl;
			else
			std::cout<<"right child is NULL"<<std::endl;*/
				
		if (curr==NULL)
		{
			curr=NULL;
		}
		else{
			Node<KeyType, ValueType> *p;
			if (curr->getRight() !=NULL)
			{
				curr=curr->getRight();
				
				while (curr->getLeft() != NULL)
				{
					curr=curr->getLeft();
				}
			}
			
			else
			{	
				p=curr->getParent();
				while (p !=NULL && (curr==p->getRight()) )
				{
					//std::cout << "curr: " << p->getValue() << std::endl;
					//std::cout << "pare: " << p->getParent() << std::endl;
					curr=p;
					p=p->getParent();
				}
				
				//std::cout << "assigning: " << p << std::endl;
				curr = p;
				if (p == NULL)
				{
					curr = NULL;
					return *this;
				}
					
			}
			
			}
			
				//this->curr = p;
				
		return *this;
		
	  }
	  

	  
	      // this one is yours to implement.
              // You are welcome to define private or protected
              // helper functions.
	  
	protected:
	  Node<KeyType, ValueType>* curr;
	};

	iterator begin() { iterator it (root); return it; }
	iterator end()   { iterator it (NULL); return it; }

 protected:
	Node<KeyType, ValueType> *root;
	//KeyNotFoundException error;
	bool find (Node<KeyType, ValueType> *currentNode, KeyType key, ValueType *value)
	{
		if (currentNode->getKey()==key)
		{
			*value=currentNode->getValue();
			return true;
		}
		else if (currentNode->getLeft()==NULL && currentNode->getRight()==NULL)//check if leaf of tree
		{
			return false;
		}
		else if (currentNode->getLeft()==NULL)//check if only has a left leaf
		{
			if (find(currentNode->getRight(),key, value))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (currentNode->getRight()==NULL)//check if only has a right leaf
		{
			if (find(currentNode->getLeft(),key, value))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			if (find(currentNode->getLeft(),key, value))
			{
				return true;
			}
			else if (find(currentNode->getRight(), key, value))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	
	void printRoot (Node<KeyType, ValueType> *r) const
	{
    	if (r != NULL)
	  {
		if(r->getParent()==NULL)
		{
			std::cout<<"FOUND PARENT!";
		}
	    std::cout << "[";
	    printRoot (r->getLeft());
	    std::cout << " (" << r->getKey() << ", " << r->getValue() << ") ";
    		printRoot (r->getRight());
    		std::cout << "]";
	  }
	}

	void deleteAll (Node<KeyType, ValueType> *r)
	{
	  if (r != NULL)
	    {
	      deleteAll (r->getLeft());
	      deleteAll (r->getRight());
	      delete r;
	    }
	}
};
