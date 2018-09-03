#include "AbstractVM.hpp"

void printList( std::vector< std::vector <std::string> > & v )
{
	for (vIter it = v.begin(); it != v.end(); it++)
	{
		for (size_t j = 0; j < it->size(); j++)
			std::cout << "\"" << (*it)[ j ] << "\" ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void printVector( std::vector<std::string> & v )
{
	for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); it++)
	{
		std::cout << "\"" << *it << "\" ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}