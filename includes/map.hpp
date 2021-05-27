/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 11:03:45 by mmonroy-          #+#    #+#             */
/*   Updated: 2021/05/23 17:13:41 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <cstddef>
# include <limits>

# include "mapUtils.hpp"

namespace ft
{
	// --- Template ---
	template <
	class Key,
    class T,
	class Compare = std::less<Key>,
    class Alloc = std::allocator< std::pair<Key, T> >
	>

	// --- Body ---
	class map
	{
	// --- Member types ---
		public:
			typedef	Key												key_type;
			typedef	T												mapped_type;
			typedef	std::pair<Key, T>								value_type;
			typedef Compare											key_compare;
			typedef Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef MapIterator<key_type, mapped_type>				iterator;
			typedef ConstMapIterator<key_type, mapped_type>			const_iterator;
			typedef RevMapIterator<key_type, mapped_type>			reverse_iterator;
			typedef ConstRevMapIterator	<key_type, mapped_type>		const_reverse_iterator;
			typedef std::ptrdiff_t									difference_type;
			typedef std::size_t										size_type;
			class	value_compare // Class is copied from cpp reference page -> https://www.cplusplus.com/reference/map/map/value_comp/
			{
				friend class map;
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {};
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					};
			};


	// --- Internal data / Nodes ---
		private:

			allocator_type					_myAllocator;
			size_t							_lenght;
			MapNode<key_type, mapped_type>*	_root;
			key_compare						_comp;
		
		// > Node creation
			MapNode<key_type, mapped_type> *_newNode( key_type key, mapped_type value,
				MapNode<key_type, mapped_type> *parent, bool end = false )
			{
				MapNode<key_type, mapped_type>* rst = new MapNode<key_type, mapped_type>();
				rst->data = std::make_pair(key, value);
				rst->parent = parent;
				rst->left = 0;
				rst->right = 0;
				rst->end = end;
				return (rst);
			}

		// > Free binary tree
			void	_freeTree( MapNode<key_type, mapped_type> *node )
			{
				if (node->left)
					_freeTree(node->left);
				if (node->right)
					_freeTree(node->right);
				delete node;
			}

		// > Insert node
			MapNode<key_type, mapped_type> *_insertNode( MapNode<key_type, mapped_type> *node,
				key_type key, mapped_type value )
			{
				if (key < node->data.first || node->end)
				{
					if (!node->left)
					{
						node->left = this->_newNode(key, value, node);
						return (node->left);
					}
					else
						return (this->_insertNode(node->left, key, value));
				}
				else
				{
					if (!node->right)
					{
						node->right = this->_newNode(key, value, node);
						return (node->right);
					}
					else
						return (this->_insertNode(node->right, key, value));
				}
			}

		// > Delete node
			void	_nodeDelete( MapNode< key_type, mapped_type > *node )
			{
				MapNode< key_type, mapped_type > *parent = node->parent;
				MapNode< key_type, mapped_type > *aux;
				if (!node->left || !node->right)
				{
					if (node->right)
						aux = node->right;
					else if (node->left)
						aux = node->left;
					else
						aux = 0;
					if (parent->left == node)
						parent->left = aux;
					else
						parent->right = aux;
					if (aux)
						aux->parent = parent;
					delete node;
					return;
				}
				aux = (++iterator(node)).getPointer();
				if (!aux)
					aux = (--iterator(node)).getPointer();
				MapNode< key_type, mapped_type > * temp = aux;
				aux->data = node->data;
				node->data = temp->data;
				this->_nodeDelete(aux);
			}

		// > Search node
			MapNode<key_type, mapped_type> *_findNode(MapNode<key_type, mapped_type> *node, key_type key) const
			{
				MapNode<key_type, mapped_type> *aux;
				if (!node->end && node->data.first == key && node->parent)
					return (node);
				if (node->right)
				{
					if ((aux = _findNode(node->right, key)))
						return (aux);
				}
				if (node->left)
				{
					if ((aux = _findNode(node->left, key)))
						return (aux);
				}
				return (0);
			}

		// > Tree creation
			void	_startTree( void )
			{
				_root = _newNode(key_type(), mapped_type(), 0);
				_root->right = _newNode(key_type(), mapped_type(), _root, true);
			}

		// > Last node access
			MapNode<key_type, mapped_type> *_lastNode( void ) const
			{
				return (this->_root->right);
			}

	// --- Member functions ---
		public:

	// > Constructors, assigment and destructor
	
		// > Constructors
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
			_myAllocator(alloc), _lenght(0), _comp(comp)
			{
				this->_startTree();
				return ;
			}	// Default constructor. Constructs an empty container with the given allocator alloc.
			template <class InputIterator>
  			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
			_myAllocator(alloc), _lenght(0), _comp(comp)
			{
				this->_startTree();
				this->insert(first, last);
				return ;
			}	// Constructs the container with the contents of the range [first, last).
			map( const map& x ) :
			_myAllocator(x._myAllocator), _lenght(0), _comp(x._comp)
			{
				this->_startTree();
				*this = x;
				return ;
			}	// Copy constructor. Constructs the container with the copy of the contents of other.
			
		// > Destructor
			~map()
			{
				_freeTree(_root);
				return ;
			}	// Destructs the map. The destructors of the elements are called and the used storage is deallocated.

		// > Operator '=' overloard / Assignment 
			map& operator=( const map& x )
			{
				this->clear();
				this->_lenght = 0;
				this->insert(x.begin(), x.end());
				return (*this);
			}	// Copy assignment operator. Replaces the contents with a copy of the contents of other.

	// > Iterators
	
		// > Begin
			iterator begin()
			{
				MapNode<key_type, mapped_type> *node = this->_root;
				if (!node->left && !node->right)
					return(this->end());
				else if (!node->left && node->right)
					node = node->right;
				while (node->left)
					node = node->left;
				return (iterator(node));
			}
			const_iterator begin() const
			{
				MapNode<key_type, mapped_type> *node = this->_root;
				if (!node->left && !node->right)
					return(this->end());
				else if (!node->left && node->right)
					node = node->right;
				while (node->left)
					node = node->left;
				return (const_iterator(node));
			}	// Returns an iterator to the first element of the map. If the map is empty, the returned iterator will be equal to end().

		// > End
			iterator end()
			{
				return (iterator(this->_lastNode()));
			}
			const_iterator end() const
			{
				return (const_iterator(this->_lastNode()));
			}	// Returns an iterator to the element following the last element of the map. This element acts as a placeholder; attempting to access it results in undefined behavior.
		
		// > Reverse begin
			reverse_iterator rbegin()
			{
				iterator aux = this->end();
				aux--;
				return (reverse_iterator(aux.getPointer()));
			}
			const_reverse_iterator rbegin() const
			{
				iterator aux = this->end();
				aux--;
				return (const_reverse_iterator(aux.getPointer()));
			}	// Returns a reverse iterator to the first element of the reversed map. It corresponds to the last element of the non-reversed map. If the map is empty, the returned iterator is equal to rend().

		// > Reverse end
			reverse_iterator rend()
			{
				return (reverse_iterator(this->_root));
			}
			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(this->_root));
			}	// Returns a reverse iterator to the element following the last element of the reversed map. It corresponds to the element preceding the first element of the non-reversed map. This element acts as a placeholder, attempting to access it results in undefined behavior.

	// > Capacity

		// > Empty
			bool empty() const
			{
				return (this->_lenght == 0);
			}	// Checks if the container has no elements.
		
		// > Size
			size_type size() const
			{
				return (this->_lenght);
			}	// Returns the number of elements in the container.

		// > Max size
			size_type max_size() const
			{
				return (std::numeric_limits<size_type>::max() / (sizeof(MapNode<key_type, mapped_type>)));
			}	// Returns the maximum number of elements the container is able to hold due to system or library implementation limitations.


	// > Element access
	
		// > Operator []
			mapped_type& operator[] (const key_type& k)
			{
				return ((*((this->insert(std::make_pair(k,mapped_type()))).first)).second); // Code from cpp-reference
			}	// If k matches the key of an element in the container, the function returns a reference to its mapped value.

	// > Modifiers

		// > Insert
			std::pair<iterator,bool> insert (const value_type& val)
			{
				iterator aux = this->find(val.first);
				if (aux != this->end())
					return (std::make_pair(aux, false));
				this->_lenght++;
				aux = this->_insertNode(this->_root, val.first, val.second);
				return (std::make_pair(aux, true));
				
			}	// Extends the container by inserting new elements. If dup, return original. Returns pair of iterator + bool (false for dup, true for non-dup).
			iterator insert (iterator position, const value_type& val)
			{
				iterator aux = this->find(val.first);
				if (aux != this->end())
					return (aux);
				this->_lenght++;
				aux = this->_insertNode(position.getPointer(), val.first, val.second);
				return (aux);
			}	// Same as above, using a position for insert and without pair.
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					this->insert(*first);
					first++;
				}
			}	// Inserts range of elements.
		
		// > Erase
			void erase (iterator position)
			{
				this->_nodeDelete(position.getPointer());
				this->_lenght--;
				return ;
			}	// Removes the element at pos.
			size_type erase (const key_type& k)
			{
				int i = 0;
				iterator element;
				while (element != end())
				{
					element = find(k);
					if (element != end())
					{
						erase(element);
						i++;
					}
				}
				return (i);
			}	// Removes all the elements with key 'k'.
			void erase (iterator first, iterator last)
			{
				while (first != last)
					erase(first++);
				return ;
			}	// Removes the elements in the range [first, last).
			
		// > Swap
			void swap( map& x )
			{
				MapNode<key_type, mapped_type>*	auxRoot		= x._root;
				key_compare			auxComp					= x._comp;
				size_type			auxLenght				= x._lenght;
				Alloc				auxMyAllocator			= x._myAllocator;
				x._root				= this->_root;
				x._comp				= this->_comp;
				x._lenght			= this->_lenght;
				x._myAllocator		= this->_myAllocator;
				this->_root			= auxRoot;
				this->_comp			= auxComp;
				this->_lenght		= auxLenght;
				this->_myAllocator	= auxMyAllocator;
			}	// Exchanges the contents of the container with those of other. Does not invoke any move, copy, or swap operations on individual elements.
		
		// > Clear
			void clear()
			{
				erase(begin(), end());
				return ;
			}	// Erases all elements from the container. After this call, size() returns zero.

	// > Observers

		// > Key compare
			key_compare key_comp() const
			{
				return (this->_comp);
			}	// Return key comparison object.

		// > Value compare
			value_compare value_comp() const
			{
				return (this->value_compare);
			}	// Return Value comparison object.

	// > Operations

		// > Find
			iterator find (const key_type& k)
			{
				if (!this->empty())
				{
					MapNode<key_type, mapped_type> *aux = this->_findNode(_root, k);
					if (aux)
						return (iterator(aux));
				}
				return (this->end());
			}
			const_iterator find (const key_type& k) const
			{
				if (!this->empty())
				{
					MapNode<key_type, mapped_type> *aux = this->_findNode(_root, k);
					if (aux)
						return (const_iterator(aux));
				}
				return (this->end());
			}	// Searches the container for an element with a key equivalent to k and returns an iterator to it if found, otherwise it returns an iterator to map::end.

		// > Count
			size_type count (const key_type& k) const
			{
				int i = 0;
				const_iterator aux = this->begin();
				while (aux != this->end())
				{
					if (aux->first == k)
						i++;
					aux++;
				}
				return (i);
			}	// Return number of elements with 'k' key in the container

		// > Lower bound
			iterator lower_bound(const key_type &k)
			{
				iterator aux = this->begin();
				while (aux != this->end())
				{
					if (this->_comp(aux->first, k) == false)
						return (aux);
					aux++;
				}
				return (this->end());
			}
			const_iterator lower_bound(const key_type &k) const
			{
				const_iterator aux = this->begin();
				while (aux != this->end())
				{
					if (this->_comp(aux->first, k) == false)
						return (aux);
					aux++;
				}
				return (this->end());
			}	// Returns an iterator pointing to the first element in the container whose key is not considered to go before k.

		// > Upper bound
			iterator upper_bound (const key_type& k)
			{
				iterator aux = this->begin();
				while (aux != this->end())
				{
					if (this->_comp(aux->first, k) == false && aux->first != k)
						return (aux);
					aux++;
				}
				return (this->end());
			}
			const_iterator upper_bound (const key_type& k) const
			{
				const_iterator aux = this->begin();
				while (aux != this->end())
				{
					if (this->_comp(aux->first, k) == false && aux->first != k)
						return (aux);
					aux++;
				}
				return (this->end());
			}	// Returns an iterator pointing to the first element in the container whose key is considered to go after k.

		// > Equal range
			std::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{
				return (std::pair<const_iterator, const_iterator>(this->lower_bound(k), this->upper_bound(k)));
			}
			std::pair<iterator,iterator>             equal_range (const key_type& k)
			{
				return (std::pair<iterator, iterator>(this->lower_bound(k), this->upper_bound(k)));
			}	// Returns the bounds of a range that includes all the elements in the container which have a key equivalent to k.
	
	};

	// --- Non-member functions overload ---

	// > Relatonial operators
		// ==
	template <class Key, class T, class Compare, class Alloc>
	bool operator== (const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename map<Key, T, Compare, Alloc>::const_iterator x = lhs.begin();
		typename map<Key, T, Compare, Alloc>::const_iterator y = rhs.begin();
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
	template <class Key, class T, class Compare, class Alloc>
	bool operator!= ( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs == rhs)
			return (false);
		return (true);
	}
		// <
	template <class Key, class T, class Compare, class Alloc>
	bool operator<  ( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs.size() < rhs.size())
			return (true);
		if (lhs.size() > rhs.size())
			return (false);
		typename map<Key, T, Compare, Alloc>::const_iterator x = lhs.begin();
		typename map<Key, T, Compare, Alloc>::const_iterator y = rhs.begin();
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
	template <class Key, class T, class Compare, class Alloc>
	bool operator>  ( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
	{
		if (rhs < lhs)
			return (true);
		return (false);
	}
		// <=
	template <class Key, class T, class Compare, class Alloc>
	bool operator<= ( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs > rhs)
			return (false);
		return (true);
	}
		// >=
	template <class Key, class T, class Compare, class Alloc>
	bool operator>= ( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs < rhs)
			return (false);
		return (true);
	};


	// > Swap
	template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
	{
		x.swap(y);
		return ;
	}


}

#endif /* ***************************************************** MAP_H */