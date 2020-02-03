#include "VMachine.hpp"
#include <iostream>
#include <sstream>

int		main(int argc, char **argv)
{
	VMachine		virtualMachine;

	try
	{
		if (argc > 1)
			virtualMachine.ReadCmd(argv[1]);
		else
			virtualMachine.ReadCmd();
		virtualMachine.Run();
	}
	catch (VMachine::cmd_unknown & ex)
	{ std::cout << "line " << ex.getLine() << ": " << ex.what() << std::endl; }
	catch (VMachine::assert_false & ex)
	{ std::cout << "line " << ex.getLine() << ": " << ex.what() << std::endl; }
	catch (VMachine::not_enough_operands & ex)
	{ std::cout << "line " << ex.getLine() << ": " << ex.what() << std::endl; }
	catch (VMachine::execution_impossible & ex)
	{ std::cout << "line " << ex.getLine() << ": " << ex.what() << std::endl; }
	catch (VMachine::unexpected_eof & ex)
	{ std::cout << "line " << ex.getLine() << ": " << ex.what() << std::endl; }
	catch (std::exception & ex)
	{ std::cout << ex.what() << std::endl; }
	return 0;
}