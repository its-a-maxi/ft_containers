/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 10:26:06 by mmonroy-          #+#    #+#             */
/*   Updated: 2021/05/10 09:59:17 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "list.hpp"

namespace ft
{
	// --- Template --
	template <
	class T,
	class Container = ft::list<T>
	>

	// --- Body ---
	class stack
	{
	// --- Member types ---
		public:
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;

	// --- Internal data ---
		private:
			container_type		_container;

	// --- Member functions ---
		public:
		// > Constructor
			explicit stack (const container_type& ctnr = container_type()) : _container(ctnr)
			{
				return ;
			}	// Intitialize the container.

		// > Empty
			bool empty() const
			{
				return (this->_container.empty());
			}	// Check if the container is empty.

		// > Size
			size_type size() const
			{
				return (this->_container.size());
			}	// Return size of the container.

		// > Top
			value_type& top()
			{
				return (this->_container.back());
			}
			const value_type& top() const
			{
				return (this->_container.back());
			}	// Return the top of the container (last element).

		// > Push
			void push(const value_type& val)
			{
				this->_container.push_back(val);
				return ;
			}	// Add an element at the end of the container.

		// > Pop
			void pop()
			{
				this->_container.pop_back();
				return ;
			}	// Eliminate last element of the container.
	};

	// --- Non-member functions overload ---

	// > Relational operators
		// ==
		template <class T, class Container>
		bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
		{
			return (lhs._container == rhs._container);
		}
		// !=
		template <class T, class Container>
		bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
		{
			return (lhs._container != rhs._container);
		}
		// <
		template <class T, class Container>
		bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
		{
			return (lhs._container < rhs._container);
		}
		// <=
		template <class T, class Container>
		bool operator<=  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
		{
			return (lhs._container <= rhs._container);
		}
		// >
		template <class T, class Container>
		bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
		{
			return (lhs._container > rhs._container);
		}
		// >=
		template <class T, class Container>
		bool operator>=  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
		{
			return (lhs._container >= rhs._container);
		}
}

#endif /* ***************************************************** STACK_H */
