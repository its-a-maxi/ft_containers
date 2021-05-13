/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorUtils.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 12:49:05 by mmonroy-          #+#    #+#             */
/*   Updated: 2021/05/13 12:29:26 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORUTILS_HPP
# define VECTORUTILS_HPP

# include <iterator>

# include "vector.hpp"


namespace ft
{

// --- Bidirectonial vector iterator ---
	template< class T >
    class VectorIterator 
	{
		public:
			typedef std::random_access_iterator_tag		iterator_category;
			typedef std::ptrdiff_t						difference_type;
			typedef T									value_type;
			typedef T*									pointer;
			typedef T&									reference;

			VectorIterator() {}
			VectorIterator(pointer ptr) : _ptr(ptr) {}

			pointer	getPointer() const
			{
				return (_ptr);
			}
			VectorIterator &operator=(const VectorIterator &other)
			{
				_ptr = other._ptr;
				return (*this);
			};
			value_type &operator*() const
			{
				return (*_ptr);
			}
			value_type *operator->() const
			{
				return (_ptr);
			}
			VectorIterator &operator++()
			{
				_ptr++;
				return (*this);
			}
			VectorIterator operator++(int)
			{
				VectorIterator tmp = *this;
				operator++();
				return (tmp);
			}
			VectorIterator &operator--()
			{
				_ptr--;
				return (*this);
			}
			VectorIterator operator--(int)
			{
				VectorIterator tmp = *this;
				operator--();
				return (tmp);
			}
			bool operator== (const VectorIterator &x) 
			{
				return (_ptr == x._ptr);
			}
			bool operator!= (const VectorIterator &x)
			{
				return (_ptr != x._ptr);
			}
			bool operator> (const VectorIterator &x)
			{
				return (_ptr > x._ptr);
			}
			bool operator>= (const VectorIterator &x)
			{
				return (_ptr >= x._ptr);
			}
			bool operator< (const VectorIterator &x)
			{
				return (_ptr < x._ptr);
			}
			bool operator<= (const VectorIterator &x)
			{
				return (_ptr <= x._ptr);
			}
			VectorIterator operator+(int n)
			{
				VectorIterator aux(*this);
				aux += n;
				return (aux);
			}
			VectorIterator operator-(int n)
			{
				VectorIterator aux(*this);
				aux -= n;
				return (aux);
			}
			VectorIterator &operator+=(int n)
			{
				while (n < 0)
				{
					(*this)--;
					n++;
				}
				while (n > 0)
				{
					(*this)++;
					n--;
				}
				return (*this);
			}
			VectorIterator &operator-=(int n)
			{
				while (n > 0)
				{
					(*this)--;
					n--;
				}
				while (n < 0)
				{
					(*this)++;
					n++;
				}
				return (*this);
			}
			value_type &operator[](int n)
			{
				return (*(*this + n));
			}
		
		private:
			pointer _ptr;
	};

	// --- Const bidirectonial vector iterator ---
	template< class T >
    class ConstVectorIterator 
	{
		public:
			typedef std::random_access_iterator_tag		iterator_category;
			typedef std::ptrdiff_t						difference_type;
			typedef T									value_type;
			typedef T*									pointer;
			typedef T&									reference;

			ConstVectorIterator() {}
			ConstVectorIterator(pointer ptr) : _ptr(ptr) {}

			pointer	getPointer() const
			{
				return (_ptr);
			}
			ConstVectorIterator &operator=(const ConstVectorIterator &other)
			{
				_ptr = other._ptr;
				return (*this);
			};
			const value_type &operator*() const
			{
				return (*_ptr);
			}
			const value_type *operator->() const
			{
				return (_ptr);
			}
			ConstVectorIterator &operator++()
			{
				_ptr++;
				return (*this);
			}
			ConstVectorIterator operator++(int)
			{
				ConstVectorIterator tmp = *this;
				operator++();
				return (tmp);
			}
			ConstVectorIterator &operator--()
			{
				_ptr--;
				return (*this);
			}
			ConstVectorIterator operator--(int)
			{
				ConstVectorIterator tmp = *this;
				operator--();
				return (tmp);
			}
			bool operator== (const ConstVectorIterator &x) 
			{
				return (_ptr == x._ptr);
			}
			bool operator!= (const ConstVectorIterator &x)
			{
				return (_ptr != x._ptr);
			}
			bool operator> (const ConstVectorIterator &x)
			{
				return (_ptr > x._ptr);
			}
			bool operator>= (const ConstVectorIterator &x)
			{
				return (_ptr >= x._ptr);
			}
			bool operator< (const ConstVectorIterator &x)
			{
				return (_ptr < x._ptr);
			}
			bool operator<= (const ConstVectorIterator &x)
			{
				return (_ptr <= x._ptr);
			}
			ConstVectorIterator operator+(int n)
			{
				ConstVectorIterator aux(*this);
				aux += n;
				return (aux);
			}
			ConstVectorIterator operator-(int n)
			{
				ConstVectorIterator aux(*this);
				aux -= n;
				return (aux);
			}
			ConstVectorIterator &operator+=(int n)
			{
				while (n < 0)
				{
					(*this)--;
					n++;
				}
				while (n > 0)
				{
					(*this)++;
					n--;
				}
				return (*this);
			}
			ConstVectorIterator &operator-=(int n)
			{
				while (n > 0)
				{
					(*this)--;
					n--;
				}
				while (n < 0)
				{
					(*this)++;
					n++;
				}
				return (*this);
			}
			value_type &operator[](int n)
			{
				return (*(*this + n));
			}
	
		private:
			pointer _ptr;
	};

	// --- Reverse bidirectonial vector iterator ---
	template< class T >
    class RevVectorIterator 
	{
		public:
			typedef std::random_access_iterator_tag		iterator_category;
			typedef std::ptrdiff_t						difference_type;
			typedef T									value_type;
			typedef T*									pointer;
			typedef T&									reference;

			RevVectorIterator() {}
			RevVectorIterator(pointer ptr) : _ptr(ptr) {}

			pointer	getPointer() const
			{
				return (_ptr);
			}
			RevVectorIterator &operator=(const RevVectorIterator &other)
			{
				_ptr = other._ptr;
				return (*this);
			};
			value_type &operator*() const
			{
				return (*_ptr);
			}
			value_type *operator->() const
			{
				return (_ptr);
			}
			RevVectorIterator &operator++()
			{
				_ptr--;
				return (*this);
			}
			RevVectorIterator operator++(int)
			{
				RevVectorIterator tmp = *this;
				operator++();
				return (tmp);
			}
			RevVectorIterator &operator--()
			{
				_ptr++;
				return (*this);
			}
			RevVectorIterator operator--(int)
			{
				RevVectorIterator tmp = *this;
				operator--();
				return (tmp);
			}
			bool operator== (const RevVectorIterator &x) 
			{
				return (_ptr == x._ptr);
			}
			bool operator!= (const RevVectorIterator &x)
			{
				return (_ptr != x._ptr);
			}
			bool operator> (const RevVectorIterator &x)
			{
				return (_ptr > x._ptr);
			}
			bool operator>= (const RevVectorIterator &x)
			{
				return (_ptr >= x._ptr);
			}
			bool operator< (const RevVectorIterator &x)
			{
				return (_ptr < x._ptr);
			}
			bool operator<= (const RevVectorIterator &x)
			{
				return (_ptr <= x._ptr);
			}
			RevVectorIterator operator+(int n)
			{
				RevVectorIterator aux(*this);
				aux += n;
				return (aux);
			}
			RevVectorIterator operator-(int n)
			{
				RevVectorIterator aux(*this);
				aux -= n;
				return (aux);
			}
			RevVectorIterator &operator+=(int n)
			{
				while (n < 0)
				{
					(*this)--;
					n++;
				}
				while (n > 0)
				{
					(*this)++;
					n--;
				}
				return (*this);
			}
			RevVectorIterator &operator-=(int n)
			{
				while (n > 0)
				{
					(*this)--;
					n--;
				}
				while (n < 0)
				{
					(*this)++;
					n++;
				}
				return (*this);
			}
			value_type &operator[](int n)
			{
				return (*(*this + n));
			}
		
		private:
			pointer _ptr;
	};

	// --- Const bidirectonial vector iterator ---
	template< class T >
    class ConstRevVectorIterator 
	{
		public:
			typedef std::random_access_iterator_tag		iterator_category;
			typedef std::ptrdiff_t						difference_type;
			typedef T									value_type;
			typedef T*									pointer;
			typedef T&									reference;

			ConstRevVectorIterator() {}
			ConstRevVectorIterator(pointer ptr) : _ptr(ptr) {}

			pointer	getPointer() const
			{
				return (_ptr);
			}
			ConstRevVectorIterator &operator=(const ConstRevVectorIterator &other)
			{
				_ptr = other._ptr;
				return (*this);
			};
			const value_type &operator*() const
			{
				return (*_ptr);
			}
			const value_type *operator->() const
			{
				return (_ptr);
			}
			ConstRevVectorIterator &operator++()
			{
				_ptr--;
				return (*this);
			}
			ConstRevVectorIterator operator++(int)
			{
				ConstRevVectorIterator tmp = *this;
				operator++();
				return (tmp);
			}
			ConstRevVectorIterator &operator--()
			{
				_ptr++;
				return (*this);
			}
			ConstRevVectorIterator operator--(int)
			{
				ConstRevVectorIterator tmp = *this;
				operator--();
				return (tmp);
			}
			bool operator== (const ConstRevVectorIterator &x) 
			{
				return (_ptr == x._ptr);
			}
			bool operator!= (const ConstRevVectorIterator &x)
			{
				return (_ptr != x._ptr);
			}
			bool operator> (const ConstRevVectorIterator &x)
			{
				return (_ptr > x._ptr);
			}
			bool operator>= (const ConstRevVectorIterator &x)
			{
				return (_ptr >= x._ptr);
			}
			bool operator< (const ConstRevVectorIterator &x)
			{
				return (_ptr < x._ptr);
			}
			bool operator<= (const ConstRevVectorIterator &x)
			{
				return (_ptr <= x._ptr);
			}
			ConstRevVectorIterator operator+(int n)
			{
				ConstRevVectorIterator aux(*this);
				aux += n;
				return (aux);
			}
			ConstRevVectorIterator operator-(int n)
			{
				ConstRevVectorIterator aux(*this);
				aux -= n;
				return (aux);
			}
			ConstRevVectorIterator &operator+=(int n)
			{
				while (n < 0)
				{
					(*this)--;
					n++;
				}
				while (n > 0)
				{
					(*this)++;
					n--;
				}
				return (*this);
			}
			ConstRevVectorIterator &operator-=(int n)
			{
				while (n > 0)
				{
					(*this)--;
					n--;
				}
				while (n < 0)
				{
					(*this)++;
					n++;
				}
				return (*this);
			}
			value_type &operator[](int n)
			{
				return (*(*this + n));
			}
		
		private:
			pointer _ptr;
	};

};

#endif