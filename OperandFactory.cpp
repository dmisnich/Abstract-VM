#include "Operand.hpp"
#include "OperandFactory.hpp"

OperandFactory::~OperandFactory()
{}

OperandFactory::OperandFactory(): methods
    {&OperandFactory::createInt8,
	&OperandFactory::createInt16,
	&OperandFactory::createInt32,
	&OperandFactory::createFloat,
	&OperandFactory::createDouble}
{}

OperandFactory::OperandFactory(OperandFactory const &copy)
{
    *this = copy;
}

const char *		OperandFactory::overflow::what() const noexcept
{
    return "overflow occurred";
}

OperandFactory::overflow::overflow() : out_of_range("overflow")
{}

IOperand const *	OperandFactory::createInt8(std::string const & value) const
{
	int		int32 = std::stoi(value);

	if (int32 < INT8_MIN || int32 > INT8_MAX)
		throw std::out_of_range("overflow");
	return new Operand<int8_t>(static_cast<int8_t>(int32), t_int8, 0);
}

IOperand const *	OperandFactory::createInt16(std::string const & value) const
{
	int		int32 = std::stoi(value);

	if (int32 < INT16_MIN || int32 > INT16_MAX)
		throw std::out_of_range("overflow");
	return new Operand<int16_t>(static_cast<int16_t>(int32), t_int16, 0);
}

IOperand const *	OperandFactory::createInt32(std::string const & value) const
{ return new Operand<int32_t>(std::stoi(value), t_int32, 0); }

IOperand const *	OperandFactory::createFloat(std::string const & value) const
{ return new Operand<float>(std::stof(value), t_float, 42); }

IOperand const *	OperandFactory::createDouble(std::string const & value) const
{ return new Operand<double>(std::stod(value), t_double, 42); }

IOperand const *	OperandFactory::createOperand(eOperandType type, std::string const & value) const
{
	IOperand const *	result;

	try
	{ result = (this->*methods[static_cast<int>(type)])(value); }
	catch (std::out_of_range & ex)
	{ throw OperandFactory::overflow(); }
	return result;
}



OperandFactory &	OperandFactory::operator = (OperandFactory const &r)
{
	static_cast<void>(r);
	return *this;
}


