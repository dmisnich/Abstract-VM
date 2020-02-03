#ifndef ABSTRACT_VM_OperandFactory_HPP
#define ABSTRACT_VM_OperandFactory_HPP

#include <vector>
#include "IOperand.hpp"
#include <stdexcept>

class OperandFactory;
typedef IOperand const *(OperandFactory::*factoryMethod)(std::string const &) const;

class OperandFactory
{
private:
	std::vector<factoryMethod>	methods;

	IOperand const *	createInt8(std::string const & v) const;
	IOperand const *	createInt16(std::string const & v) const;
	IOperand const *	createInt32(std::string const & v) const;
	IOperand const *	createFloat(std::string const & v) const;
	IOperand const *	createDouble(std::string const & v) const;

public:
	~OperandFactory();
	OperandFactory();
	OperandFactory(OperandFactory const &copy);

	class overflow : public std::out_of_range
	{
	public:
		overflow();
		const char *	what() const noexcept override;
	};

	IOperand const *	createOperand(eOperandType type, std::string const & v) const;

	OperandFactory &	operator = (OperandFactory const & r);
};

#endif
