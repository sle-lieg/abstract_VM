#ifndef AVMEXCEPTIONS_HPP
# define AVMEXCEPTIONS_HPP

#include <exception>
#include <vector>
#include <string>

class GenericException : public std::exception
{
	public:
		GenericException( std::vector< std::string > & errors );
		GenericException( std::string const & error );
		GenericException( GenericException const & );
		GenericException & operator=( GenericException const & );
		virtual ~GenericException( void );
		virtual const char* what() const throw();
	
	protected:
		GenericException( void );

		std::string	_errors;	
};

class LexicalException : public GenericException
{
	public:
		LexicalException( std::vector< std::string > & errors );
		virtual ~LexicalException( void );
};

class AassertException : public GenericException
{
	public:
		AassertException( std::string & error );
		virtual ~AassertException( void );
};

#endif
