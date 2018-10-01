// William Kirkpatrick
// Lab02
// LinkedList.cpp

// tom bailey   0745  5 oct 2010
// Definition of methods for the List class.
#include "stdafx.h"
#include "LinkedList.h"

#include <utility>


List::List()
	: first_(NULL), size_(0), sum_(0)
{
}


List::List(const List & other)
	: first_(clone(other.first_)) /* define size here? */
{
	size_ = other.size();
	sum_ = other.sum();
}


List::~List()
{
	while (!empty())
	{
		removeFirst();
	}
	size_ = 0;
}

const List & List::operator=(const List & other)
{
	// check for list = list
	if (&other != this)
	{
		// clear the current contents of this List
		this -> ~List();
		// and get a copy of other
		first_ = clone(other.first_);
		size_ = other.size();  /* maybe set size here to something else? */
		sum_ = other.sum();
	}

	return *this;
}

/*bool List::operator==(const List &rhs) {
	/*if(size() == 0 && rhs.size() == 0){return true;}//both empty
	if(size() != rhs.size()){return false;}//sizes not the same

	Node * lptr = this->next_;
	Node * rptr = rhs->next_;
	Double lEntry = lptr->entry_;
	Double rEntry = rptr->entry_;
	while (lptr != NULL && rptr != NULL)
	{
	if(lEntry != rEntry){
	return false;
	}
	lptr = lptr->next_;
	rptr = rptr->next_;
	lEntry = lptr->entry_;
	rEntry = rptr->entry_;
	}

	return true;
}*/


bool List::empty() const
{
	return first_ == NULL;
}
int List::size() const
{
	if (!empty())
	{
		int size_ = 0;
		Node * temp = first_;
		while (temp != NULL)
		{
			temp = temp->next_;
			size_++;
		}
		return size_;
	}
	return 0;
}

double List::sum() const
{
	if (!empty())
	{

		double sum_ = 0;
		Node * temp = first_;
		while (temp != NULL)
		{
			sum_ = sum_ + temp->entry_;
			temp = temp->next_;
		}
		return sum_;
	}
	return 0;
}




void List::insertAsFirst(double x)
{
	size_ = size_ + 1; /* maybe change size here? */
	sum_ = sum_ + x;
	first_ = new Node(x, first_);
}

void List::insertAsLast(double x)
{
	if (!empty())
	{
		Node * temp = first_;
		while (temp->next_ != NULL)
		{
			temp = temp->next_;
		}
		temp->next_ = new Node(x, NULL);
	}
	else
	{
		first_ = new Node(x, NULL);
	}
}

double List::removeFirst()
{
	double item = first_->entry_;
	Node * tempPtr = first_;
	first_ = first_->next_;
	size_ = size_ - 1; /*maybe change size here? */
	sum_ = sum_ - item;
	delete tempPtr;
	return item;
}


void List::print(ostream & outfile) const
{
	outfile << "[ ";
	if (!empty())
	{
		// The first entry is printed separately because no comma
		// is needed.
		outfile << first_->entry_;
		Node * ptr = first_->next_;
		while (ptr != NULL)
		{
			outfile << ", " << ptr->entry_;
			ptr = ptr->next_;
		}
	}
	outfile << " ]";
}


// Iterative version of clone.
// This version walks down the linked structure making a
//   new Node for each double in the structure.
Node * List::clone(Node * ptr)
{
	if (ptr == NULL)
	{
		return NULL;
	}
	Node * first = new Node(ptr->entry_);
	Node * last = first;
	ptr = ptr->next_;
	while (ptr != NULL)
	{
		last->next_ = new Node(ptr->entry_);
		last = last->next_;
		ptr = ptr->next_;
	}
	return first;
}


//// Recursive version of clone.
//// This version handles two cases, a linked structure with
////   no Nodes, and a linked structure with one or more
////   Nodes.
//Node * List::clone( Node * ptr )
//{
//   if( ptr == NULL )
//   {
//      return NULL;
//   }
//   return new Node( ptr->entry_, clone( ptr->next_ ) );
//}


ostream & operator<<(ostream & outfile, const List & list)
{
	list.print(outfile);
	return outfile;
}
