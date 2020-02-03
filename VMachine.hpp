#ifndef ABSTRACT_VM_VMACHINE_HPP
#define  ABSTRACT_VM_VMACHINE_HPP

#include <map>
#include <regex>
#include "MStack.hpp"
#include "IOperand.hpp"

class VMachine;

typedef std::pair<std::string,std::string> pars_cmd;
typedef void (VMachine::*cmd)(pars_cmd, int);

class VMachine
{
private:

    MStack<IOperand const *>			_stack;
	std::map<std::string, cmd>				_cmd;
	std::deque<std::pair<cmd, pars_cmd>>	_queue;

	void			_delete_element();
	
    eOperandType	_str_to_type(std::string, int line);
	bool			_cmdFind(std::string input);
	void			_printRecursive(std::deque<IOperand const *>::iterator it);

    void	_push(pars_cmd pars, int line);
	void	_pop(pars_cmd pars, int line);
	void	_dump(pars_cmd pars, int line);
	void	_assert(pars_cmd pars, int line);
	void	_add(pars_cmd pars, int line);
	void	_sub(pars_cmd pars, int line);
	void	_mul(pars_cmd pars, int line);
	void	_div(pars_cmd pars, int line);
	void	_mod(pars_cmd pars, int line);
	void	_print(pars_cmd pars, int line);
	void	_exit(pars_cmd pars, int line);  

public:
    VMachine();
    VMachine(VMachine const & copy);
    ~VMachine();

    void				Run();
    void				ReadCmd(); // from stdin
	void				ReadCmd(std::string nameFile);

    VMachine &	operator = (VMachine const & r);

    	class unexpected_eof : public std::exception
		{
		private:
			int 	_line;
		public:
			unexpected_eof();
			unexpected_eof(int line);
			unexpected_eof(unexpected_eof const & copy);
			~unexpected_eof();
			const char *		what() const noexcept override;
			int 				getLine() const;
			unexpected_eof &	operator = (unexpected_eof const & r);
		};

        class execution_impossible : public std::exception
		{
		private:
			int 	_line;
		public:
			execution_impossible();
			execution_impossible(int line);
			execution_impossible(execution_impossible const & copy);
			~execution_impossible();
			const char *			what() const noexcept override;
			int 					getLine() const;
			execution_impossible &	operator = (execution_impossible const & r);
		};

        class not_enough_operands : public std::exception
		{
		private:
			int 	_line;
		public:
			not_enough_operands();
			not_enough_operands(int line);
			not_enough_operands(not_enough_operands const & copy);
			~not_enough_operands();
			const char *			what() const noexcept override;
			int 					getLine() const;
			not_enough_operands &	operator = (not_enough_operands const & r);
		};

        class assert_false : public std::exception
		{
		private:
			int 	_line;
		public:
			assert_false();
			assert_false(int line);
			assert_false(assert_false const & copy);
			~assert_false();
			const char *	what() const noexcept override;
			int 			getLine() const;
			assert_false &	operator = (assert_false const & r);
		};

        class cmd_unknown : public std::exception
		{
		private:
			int 	_line;
		public:
			cmd_unknown();
			cmd_unknown(int line);
			cmd_unknown(cmd_unknown const & copy);
			~cmd_unknown();
			const char *	what() const noexcept override;
			int 			getLine() const;
			cmd_unknown &	operator = (cmd_unknown const & r);
		};

        class not_open_file : public std::exception
		{
		public:
			const char *	what() const noexcept override;
		};
};




#endif