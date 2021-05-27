/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:51:42 by mmonroy-          #+#    #+#             */
/*   Updated: 2021/05/13 13:14:11 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

# include <memory>
# include <cstddef>
# include <limits>

# include "listUtils.hpp"

namespace ft
{

	// --- Template ---
	template <
    class T,
    class Alloc = std::allocator<T>
	>

	// --- Body ---
	class list
	{
	// --- Member types ---
		public:

			typedef	T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ListIterator<value_type>					iterator;
			typedef ConstListIterator<value_type>				const_iterator;
			typedef RevListIterator<value_type>					reverse_iterator;
			typedef ConstRevListIterator<value_type>			const_reverse_iterator;
			typedef std::ptrdiff_t								difference_type;
			typedef std::size_t									size_type;


	// --- Internal data / Nodes ---
		private:

		// > My allocator
			allocator_type	_myAllocator;

		// > Lenght of my list
			size_t			_lenght;

		// > Node creation
			Node<value_type> *_newNode(value_type value, Node<value_type> *prev, Node<value_type> *next)
			{
				Node<value_type>* rst = new Node<value_type>();
				rst->data = value;
				rst->prev = prev;
				rst->next = next;
				return (rst);
			};

		// > First and last nodes
			Node<value_type>*	_firstNode;
			Node<value_type>*	_lastNode;

		// > list creation
			void		_startlist()
			{
				_firstNode = _newNode(value_type(), 0, 0);
				_lastNode = _newNode(value_type(), _firstNode, 0);
				_firstNode->next = _lastNode;
			}

		// > Boolean operators
			struct _isSmaller {
				bool operator()(const value_type &a, const value_type &b)
				{
					return a > b;
				};
			};
			struct _isEqual {
				bool operator()(const value_type &a, const value_type &b)
				{
					return a == b;
				};
			};

	// --- Member functions ---
		public:

	// > Constructors, assigment and destructor
	
		// > Constructors
			explicit list (const allocator_type& alloc = allocator_type()) :
			_myAllocator(alloc), _lenght(0)
			{
				this->_startlist();
				return ;
			}	// Default constructor. Constructs an empty container with the given allocator alloc.
			explicit list (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) :
			_myAllocator(alloc), _lenght(0)
			{
				this->_startlist();
				this->assign(n, val);
				return ;
			}	// Constructs the container with count copies of elements with value value.
			template <class InputIterator>
  			list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) :
			_myAllocator(alloc), _lenght(0)
			{
				this->_startlist();
				this->assign(first, last);
				return ;
			}	// Constructs the container with the contents of the range [first, last).
			list( const list& x ) :
			_myAllocator(x._myAllocator), _lenght(0)
			{
				this->_startlist();
				*this = x;
				return ;
			}	// Copy constructor. Constructs the container with the copy of the contents of other.
			
		// > Destructor
			~list()
			{
				this->clear();
				delete this->_lastNode;
				delete this->_firstNode;
				return ;
			}	// Destructs the list. The destructors of the elements are called and the used storage is deallocated.

		// > Operator '=' overloard / Assignment 
			list& operator=( const list& x )
			{
				this->clear();
				this->_firstNode->next = this->_lastNode;
				this->_lastNode->prev = this->_firstNode;
				this->_lenght = 0;
				this->assign(x.begin(), x.end());
				return (*this);
			}	// Copy assignment operator. Replaces the contents with a copy of the contents of other.

	// > Iterators
	
		// > Begin
			iterator begin()
			{
				return (iterator(this->_firstNode->next));
			}
			const_iterator begin() const
			{
				return (const_iterator(this->_firstNode->next));
			}	// Returns an iterator to the first element of the list. If the list is empty, the returned iterator will be equal to end().

		// > End
			iterator end()
			{
				return (iterator(this->_lastNode));
			}
			const_iterator end() const
			{
				return (const_iterator(this->_lastNode));
			}	// Returns an iterator to the element following the last element of the list. This element acts as a placeholder; attempting to access it results in undefined behavior.
		
		// > Reverse begin
			reverse_iterator rbegin()
			{
				return (reverse_iterator(this->_lastNode->prev));
			}
			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(this->_lastNode->prev));
			}	// Returns a reverse iterator to the first element of the reversed list. It corresponds to the last element of the non-reversed list. If the list is empty, the returned iterator is equal to rend().

		// > Reverse end
			reverse_iterator rend()
			{
				return (reverse_iterator(this->_firstNode));
			}
			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(this->_firstNode));
			}	// Returns a reverse iterator to the element following the last element of the reversed list. It corresponds to the element preceding the first element of the non-reversed list. This element acts as a placeholder, attempting to access it results in undefined behavior.

	// > Capacity

		// > Empty
			bool empty() const
			{
				if (this->_lenght == 0)
					return (true);
				else
					return (false);
			}	// Checks if the container has no elements.
		
		// > Size
			size_type size() const
			{
				return (this->_lenght);
			}	// Returns the number of elements in the container.

		// > Max size
			size_type max_size() const
			{
				return (std::numeric_limits<size_type>::max() / (sizeof(Node<value_type>)));
			}	// Returns the maximum number of elements the container is able to hold due to system or library implementation limitations.

	// > Element access
	
		// > Front
			reference front()
			{
				return (this->_firstNode->next->data);
			}
			const_reference front() const
			{
				return (this->_firstNode->next->data);
			}	// Returns a reference to the first element in the container.
		
		// > Back
			reference back()
			{
				return (this->_lastNode->prev->data);
			}
			const_reference back() const
			{
				return (this->_lastNode->prev->data);
			}	// Returns a reference to the last element in the container.

	// > Modifiers

		// > Assign
			template <class InputIterator>
  			void assign (InputIterator first, InputIterator last)
			{
				this->clear();
				while (first != last)
				{
					this->push_back(*first);
					first++;
				}
				return ;
			}	// Assigns new contents to the list container, replacing its current contents, and modifying its size accordingly. The new contents are elements constructed from each of the elements in the range between first and last, in the same order.
			void assign (size_type n, const value_type& val)
			{
				size_type i = 0;
				this->clear();
				while (i < n)
				{
					this->push_back(val);
					i++;
				}
				return ;
			}	// The new contents are n elements, each initialized to a copy of val.

		// > Clear
			void clear()
			{
				while (this->_lenght)
					this->pop_back();
				return ;
			}	// Erases all elements from the container. After this call, size() returns zero.
		
		// > Insert
			iterator insert( iterator pos, const T& val )
			{
				Node<value_type> *aux = this->_newNode(val, pos.getPointer()->prev, pos.getPointer());
				aux->prev->next = aux;
				aux->next->prev = aux;
				this->_lenght++;
				return (iterator(aux));
			}	// Inserts value before pos.
			void insert( iterator pos, size_type count, const T& val )
			{
				size_type i = 0;
				while (i < count)
				{
					this->insert(pos, val);
					i++;
				}
				return ;
			}	// Inserts count copies of the value before pos.
			template< class InputIt >
			void insert( iterator pos, InputIt first, InputIt last)
			{
				while (first != last)
				{
					this->insert(pos, *first);
					first++;
				}
				return ;
			}	// Inserts elements from range [first, last) before pos.

		// > Erase
			iterator erase( iterator position )
			{
				Node<value_type> *del = position.getPointer();
				del->prev->next = del->next;
				del->next->prev = del->prev;
				position++;
				delete del;
				this->_lenght--;
				return (position);
			}	// Removes the element at pos.
			iterator erase( iterator first, iterator last )
			{
				while (first != last)
				{
					this->erase(first++);
				}
				return (first);
			}	// Removes the elements in the range [first, last).

		// > Push back
			void push_back( const value_type& val )
			{
				Node<value_type> *aux = this->_newNode(val, this->_lastNode->prev, this->_lastNode);
				aux->prev->next = aux;
				aux->next->prev = aux;
				this->_lenght++;
				return ;
			}	// The new element is initialized as a copy of value.

		// > Pop back
			void pop_back()
			{
				Node<value_type> *del = this->_lastNode->prev;
				del->prev->next = del->next;
				del->next->prev = del->prev;
				delete del;
				this->_lenght--;
				return ;
			}	// Removes the last element of the container.

		// > Push front
			void push_front( const value_type& val )
			{
				Node<value_type> *aux = this->_newNode(val, this->_firstNode, this->_firstNode->next);
				aux->prev->next = aux;
				aux->next->prev = aux;
				this->_lenght++;
				return ;
			}	// Prepends the given element value to the beginning of the container.

		// > Pop front
			void pop_front()
			{
				Node<value_type> *del = this->_firstNode->next;
				del->prev->next = del->next;
				del->next->prev = del->prev;
				delete del;
				this->_lenght--;
				return ;
			}	// Removes the first element of the container. If there are no elements in the container, the behavior is undefined.
		
		// > Resize
			void resize( size_type n, value_type val = value_type() )
			{
				while (this->_lenght < n)
					this->push_back(val);
				while (this->_lenght > n)
					this->pop_back();
				return ;
			}	// Additional copies of value are appended.

		// > Swap
			void swap( list& x )
			{
				Node<value_type>*	auxFirstNode	= x._firstNode;
				Node<value_type>*	auxLastNode		= x._lastNode;
				size_type			auxLenght		= x._lenght;
				allocator_type		auxMyAllocator	= x._myAllocator;
				x._firstNode		= this->_firstNode;
				x._lastNode			= this->_lastNode;
				x._lenght			= this->_lenght;
				x._myAllocator		= this->_myAllocator;
				this->_firstNode	= auxFirstNode;
				this->_lastNode		= auxLastNode;
				this->_lenght		= auxLenght;
				this->_myAllocator	= auxMyAllocator;
			}	// Exchanges the contents of the container with those of other. Does not invoke any move, copy, or swap operations on individual elements.
		
	// > Operations

		// > Splice
			void splice( iterator position, list& x )
			{
				this->splice(position, x, x.begin(), x.end());
				return ;
			}	// Transfers all elements from other into *this. The elements are inserted before the element pointed to by pos. The container other becomes empty after the operation. The behavior is undefined if other refers to the same object as *this.
			void splice( iterator position, list& x, iterator i )
			{
				this->insert(position, *i);
				x.erase(i);
				return ;
			}	// Transfers the element pointed to by it from other into *this. The element is inserted before the element pointed to by pos.
			void splice( iterator position, list& x, iterator first, iterator last )
			{
				this->insert(position, first, last);
				x.erase(first, last);
				return ;
			}	// Transfers the elements in the range [first, last) from other into *this. The elements are inserted before the element pointed to by pos. The behavior is undefined if pos is an iterator in the range [first,last).

		// > Remove
			void remove( const T& val )
			{
				iterator aux = this->begin();
				while (aux != this->end())
				{
					if (*aux != val)
						aux++;
					else if (*aux == val)
						aux = erase(aux);
				}
				return ;
			}
			template< class UnaryPredicate >
			void remove_if( UnaryPredicate pred )
			{
				iterator aux = this->begin();
				while (aux != this->end())
				{
					if (pred(*aux) == false)
						aux++;
					else if (pred(*aux) == true)
						aux = erase(aux);
				}
				return ;
			}	// Removes all elements satisfying specific criteria. The first version removes all elements that are equal to value, the second version removes all elements for which predicate p returns true.
		
		// > Unique
			void unique()
			{
				this->unique(_isEqual());
				return ;
			}
			template< class BinaryPredicate >
			void unique( BinaryPredicate binary_pred )
			{
				iterator x = this->begin();
				iterator y = x;
				while (++y != this->end())
				{
					if (binary_pred(*x, *y))
					{
						erase(y);
						y = x;
					}
					else
						x = y;
				}
				return ;
			}	// Removes all consecutive duplicate elements from the container. Only the first element in each group of equal elements is left. The first version uses operator== to compare the elements, the second version uses the given binary predicate p.
		
		// > Merge
			void merge( list& x )
			{
				this->merge(x, _isSmaller());
				return ;
			}
			template <class Compare>
			void merge( list& x, Compare comp )
			{
				if (x != *this)
				{
					this->insert(this->end(), x.begin(), x.end());
					x.clear();
					this->sort(comp);
				}
				return ;
			}	// Merges two sorted lists into one. The lists should be sorted into ascending order.

		// > Sort
			void sort()
			{
				sort(_isSmaller());
				return ;
			}
			template< class Compare >
			void sort( Compare comp )
			{
				iterator x = this->begin();
				iterator y;
				while (++x != this->end())
				{
					y = x;
					x--;
					while (y != this->end())
					{
						if (comp(*x, *y))
						{
							int aux = *x;
							*x = *y;
							*y = aux;
						}
						y++;
					}
					x++;
				}
				return ;
			}	// Sorts the elements in ascending order. The order of equal elements is preserved. The first version uses operator< to compare the elements, the second version uses the given comparison function comp.

		// > Reverse
			void reverse()
			{
				iterator aux = this->begin();
				Node<value_type> *temp;
				while (aux != this->end())
				{
					temp = aux.getPointer()->prev;
					aux.getPointer()->prev = aux.getPointer()->next;
					aux.getPointer()->next = temp;
					aux--;
				}
				temp = this->_firstNode->prev;
				this->_firstNode->prev = this->_firstNode->next;
				this->_firstNode->next = temp;
				temp = this->_lastNode->prev;
				this->_lastNode->prev = this->_lastNode->next;
				this->_lastNode->next = temp;
				temp = this->_firstNode;
				this->_firstNode = this->_lastNode;
				this->_lastNode = temp;
				return ;
			}	// Reverses the order of the elements in the container. No references or iterators become invalidated.

	};

	// --- Non-member functions overload ---

	// > Relatonial operators
		// ==
	template <class T, class Alloc>
	bool operator== (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename list<T>::const_iterator x = lhs.begin();
		typename list<T>::const_iterator y = rhs.begin();
		while (x != lhs.end())
		{
			if (*x != *y)
				return (false);
			x++;
			y++;
		}
		return (true);
	}
		// !=
	template <class T, class Alloc>
	bool operator!= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		if (lhs == rhs)
			return (false);
		return (true);
	}
		// <
	template <class T, class Alloc>
	bool operator<  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		if (lhs.size() < rhs.size())
			return (true);
		if (lhs.size() > rhs.size())
			return (false);
		typename list<T>::const_iterator x = lhs.begin();
		typename list<T>::const_iterator y = rhs.begin();
		while (x != lhs.end())
		{
			if (*x != *y)
			{
				if (*x < *y)
					return (true);
				else
					return (false);
			}
			x++;
			y++;
		}
		return (false);
	}
		// >
	template <class T, class Alloc>
	bool operator>  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		if (rhs < lhs)
			return (true);
		return (false);
	}
		// <=
	template <class T, class Alloc>
	bool operator<= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		if (rhs < lhs)
			return (false);
		return (true);
	}
		// >=
	template <class T, class Alloc>
	bool operator>= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		if (lhs < rhs)
			return (false);
		return (true);
	};

	// > Swap
	template <class T, class Alloc>
	void swap (list<T,Alloc>& x, list<T,Alloc>& y)
	{
		x.swap(y);
		return ;
	}

}

#endif /* ***************************************************** LIST_H */