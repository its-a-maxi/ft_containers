/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 10:59:11 by mmonroy-          #+#    #+#             */
/*   Updated: 2021/05/10 09:58:58 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
# define QUEUE_HPP

# include "list.hpp"

namespace ft
{
	// --- Template --
	template <
	class T,
	class Container = ft::list<T>
	>

	// --- Body ---
	class queue
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
			explicit queue (const container_type& ctnr = container_type()) : _container(ctnr)
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

		// > Front
			value_type& front()
			{
				return (this->_container.front());
			}
			const value_type& front() const
			{
				return (this->_container.front());
			}	// Return the first/oldest element of the container.
			
		// > Back
			value_type& back()
			{
				return (this->_container.back());
			}
			const value_type& back() const
			{
				return (this->_container.back());
			}	// Return the last/newest element of the container.

		// > Push
			void push(const value_type& val)
			{
				this->_container.push_back(val);
				return ;
			}	// Add an element at the end of the container.

		// > Pop
			void pop()
			{
				this->_container.pop_front();
				return ;
			}	// Eliminate first/oldest element of the container.
	};

	// --- Non-member functions overload ---

	// > Relational operators
		// ==
		template <class T, class Container>
		bool operator== (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
		{
			return (lhs._container == rhs._container);
		}
		// !=
		template <class T, class Container>
		bool operator!= (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
		{
			return (lhs._container != rhs._container);
		}
		// <
		template <class T, class Container>
		bool operator<  (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
		{
			return (lhs._container < rhs._container);
		}
		// <=
		template <class T, class Container>
		bool operator<=  (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
		{
			return (lhs._container <= rhs._container);
		}
		// >
		template <class T, class Container>
		bool operator>  (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
		{
			return (lhs._container > rhs._container);
		}
		// >=
		template <class T, class Container>
		bool operator>=  (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
		{
			return (lhs._container >= rhs._container);
		}
}

#endif /* ***************************************************** QUEUE_H */