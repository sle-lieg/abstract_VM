#include "AVMExceptions.hpp"
#include <iostream>

GenericException::GenericException( std::vector< std::string > & errors )
{
	for (std::vector< std::string >::iterator it = errors.begin(); it != errors.end(); it++)
	{
		_errors.append(*it);
		if (*it != errors.back())
			_errors.append("\n");
	}
}

GenericException::GenericException( std::string const & error ) :
	_errors(error)
{}

GenericException::GenericException( GenericException const & rhs) :
	_errors(rhs._errors)
{}

GenericException & GenericException::operator=( GenericException const & rhs)
{
	if (this != &rhs)
		_errors = rhs._errors;
	return *this;
}

GenericException::~GenericException( void )
{}

const char* GenericException::what() const throw()
{
	return _errors.c_str();
}


LexicalException::LexicalException( std::vector< std::string > & errors ) :
	GenericException(errors)
{}

LexicalException::~LexicalException( void )
{}

AassertException::AassertException( std::string & error ) :
	GenericException(error)
{}

AassertException::~AassertException( void )
{}

EmptyStackException::EmptyStackException( char const * error ) :
	GenericException(error)
{}

EmptyStackException::~EmptyStackException( void )
{}