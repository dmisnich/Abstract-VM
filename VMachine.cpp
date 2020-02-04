#include <iostream>
#include <fstream>
#include "VMachine.hpp"
#include "OperandFactory.hpp"

VMachine::VMachine()
		: _cmd({
			{"\\s*push\\s*(int(8|16|32)|float|double)\\s*\\(\\s*(-?\\d+.?\\d*)\\s*\\)\\s*(;.*|)", &VMachine::_push},
			{"\\s*pop\\s*(;.*|)", &VMachine::_pop},
			{"\\s*dump\\s*(;.*|)", &VMachine::_dump},
			{"\\s*assert\\s*(int(8|16|32)|float|double)\\s*\\(\\s*(-?\\d+.?\\d*)\\s*\\)\\s*(;.*|)", &VMachine::_assert},
			{"\\s*add\\s*(;.*|)", &VMachine::_add},
			{"\\s*sub\\s*(;.*|)", &VMachine::_sub},
			{"\\s*mul\\s*(;.*|)", &VMachine::_mul},
			{"\\s*div\\s*(;.*|)", &VMachine::_div},
			{"\\s*mod\\s*(;.*|)", &VMachine::_mod},
			{"\\s*print\\s*(;.*|)", &VMachine::_print},
			{"\\s*exit\\s*(;.*|)", &VMachine::_exit}
			   })
{}

VMachine::VMachine(VMachine const &copy)
{ 
    *this = copy; 
}

VMachine::~VMachine()
{
	for (IOperand const * elem : _stack)
		delete elem;
}

VMachine &	VMachine::operator = (VMachine const & r)
{
	_stack = r._stack;
	_queue = r._queue;
	_cmd = r._cmd;
	return *this;
}

void			VMachine::_delete_element()
{ delete _stack.top(); _stack.pop(); }

#define NUM_OF_TYPES 5

eOperandType	VMachine::_str_to_type(std::string str, int line)
{
	std::string		types[NUM_OF_TYPES] = {"int8", "int16", "int32", "float", "double"};

	for (int i = 0; i < NUM_OF_TYPES; ++i)
		if (str == types[i])
			return static_cast<eOperandType>(i);
	throw VMachine::cmd_unknown(line);
}

void			VMachine::_printRecursive(std::deque<IOperand const *>::iterator it)
{
	if (it == _stack.end())
		return;
	_printRecursive(it + 1);
	std::cout << (*it)->toString() << std::endl;
}

bool			VMachine::_cmdFind(std::string input)
{
	std::cmatch		parsed;

	for (std::pair<std::string,cmd> pair : _cmd)
		if (std::regex_match(input.c_str(), parsed, std::regex(pair.first)))
		{
			_queue.push_back(std::make_pair(pair.second, std::make_pair(parsed[1], parsed[3])));
			return true;
		}
	return false;
}

void			VMachine::CmdRead()
{
	std::string	input;
	int			line = 0;

	do
	{
		if (std::cin.eof())
			throw VMachine::unexpected_eof(line);
		++line;
		std::getline(std::cin, input);
		if (!_cmdFind(input) && !std::cin.eof() && input[0] != ';')
			throw VMachine::cmd_unknown(line);
	} while (input != ";;");
}

void			VMachine::CmdRead(std::string filename)
{
	std::ifstream	file(filename);
	std::string		input;
	int				line = 0;

	if (!file.is_open())
		throw VMachine::not_open_file();
	do
	{
		if (file.eof())
			throw VMachine::unexpected_eof(line);
		++line;
		std::getline(file, input);
		if (!_cmdFind(input) && !file.eof() && input[0] != ';')
			throw VMachine::cmd_unknown(line);
	} while (input != "exit");
}

void			VMachine::Run()
{
	int		line = 0;

	for (std::pair<cmd,pars_cmd> p : _queue)
	{
		++line;
		(this->*p.first)(p.second, line);
	}
}

//unexpected_eof

VMachine::unexpected_eof::unexpected_eof() : _line(0)
{}

VMachine::unexpected_eof::unexpected_eof(int line) : _line(line)
{}

VMachine::unexpected_eof::unexpected_eof(VMachine::unexpected_eof const & copy)
{
    *this = copy;
}

VMachine::unexpected_eof::~unexpected_eof()
{}

VMachine::unexpected_eof &	VMachine::unexpected_eof::operator = (VMachine::unexpected_eof const & r)
{
    _line = r._line;
    return *this;
}

const char *	VMachine::unexpected_eof::what() const noexcept
{
    return "unexpected eof";
}

int 			VMachine::unexpected_eof::getLine() const
{
    return _line;
}

//execution_impossible

VMachine::execution_impossible::execution_impossible() : _line(0)
{}

VMachine::execution_impossible::execution_impossible(int line) : _line(line)
{}

VMachine::execution_impossible::execution_impossible(VMachine::execution_impossible const & copy)
{ 
    *this = copy;
}

VMachine::execution_impossible::~execution_impossible()
{}

VMachine::execution_impossible &	VMachine::execution_impossible::operator = (VMachine::execution_impossible const & r)
{
    _line = r._line; return *this;
}

const char *	VMachine::execution_impossible::what() const noexcept
{
    return "execution of command impossible";
}

int 			VMachine::execution_impossible::getLine() const
{
    return _line;
}

//not_enough_operands

VMachine::not_enough_operands::not_enough_operands() : _line(0)
{}

VMachine::not_enough_operands::not_enough_operands(int line) : _line(line)
{}

VMachine::not_enough_operands::not_enough_operands(VMachine::not_enough_operands const & copy)
{
    *this = copy;
}

VMachine::not_enough_operands::~not_enough_operands()
{}

VMachine::not_enough_operands &	VMachine::not_enough_operands::operator = (VMachine::not_enough_operands const & r)
{
    _line = r._line; return *this;
}

const char *	VMachine::not_enough_operands::what() const noexcept
{
    return "not enough operands";
}

int 			VMachine::not_enough_operands::getLine() const
{
    return _line;
}

//not_open_file

const char *	VMachine::not_open_file::what() const noexcept
{
    return "file not open";
}

//cmd_uknown

VMachine::cmd_unknown::cmd_unknown() : _line(0)
{}

VMachine::cmd_unknown::cmd_unknown(int line) : _line(line)
{}

VMachine::cmd_unknown::cmd_unknown(VMachine::cmd_unknown const & copy)
{
    *this = copy;
}

VMachine::cmd_unknown::~cmd_unknown()
{}

VMachine::cmd_unknown &	VMachine::cmd_unknown::operator = (VMachine::cmd_unknown const & r)
{
    _line = r._line;
    return *this;
}

const char *	VMachine::cmd_unknown::what() const noexcept
{
    return "unknown command";
}

int 			VMachine::cmd_unknown::getLine() const
{
    return _line;
}

//assert_false

VMachine::assert_false::assert_false() : _line(0)
{}

VMachine::assert_false::assert_false(int line) : _line(line)
{}

VMachine::assert_false::assert_false(VMachine::assert_false const & copy)
{
    *this = copy;
}

VMachine::assert_false::~assert_false()
{}

VMachine::assert_false &	VMachine::assert_false::operator = (VMachine::assert_false const & r)
{
    _line = r._line;
    return *this;
}

const char *	VMachine::assert_false::what() const noexcept
{
    return "assert false";
}

int 			VMachine::assert_false::getLine() const
{
    return _line;
}

//VMachine COMMANDS

void			VMachine::_push(pars_cmd pars, int line)
{ 
   _stack.push(OperandFactory().createOperand(_str_to_type(pars.first, line), pars.second));
}

void			VMachine::_pop(pars_cmd pars, int line)
{
	static_cast<void>(pars);
	if (_stack.empty()) throw VMachine::execution_impossible(line);
	_stack.pop();
}

void			VMachine::_dump(pars_cmd pars, int line)
{
	static_cast<void>(pars);
	static_cast<void>(line);
	_printRecursive(_stack.begin());
}

void			VMachine::_assert(pars_cmd pars, int line)
{
	if (_str_to_type(pars.first, line) != _stack.top()->getType())
		throw VMachine::assert_false(line);

	bool	assert;

	switch (_stack.top()->getType())
	{
		case t_float:
			assert = std::stof(pars.second) != std::stof(_stack.top()->toString());
			break ;
		case t_double:
			assert = std::stod(pars.second) != std::stod(_stack.top()->toString());
			break ;
		default:
			assert = std::stoi(pars.second) != std::stoi(_stack.top()->toString());
			break ;
	}
	if (assert)
		throw VMachine::assert_false(line);
}

void			VMachine::_add(pars_cmd pars, int line)
{
	static_cast<void>(pars);
	if (_stack.size() < 2)
		throw VMachine::not_enough_operands(line);

	IOperand const *	new_elem;

	new_elem = **(_stack.end() - 2) + **(_stack.end() - 1);
	_delete_element();
	_delete_element();
	_stack.push(new_elem);
}

void			VMachine::_sub(pars_cmd pars, int line)
{
	static_cast<void>(pars);
	if (_stack.size() < 2)
		throw VMachine::not_enough_operands(line);

	IOperand const *	new_elem;

	new_elem = **(_stack.end() - 2) - **(_stack.end() - 1);
	_delete_element();
	_delete_element();
	_stack.push(new_elem);
}

void			VMachine::_mul(pars_cmd pars, int line)
{
	static_cast<void>(pars);
	if (_stack.size() < 2)
		throw VMachine::not_enough_operands(line);

	IOperand const *	new_elem;

	new_elem = **(_stack.end() - 2) * **(_stack.end() - 1);
	_delete_element();
	_delete_element();
	_stack.push(new_elem);
}

void			VMachine::_div(pars_cmd pars, int line)
{
	static_cast<void>(pars);
	if (_stack.size() < 2)
		throw VMachine::not_enough_operands(line);

	IOperand const *	new_elem;

	new_elem = **(_stack.end() - 2) / **(_stack.end() - 1);
	_delete_element();
	_delete_element();
	_stack.push(new_elem);
}

void			VMachine::_mod(pars_cmd pars, int line)
{
	static_cast<void>(pars);
	if (_stack.size() < 2)
		throw VMachine::not_enough_operands(line);

	IOperand const *	new_elem;

	new_elem = **(_stack.end() - 2) % **(_stack.end() - 1);
	_delete_element();
	_delete_element();
	_stack.push(new_elem);
}

void			VMachine::_print(pars_cmd pars, int line)
{
	static_cast<void>(pars);
	if (_stack.top()->getType() != t_int8)
		throw VMachine::assert_false(line);
	std::cout << static_cast<char>(std::stoi(_stack.top()->toString())) << std::endl;
}

void			VMachine::_exit(pars_cmd pars, int line)
{
	static_cast<void>(pars);
	static_cast<void>(line);
	//VMachine::~VMachine();
	exit(0);
}
