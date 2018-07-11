#include "AbstractVM.hpp"

void printList( std::list< std::vector <std::string> > & v )
{
	for (listIterator it = v.begin(); it != v.end(); it++)
	{
		for (size_t j = 0; j < it->size(); j++)
			std::cout << "\"" << (*it)[ j ] << "\" ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
