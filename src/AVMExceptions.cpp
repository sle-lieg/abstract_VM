#include "AVMExceptions.hpp"
#include <iostream>

LexicalException::LexicalException( std::vector< std::string > & errors )
{
	for (std::vector< std::string >::iterator it = errors.begin(); it != errors.end(); it++)
	{
		_errors.append(*it);
		if (*it != errors.back())
			_errors.append("\n");
	}
}

LexicalException::LexicalException( LexicalException const & rhs) :
	_errors(rhs._errors)
{}

LexicalException::~LexicalException( void )
{}

const char* LexicalException::what() const throw()
{
	return _errors.c_str();
}
