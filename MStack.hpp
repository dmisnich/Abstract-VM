#ifndef ABSTRACT_VM_MSTACK_HPP
#define ABSTRACT_VM_MSTACK_HPP

#include <stack>

template <class T>
class MStack : public std::stack<T>
{
public:
	MStack();
	MStack(MStack const &copy);
	~MStack();

		class iterator : public std::deque<T>::iterator
		{
		public:
			iterator();
			iterator(iterator const & copy);
			~iterator();

			iterator &	operator = (iterator const & r);
			iterator &	operator = (typename std::deque<T>::iterator const & r);
		};

	iterator	begin();
	iterator	end();

	MStack &	operator = (MStack const & r);
	
};

template <class T>
MStack<T>::MStack()
{}

template <class T>
MStack<T>::MStack(MStack<T> const &copy)
{
	*this = copy;
}

template <class T>
MStack<T>::~MStack()
{}

template <class T>
MStack<T> &	MStack<T>::operator = (MStack<T> const & r)
{
	this->c = r.c;
	return *this;
}

template <class T>
MStack<T>::iterator::iterator()
{}

template <class T>
MStack<T>::iterator::iterator(iterator const &copy)
{
	*this = copy;
}

template <class T>
MStack<T>::iterator::~iterator()
{}

template <class T>
typename MStack<T>::iterator &	MStack<T>::iterator::operator = (typename MStack<T>::iterator const & r)
{
	std::deque<T>::iterator::operator=(r);
	return *this;
}

template <class T>
typename MStack<T>::iterator &	MStack<T>::iterator::operator = (typename std::deque<T>::iterator const & r)
{
	std::deque<T>::iterator::operator=(r);
	return *this;
}

template <class T>
typename MStack<T>::iterator	MStack<T>::begin()
{
	MStack<T>::iterator	it;

	it = this->c.begin();
	return it;
}

template <class T>
typename MStack<T>::iterator	MStack<T>::end()
{
	MStack<T>::iterator	it;

	it = this->c.end();
	return it;
}

#endif