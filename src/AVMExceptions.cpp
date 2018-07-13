#include "AVMExceptions.hpp"

LexicalException::LexicalException( std::vector< std::string > & errors ) :
	_errors(errors)
{}

LexicalException::~LexicalException( void )
{}

const char* LexicalException::what() const throw()
{
	std::string	msg;

	for (std::vector< std::string >::iterator it = _errors.begin(); it != _errors.end(); it++)
	{
		msg.append(*it);
	}
	return msg.c_str();
}
