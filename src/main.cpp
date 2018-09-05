#include "AbstractVM.hpp"
#include "sys/types.h"
#include "sys/stat.h"

int main(int ac, char **av)
{
	AbstractVM	avm;
	struct stat	buf;

	try	{
		if (ac == 1)
			avm.fetchInstructions(std::cin, false);
		else
		{
			stat(av[1], &buf);
			if ((buf.st_mode & S_IFMT) != S_IFREG)
			{
				std::cout << "Error: argument is not a valid filename" << std::endl;
				return -1;
			}
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
