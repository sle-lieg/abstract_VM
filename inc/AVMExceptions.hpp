#ifndef AVMEXCEPTIONS_HPP
# define AVMEXCEPTIONS_HPP

#include <exception>
#include <vector>
#include <string>

class LexicalException : public std::exception
{
	public:
		LexicalException( std::vector< std::string > & errors );
		LexicalException( LexicalException const & );
		virtual ~LexicalException( void );
		virtual const char* what() const throw();
	
	private:
		LexicalException( void );
		LexicalException & operator=( LexicalException const & );
		std::string						_errors;
};

#endif
