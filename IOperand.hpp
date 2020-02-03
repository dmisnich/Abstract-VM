#ifndef ABSTRACT_VM_IOPERAND_HPP
#define ABSTRACT_VM_IOPERAND_HPP

#include <string>

enum eOperandType
{
	t_int8,
	t_int16,
	t_int32,
	t_float,
	t_double
};

class IOperand
{
public:

	virtual IOperand const * operator + (IOperand const & r) const = 0;
	virtual IOperand const * operator - (IOperand const & r) const = 0;
	virtual IOperand const * operator * (IOperand const & r) const = 0;
	virtual IOperand const * operator / (IOperand const & r) const = 0;
	virtual IOperand const * operator % (IOperand const & r) const = 0;

	virtual std::string const &	toString(void) const = 0;

    virtual int				getPrecision(void) const = 0;
	virtual eOperandType	getType(void) const = 0;

	virtual ~IOperand(void) {}
};

#endif 