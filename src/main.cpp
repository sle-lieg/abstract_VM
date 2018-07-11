#include "AbstractVM.hpp"

int main(int ac, char **av)
{
	AbstractVM avm;

	try	{
		if (ac == 1)
			avm.fetchInstructions(std::cin);
		else
		{
			std::ifstream ifs;
			ifs.exceptions(std::ifstream::badbit);
			for (int i = 1; i < ac; i++)
			{
				ifs.open(av[i]);
				avm.fetchInstructions(ifs);
				// avm.decodeInstructions();
				av.executeInstructions
				ifs.close();
			}
		}
	} catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}
	return (0);
}
