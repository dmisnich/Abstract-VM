#ifndef ABSTRACT_VM_OPERAND_HPP
#define ABSTRACT_VM_OPERAND_HPP

#include "IOperand.hpp"
#include "OperandFactory.hpp"
#include <string>

template <class T>
class Operand : public IOperand
{
private:
	T				_val;
	std::string		_str_val;
	eOperandType	_type;
	int				_prec;

public:
    ~Operand();
	Operand();
    Operand(Operand const &copy);
	Operand(T value, eOperandType type, int prec);

		class mod_with_floating_point : public std::exception
		{
		public:
			const char *	what() const noexcept;
		};

		class division_by_zero : public std::exception
		{
		public:
			const char *	what() const noexcept;
		};

	int					getPrecision(void) const override;
	eOperandType		getType(void) const override;
	std::string const &	toString(void) const override;

	T const &			getValue(void) const;

	Operand &	operator = (Operand const & r);
    IOperand const * operator * (IOperand const & r) const override;
	IOperand const * operator / (IOperand const & r) const override;
	IOperand const * operator % (IOperand const & r) const override;
	IOperand const * operator + (IOperand const & r) const override;
	IOperand const * operator - (IOperand const & r) const override;
};

template <class T>
Operand<T>::Operand()
{}

template <class T>
Operand<T>::Operand(T val, eOperandType type, int prec)
		: _val(val),
		  _type(type),
		  _prec(prec)
{ _str_val = std::to_string(val); }

template <class T>
Operand<T>::Operand(Operand<T> const &copy)
{ *this = copy; }

template <class T>
Operand<T>::~Operand()
{}

template <class T>
Operand<T> &	Operand<T>::operator = (Operand<T> const & r)
{
	_val = r.getval();
	return *this;
}

template <class T>
const char *		Operand<T>::mod_with_floating_point::what() const noexcept
{
	return "mod uses only with integers";
}

template <class T>
const char *		Operand<T>::division_by_zero::what() const noexcept
{
	return "division by zero";
}


template <class T>
int					Operand<T>::getPrecision() const
{
	return _prec;
	}

template <class T>
eOperandType		Operand<T>::getType() const
{
	return _type;
}

template <class T>
T const &			Operand<T>::getValue() const
{
	return _val;
}

template <class T>
std::string const &	Operand<T>::toString() const
{
	return _str_val;
}

template <class T>
IOperand const *	Operand<T>::operator + (IOperand const & r) const
{
	IOperand const *	result_elem;
	OperandFactory		factory;
	double				result;

	result = std::stod(toString()) + std::stod(r.toString());
	if (getType() > r.getType())
		result_elem = factory.createOperand(getType(), std::to_string(result));
	else
		result_elem = factory.createOperand(r.getType(), std::to_string(result));
	return result_elem;
}

template <class T>
IOperand const *	Operand<T>::operator - (IOperand const & r) const
{
	IOperand const *	result_elem;
	OperandFactory		factory;
	double				result;

	result = std::stod(toString()) - std::stod(r.toString());
	if (getType() > r.getType())
		result_elem = factory.createOperand(getType(), std::to_string(result));
	else
		result_elem = factory.createOperand(r.getType(), std::to_string(result));
	return result_elem;
}

template <class T>
IOperand const *	Operand<T>::operator * (IOperand const & r) const
{
	IOperand const *	result_elem;
	OperandFactory		factory;
	double				result;

	result = std::stod(toString()) * std::stod(r.toString());
	if (getType() > r.getType())
		result_elem = factory.createOperand(getType(), std::to_string(result));
	else
		result_elem = factory.createOperand(r.getType(), std::to_string(result));
	return result_elem;
}

template <class T>
IOperand const *	Operand<T>::operator / (IOperand const & r) const
{
	IOperand const *	result_elem;
	OperandFactory		factory;
	double				result;

	if (!std::stod(r.toString()))
		throw Operand<T>::division_by_zero();

	result = std::stod(toString()) / std::stod(r.toString());
	if (getType() > r.getType())
		result_elem = factory.createOperand(getType(), std::to_string(result));
	else
		result_elem = factory.createOperand(r.getType(), std::to_string(result));
	return result_elem;
}

template <class T>
IOperand const *	Operand<T>::operator % (IOperand const & r) const
{
	IOperand const *	result_elem;
	OperandFactory		factory;
	intmax_t			result;

	if (getType() == t_float || getType() == t_double
			|| r.getType() == t_float || r.getType() == t_double)
		throw Operand<T>::mod_with_floating_point();
	if (!std::stod(r.toString()))
		throw Operand<T>::division_by_zero();

	result = std::stoll(toString()) % std::stoll(r.toString());
	if (getType() > r.getType())
		result_elem = factory.createOperand(getType(), std::to_string(result));
	else
		result_elem = factory.createOperand(r.getType(), std::to_string(result));
	return result_elem;
}


#endif