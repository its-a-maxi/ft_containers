/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:51:42 by mmonroy-          #+#    #+#             */
/*   Updated: 2021/04/27 14:12:32 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <cstddef>
# include <limits>

# include "vectorUtils.hpp"

namespace ft
{
	// --- Template ---
	template <
    class T,
    class Alloc = std::allocator<T>
	>

	// --- Body ---
	class vector
	{
	// --- Member types ---
		public:

			typedef	T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef VectorIterator<value_type>					iterator;
			typedef ConstVectorIterator<value_type>				const_iterator;
			typedef RevVectorIterator<value_type>				reverse_iterator;
			typedef ConstRevVectorIterator<value_type>			const_reverse_iterator;
			typedef std::ptrdiff_t								difference_type;
			typedef std::size_t									size_type;


	// --- Internal data / Nodes ---
		private:

			pointer				_array;
			size_type			_lenght;
			size_type			_max;
			allocator_type		_myAllocator;

	// --- Member functions ---
		public:

	// > Constructors, assigment and destructor
	
		// > Constructors
			explicit vector (const allocator_type& alloc = allocator_type()) :
			_array(0), _lenght(0), _max(0), _myAllocator(alloc)
			{
				return ;
			}	// Default constructor. Constructs an empty container with the given allocator alloc.
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) :
			_lenght(n), _max(n), _myAllocator(alloc)
			{
				this->_array = new value_type[n]();
				size_type i = 0;
				while (i < n)
				{
					this->_array[i] = val;
					i++;
				}
				return ;
			}	// Constructs the container with count copies of elements with value value.
			template <class InputIterator>
  			vector
			 (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) :
			_array(0), _lenght(0), _max(0), _myAllocator(alloc)
			{
				InputIterator aux = first;
				std::ptrdiff_t dist = 0;
				while (aux != last)
				{
					aux++;
					dist++;
				}
				this->_max = dist;
				this->_lenght = this->_max;
				this->_array = new value_type[this->_max];
				this->assign(first, last);
				return ;
			}	// Constructs the container with the contents of the range [first, last).
			vector ( const vector& x ) :
			_array(0), _lenght(0), _max(0), _myAllocator(x._myAllocator)
			{
				*this = x;
				return ;
			}	// Copy constructor. Constructs the container with the copy of the contents of other.
			
		// > Destructor
			~vector()
			{
				delete[] this->_array;
				return ;
			}	// Destructs the vector. The destructors of the elements are called and the used storage is deallocated.

		// > Operator '=' overloard / Assignment 
			vector& operator=( const vector& x )
			{
				delete[] this->_array;
				this->_array = new value_type[x._max];
				this->_max = x._max;
				this->_lenght = 0;
				this->assign(x.begin(), x.end());
				return (*this);
			}	// Copy assignment operator. Replaces the contents with a copy of the contents of other.

	// > Iterators
	
		// > Begin
			iterator begin()
			{
				return (iterator(this->_array));
			}
			const_iterator begin() const
			{
				return (const_iterator(this->_array));
			}	// Returns an iterator to the first element of the vector. If the vector is empty, the returned iterator will be equal to end().

		// > End
			iterator end()
			{
				return (iterator(&this->_array[this->_lenght]));
			}
			const_iterator end() const
			{
				return (const_iterator(&this->_array[this->_lenght]));
			}	// Returns an iterator to the element following the last element of the vector. This element acts as a placeholder; attempting to access it results in undefined behavior.
		
		// > Reverse begin
			reverse_iterator rbegin()
			{
				return (reverse_iterator(&this->_array[this->_lenght - 1]));
			}
			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(&this->_array[this->_lenght - 1]));
			}	// Returns a reverse iterator to the first element of the reversed vector. It corresponds to the last element of the non-reversed vector. If the vectoris empty, the returned iterator is equal to rend().

		// > Reverse end
			reverse_iterator rend()
			{
				return (reverse_iterator(this->_array - 1));
			}
			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(this->_array - 1));
			}	// Returns a reverse iterator to the element following the last element of the reversed vector. It corresponds to the element preceding the first element of the non-reversed vector. This element acts as a placeholder, attempting to access it results in undefined behavior.

	// > Capacity

		// > Size
			size_type size() const
			{
				return (this->_lenght);
			}	// Returns the number of elements in the container.

		// > Max size
			size_type max_size() const
			{
				return (std::numeric_limits<size_type>::max() / (sizeof(value_type)));
			}	// Returns the maximum number of elements the container is able to hold due to system or library implementation limitations.

		// > Resize
			void resize (size_type n, value_type val = value_type())
			{
				while (this->_lenght > n)
					this->pop_back();
				if (this->_max < n)
					this->reserve(n);
				while (this->_lenght < n)
					this->push_back(val);
			}	// Resizes the container so that it contains n elements.

		// > Capacity
			size_type capacity() const
			{
				return (this->_max);
			}	// Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.

		// > Empty
			bool empty() const
			{
				if (!this->_lenght)
					return (true);
				else
					return (false);
			}	// Returns whether the vector is empty.

		// > Reserve
			void reserve(size_type n)
			{
				if (this->_max < n)
				{
					if ((this->_max * 2) > n)
						n = this->_max * 2;
					pointer aux = new value_type[n];
					size_type i = 0;
					while (i < this->_lenght)
					{
						aux[i] = this->_array[i];
						i++;
					}
					delete[] this->_array;
					this->_array = aux;
					this->_max = n;
				}
				return ;
			}	// Requests that the vector capacity be at least enough to contain n elements.

	// > Element access
	
		// > Operator[]
			reference operator[] (size_type n)
			{
				return (this->_array[n]);
			}
			const_reference operator[] (size_type n) const
			{
				return (this->_array[n]);
			}	// Returns a reference to the element at position n in the vector container.

		// > At
			reference at (size_type n)
			{
				if (this->_lenght <= n)
					throw std::out_of_range("out of range");
				return (this->_array[n]);
			}
			const_reference at (size_type n) const
			{
				if (this->_lenght <= n)
					throw std::out_of_range("out of range");
				return (this->_array[n]);
			}	// Returns a reference to the element at position n in the vector, if n is not in the array it trhows an exception.

		// > Front
			reference front()
			{
				return (this->_array[0]);
			}
			const_reference front() const
			{
				return (this->_array[0]);
			}	// Returns a reference to the first element in the container.
		
		// > Back
			reference back()
			{
				return (this->_array[this->_lenght - 1]);
			}
			const_reference back() const
			{
				return (this->_array[this->_lenght - 1]);
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
			}	// Assigns new contents to the vector container, replacing its current contents, and modifying its size accordingly. The new contents are elements constructed from each of the elements in the range between first and last, in the same order.
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
			iterator insert( iterator pos, const value_type& val )
			{
				iterator aux = this->begin();
				size_type dist = 0;
				while (aux + dist != pos && dist < this->_lenght)
					dist++;
				if (this->_max < this->_lenght + 1)
					this->reserve(this->_lenght + 1);
				size_type i = this->_max - 1;
				while (i > dist)
				{
					this->_array[i] = this->_array[i - 1];
					i--;
				}
				this->_array[i] = val;
				this->_lenght++;
				return (iterator(&this->_array[dist]));
			}	// Inserts value before pos.
			void insert( iterator pos, size_type count, const value_type& val )
			{
				while (count--)
					pos = insert(pos, val);
				return ;
			}	// Inserts count copies of the value before pos.
			template< class InputIt >
			void insert( iterator pos, InputIt first, InputIt last)
			{
				while (first != last)
				{
					pos = insert(pos, *first) + 1;
					first++;
				}
				return ;
			}	// Inserts elements from range [first, last) before pos.

		// > Erase
			iterator erase( iterator pos )
			{
				iterator aux(pos);
				while (aux != this->end() - 1)
				{
					*aux = *(aux + 1);
					aux++;
				}
				this->_lenght--;
				return (pos);
			}	// Removes the element at pos.
			iterator erase( iterator first, iterator last )
			{
				iterator aux(last);
				while (aux != this->end())
				{
					*first = *aux;
					aux++;
					first++;
				}
				iterator aux2 = first;
				size_type dist = 0;
				while (aux2 != aux)
				{
					aux2++;
					dist++;
				}
				this->_lenght -= dist;
				return (last);
			}	// Removes the elements in the range [first, last).

		// > Push back
			void push_back( const value_type& val )
			{
				if (this->_lenght == this->_max)
				{
					if (this->_lenght > 0)
						this->reserve(this->_max * 2);
					else
						this->reserve(1);
				}
				this->_array[this->_lenght] = val;
				this->_lenght++;
				return ;
			}	// The new element is initialized as a copy of value.

		// > Pop back
			void pop_back()
			{
				this->_lenght--;
				return ;
			}	// Removes the last element of the container.

		// > Swap
			void swap( vector& x )
			{
				vector aux(x);
				x = *this;
				*this = aux;
				return ;
			}	// Exchanges the contents of the container with those of other. Does not invoke any move, copy, or swap operations on individual elements.
	
	};

	// --- Non-member functions overload ---

	// > Relatonial operators
		// ==
	template <class T, class Alloc>
	bool operator== (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename vector<T>::const_iterator x = lhs.begin();
		typename vector<T>::const_iterator y = rhs.begin();
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
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs == rhs)
			return (false);
		return (true);
	}
		// <
	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() < rhs.size())
			return (true);
		if (lhs.size() > rhs.size())
			return (false);
		typename vector<T>::const_iterator x = lhs.begin();
		typename vector<T>::const_iterator y = rhs.begin();
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
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (rhs < lhs)
			return (true);
		return (false);
	}
		// <=
	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (rhs < lhs)
			return (false);
		return (true);
	}
		// >=
	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs < rhs)
			return (false);
		return (true);
	};

	// > Swap
	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
		return ;
	}

}

#endif /* ***************************************************** VECTOR_H */