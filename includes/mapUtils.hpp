/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapUtils.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 11:25:44 by mmonroy-          #+#    #+#             */
/*   Updated: 2021/05/17 12:37:53 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPUTILS_HPP
# define MAPUTILS_HPP

# include <iterator>

# include "map.hpp"

namespace ft
{

// --- MapNode declaration for each element of the map ---
	template <class Key, class T>
	struct MapNode
	{
		std::pair<Key, T>	data;
		MapNode				*parent;
		MapNode				*left;
		MapNode				*right;
		bool				end;
	};

// --- Bidirectonial Map iterator ---
	template <class Key, class T>
    class MapIterator 
	{
		public:
			typedef std::bidirectional_iterator_tag		iterator_category;
			typedef std::ptrdiff_t						difference_type;
			typedef std::pair<Key, T>					value_type;
			typedef MapNode<Key, T>*					pointer;
			typedef std::pair<Key, T>&					reference;

			MapIterator() {}
			MapIterator(pointer ptr) : _ptr(ptr) {}

			pointer	getPointer() const
			{
				return (_ptr);
			}
			MapIterator &operator=(const MapIterator &other)
			{
				_ptr = other._ptr;
				return (*this);
			};
			value_type &operator*() const
			{
				return (_ptr->data);
			}
			value_type *operator->() const
			{
				return (&_ptr->data);
			}
			MapIterator &operator++()
			{
				MapNode<Key, T> *aux;
				if (_ptr->right)
				{
					_ptr = _ptr->right;
					while (_ptr->left)
						_ptr = _ptr->left;
				}
				else
				{
					aux = _ptr->parent;
					while (aux && _ptr == aux->right)
					{
						_ptr = aux;
						aux = _ptr->parent;
					}
					_ptr = aux;
				}
				return (*this);
			}
			MapIterator operator++(int)
			{
				MapIterator tmp = *this;
				operator++();
				return (tmp);
			}
			MapIterator &operator--()
			{
				MapNode<Key, T> *aux;
				if (_ptr->left)
				{
					_ptr = _ptr->left;
					while (_ptr->right)
						_ptr = _ptr->right;
				}
				else
				{
					aux = _ptr->parent;
					while (aux && _ptr == aux->left)
					{
						_ptr = aux;
						aux = _ptr->parent;
					}
					_ptr = aux;
				}
				return (*this);
			}
			MapIterator operator--(int)
			{
				MapIterator tmp = *this;
				operator--();
				return (tmp);
			}
			bool operator== (const MapIterator &x) 
			{
				return (_ptr == x._ptr);
			}
			bool operator!= (const MapIterator &x)
			{
				return (_ptr != x._ptr);
			}

		private:
			pointer _ptr;
	};

	// --- Const bidirectonial Map iterator ---
	template <class Key, class T>
	class ConstMapIterator 
	{
		public:
			typedef std::bidirectional_iterator_tag		iterator_category;
			typedef std::ptrdiff_t						difference_type;
			typedef std::pair<Key, T>					value_type;
			typedef MapNode<Key, T>*					pointer;
			typedef std::pair<Key, T>&					reference;

			ConstMapIterator() {}
			ConstMapIterator(pointer ptr) : _ptr(ptr) {}

			pointer	getPointer() const
			{
				return (_ptr);
			}
			ConstMapIterator &operator=(const ConstMapIterator &other)
			{
				_ptr = other._ptr;
				return (*this);
			};
			const value_type &operator*() const
			{
				return (_ptr->data);
			}
			const value_type *operator->() const
			{
				return (&_ptr->data);
			}
			ConstMapIterator &operator++()
			{
				MapNode<Key, T> *aux;
				if (_ptr->right)
				{
					_ptr = _ptr->right;
					while (_ptr->left)
						_ptr = _ptr->left;
				}
				else
				{
					aux = _ptr->parent;
					while (aux && _ptr == aux->right)
					{
						_ptr = aux;
						aux = _ptr->parent;
					}
					_ptr = aux;
				}
				return (*this);
			}
			ConstMapIterator operator++(int)
			{
				ConstMapIterator tmp = *this;
				operator++();
				return (tmp);
			}
			ConstMapIterator &operator--()
			{
				MapNode<Key, T> *aux;
				if (_ptr->left)
				{
					_ptr = _ptr->left;
					while (_ptr->right)
						_ptr = _ptr->right;
				}
				else
				{
					aux = _ptr->parent;
					while (aux && _ptr == aux->left)
					{
						_ptr = aux;
						aux = _ptr->parent;
					}
					_ptr = aux;
				}
				return (*this);
			}
			ConstMapIterator operator--(int)
			{
				ConstMapIterator tmp = *this;
				operator--();
				return (tmp);
			}
			bool operator== (const ConstMapIterator &x) 
			{
				if (_ptr == x._ptr)
					return (true);
				return (false);
			}
			bool operator!= (const ConstMapIterator &x)
			{
				if (_ptr != x._ptr)
					return (true);
				return (false);
			}
	
		private:
			pointer _ptr;
	};

// --- Reverse bidirectonial Map iterator ---
	template <class Key, class T>
    class RevMapIterator 
	{
		public:
			typedef std::bidirectional_iterator_tag		iterator_category;
			typedef std::ptrdiff_t						difference_type;
			typedef std::pair<Key, T>					value_type;
			typedef MapNode<Key, T>*					pointer;
			typedef std::pair<Key, T>&					reference;

			RevMapIterator() {}
			RevMapIterator(pointer ptr) : _ptr(ptr) {}

			pointer	getPointer() const
			{
				return (_ptr);
			}
			RevMapIterator &operator=(const RevMapIterator &other)
			{
				_ptr = other._ptr;
				return (*this);
			};
			value_type &operator*() const
			{
				return (_ptr->data);
			}
			value_type *operator->() const
			{
				return (&_ptr->data);
			}
			RevMapIterator &operator++()
			{
				MapNode<Key, T> *aux;
				if (_ptr->left)
				{
					_ptr = _ptr->left;
					while (_ptr->right)
						_ptr = _ptr->right;
				}
				else
				{
					aux = _ptr->parent;
					while (aux && _ptr == aux->left)
					{
						_ptr = aux;
						aux = _ptr->parent;
					}
					_ptr = aux;
				}
				return (*this);
			}
			RevMapIterator operator++(int)
			{
				RevMapIterator tmp = *this;
				operator++();
				return (tmp);
			}
			RevMapIterator &operator--()
			{
				MapNode<Key, T> *aux;
				if (_ptr->right)
				{
					_ptr = _ptr->right;
					while (_ptr->left)
						_ptr = _ptr->left;
				}
				else
				{
					aux = _ptr->parent;
					while (aux && _ptr == aux->right)
					{
						_ptr = aux;
						aux = _ptr->parent;
					}
					_ptr = aux;
				}
				return (*this);
			}
			RevMapIterator operator--(int)
			{
				RevMapIterator tmp = *this;
				operator--();
				return (tmp);
			}
			bool operator== (const RevMapIterator &x) 
			{
				if (_ptr == x._ptr)
					return (true);
				return (false);
			}
			bool operator!= (const RevMapIterator &x)
			{
				if (_ptr != x._ptr)
					return (true);
				return (false);
			}

		private:
			pointer _ptr;
	};

	// --- Const reverse bidirectonial Map iterator ---
	template <class Key, class T>
	class ConstRevMapIterator 
	{
		public:
			typedef std::bidirectional_iterator_tag		iterator_category;
			typedef std::ptrdiff_t						difference_type;
			typedef std::pair<Key, T>					value_type;
			typedef MapNode<Key, T>*					pointer;
			typedef std::pair<Key, T>&					reference;

			ConstRevMapIterator() {}
			ConstRevMapIterator(pointer ptr) : _ptr(ptr) {}

			pointer	getPointer() const
			{
				return (_ptr);
			}
			ConstRevMapIterator &operator=(const ConstRevMapIterator &other)
			{
				_ptr = other._ptr;
				return (*this);
			};
			const value_type &operator*() const
			{
				return (_ptr->data);
			}
			const value_type *operator->() const
			{
				return (&_ptr->data);
			}
			ConstRevMapIterator &operator++()
			{
				MapNode<Key, T> *aux;
				if (_ptr->left)
				{
					_ptr = _ptr->left;
					while (_ptr->right)
						_ptr = _ptr->right;
				}
				else
				{
					aux = _ptr->parent;
					while (aux && _ptr == aux->left)
					{
						_ptr = aux;
						aux = _ptr->parent;
					}
					_ptr = aux;
				}
				return (*this);
			}
			ConstRevMapIterator operator++(int)
			{
				ConstRevMapIterator tmp = *this;
				operator++();
				return (tmp);
			}
			ConstRevMapIterator &operator--()
			{
				MapNode<Key, T> *aux;
				if (_ptr->right)
				{
					_ptr = _ptr->right;
					while (_ptr->left)
						_ptr = _ptr->left;
				}
				else
				{
					aux = _ptr->parent;
					while (aux && _ptr == aux->right)
					{
						_ptr = aux;
						aux = _ptr->parent;
					}
					_ptr = aux;
				}
				return (*this);
			}
			ConstRevMapIterator operator--(int)
			{
				ConstRevMapIterator tmp = *this;
				operator--();
				return (tmp);
			}
			bool operator== (const ConstRevMapIterator &x) 
			{
				if (_ptr == x._ptr)
					return (true);
				return (false);
			}
			bool operator!= (const ConstRevMapIterator &x)
			{
				if (_ptr != x._ptr)
					return (true);
				return (false);
			}
		
		private:
			pointer _ptr;
	};
};

#endif