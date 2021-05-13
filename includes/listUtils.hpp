/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listUtils.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 11:19:13 by mmonroy-          #+#    #+#             */
/*   Updated: 2021/05/13 12:27:44 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTUTILS_HPP
# define LISTUTILS_HPP

# include <iterator>

# include "list.hpp"

namespace ft
{

// --- Node declaration for each element of 
	template <class T>
	struct Node
	{
		T data;
		Node *prev;
		Node *next;
	};


// --- Bidirectonial list iterator ---
	template <class T>
    class ListIterator 
	{
		public:
			typedef std::bidirectional_iterator_tag		iterator_category;
			typedef std::ptrdiff_t						difference_type;
			typedef T									value_type;
			typedef Node<T>*							pointer;
			typedef T&									reference;

			ListIterator() {}
			ListIterator(pointer ptr) : _ptr(ptr) {}

			pointer	getPointer() const
			{
				return (_ptr);
			}
			ListIterator &operator=(const ListIterator &other)
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
				return (_ptr->data);
			}
			ListIterator &operator++()
			{
				_ptr = _ptr->next;
				return (*this);
			}
			ListIterator operator++(int)
			{
				ListIterator tmp = *this;
				operator++();
				return (tmp);
			}
			ListIterator &operator--()
			{
				_ptr = _ptr->prev;
				return (*this);
			}
			ListIterator operator--(int)
			{
				ListIterator tmp = *this;
				operator--();
				return (tmp);
			}
			bool operator== (const ListIterator &x) 
			{
				if (_ptr == x._ptr)
					return (true);
				return (false);
			}
			bool operator!= (const ListIterator &x)
			{
				if (_ptr != x._ptr)
					return (true);
				return (false);
			}

		private:
			pointer _ptr;
	};

	// --- Const bidirectonial list iterator ---
	template <class T>
	class ConstListIterator 
	{
		public:
			typedef std::bidirectional_iterator_tag		iterator_category;
			typedef std::ptrdiff_t						difference_type;
			typedef T									value_type;
			typedef Node<T>*							pointer;
			typedef T&									reference;

			ConstListIterator() {}
			ConstListIterator(pointer ptr) : _ptr(ptr) {}

			pointer	getPointer() const
			{
				return (_ptr);
			}
			ConstListIterator &operator=(const ConstListIterator &other)
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
				return (_ptr->data);
			}
			ConstListIterator &operator++()
			{
				_ptr = _ptr->next;
				return (*this);
			}
			ConstListIterator operator++(int)
			{
				ConstListIterator tmp = *this;
				operator++();
				return (tmp);
			}
			ConstListIterator &operator--()
			{
				_ptr == _ptr->prev;
				return (*this);
			}
			ConstListIterator operator--(int)
			{
				ConstListIterator tmp = *this;
				operator--();
				return (tmp);
			}
			bool operator== (const ConstListIterator &x) 
			{
				if (_ptr == x._ptr)
					return (true);
				return (false);
			}
			bool operator!= (const ConstListIterator &x)
			{
				if (_ptr != x._ptr)
					return (true);
				return (false);
			}
	
		private:
			pointer _ptr;
	};

// --- Reverse bidirectonial list iterator ---
	template <class T>
    class RevListIterator 
	{
		public:
			typedef std::bidirectional_iterator_tag		iterator_category;
			typedef std::ptrdiff_t						difference_type;
			typedef T									value_type;
			typedef Node<T>*							pointer;
			typedef T&									reference;

			RevListIterator() {}
			RevListIterator(pointer ptr) : _ptr(ptr) {}

			pointer	getPointer() const
			{
				return (_ptr);
			}
			RevListIterator &operator=(const RevListIterator &other)
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
				return (_ptr->data);
			}
			RevListIterator &operator++()
			{
				_ptr = _ptr->prev;
				return (*this);
			}
			RevListIterator operator++(int)
			{
				RevListIterator tmp = *this;
				operator++();
				return (tmp);
			}
			RevListIterator &operator--()
			{
				_ptr = _ptr->next;
				return (*this);
			}
			RevListIterator operator--(int)
			{
				RevListIterator tmp = *this;
				operator--();
				return (tmp);
			}
			bool operator== (const RevListIterator &x) 
			{
				if (_ptr == x._ptr)
					return (true);
				return (false);
			}
			bool operator!= (const RevListIterator &x)
			{
				if (_ptr != x._ptr)
					return (true);
				return (false);
			}

		private:
			pointer _ptr;
	};

	// --- Const reverse bidirectonial list iterator ---
	template <class T>
	class ConstRevListIterator 
	{
		public:
			typedef std::bidirectional_iterator_tag		iterator_category;
			typedef std::ptrdiff_t						difference_type;
			typedef T									value_type;
			typedef Node<T>*							pointer;
			typedef T&									reference;

			ConstRevListIterator() {}
			ConstRevListIterator(pointer ptr) : _ptr(ptr) {}

			pointer	getPointer() const
			{
				return (_ptr);
			}
			ConstRevListIterator &operator=(const ConstRevListIterator &other)
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
				return (_ptr->data);
			}
			ConstRevListIterator &operator++()
			{
				_ptr = _ptr->prev;
				return (*this);
			}
			ConstRevListIterator operator++(int)
			{
				ConstRevListIterator tmp = *this;
				operator++();
				return (tmp);
			}
			ConstRevListIterator &operator--()
			{
				_ptr == _ptr->next;
				return (*this);
			}
			ConstRevListIterator operator--(int)
			{
				ConstRevListIterator tmp = *this;
				operator--();
				return (tmp);
			}
			bool operator== (const ConstRevListIterator &x) 
			{
				if (_ptr == x._ptr)
					return (true);
				return (false);
			}
			bool operator!= (const ConstRevListIterator &x)
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