#include "AbstractVM.hpp"

int main(int ac, char **av)
{
	AbstractVM avm;

	try	{
		if (ac == 1)
			avm.fetchInstructions(std::cin, false);
		else
		{
			std::ifstream ifs;
			ifs.exceptions(std::ifstream::failbit);
			ifs.open(av[1]);
			avm.fetchInstructions(ifs, true);
			ifs.close();
		}
		avm.lexer();
		if (avm.isValid())
			avm.parser();
	} catch (std::ifstream::failure e) {
	    std::cerr << "Exception opening file\n";
	} catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}
	return (0);
}
