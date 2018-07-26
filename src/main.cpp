#include "AbstractVM.hpp"

int main(int ac, char **av)
{
	AbstractVM avm;

	try	{
		if (ac == 1)
		{
			avm.fetchInstructions(std::cin, false);
			avm.decodeInstructions();
		}
		else
		{
			std::ifstream ifs;
			ifs.exceptions(std::ifstream::badbit);
			ifs.open(av[1]);
			avm.fetchInstructions(ifs, true);
			ifs.close();
		}
		avm.decodeInstructions();
	} catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}
	return (0);
}
