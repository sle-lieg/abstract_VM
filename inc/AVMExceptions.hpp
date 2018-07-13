#ifndef AVMEXCEPTIONS_HPP
# define AVMEXCEPTIONS_HPP

#include <exception>
#include <vector>
#include <string>

class LexicalException : public std::exception
{
	public:
		LexicalException( std::vector< std::string > & errors );
		virtual ~LexicalException( void );
		virtual const char* what() const throw();
	
	private:
		std::vector< std::string > &	_errors;
};

#endif