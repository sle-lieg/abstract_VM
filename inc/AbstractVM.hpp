#ifndef ABSTRACT_VM_HPP
# define ABSTRACT_VM_HPP

# include <boost/algorithm/string.hpp>
# include <stack>
# include <vector>
# include <map>
# include <iostream>
# include <fstream>
# include <regex>
# include "AVMExceptions.hpp"

typedef enum	eOperandType {
	INT8, INT16, INT32, FLOAT, DOUBLE
}				eOperandType;

// typedef enum	eInstructions {
// 	PUSH, ASSERT, POP, DUMP, ADD, SUB, MUL, DIV, MOD, PRINT, EXIT
// }				eInstructions;

class IOperand;
class AbstractVM
{
	public:
		AbstractVM( void );
		~AbstractVM( void );
		AbstractVM( AbstractVM const & );
		AbstractVM&	operator=( AbstractVM const & );

		std::vector< std::vector< std::string > >	&	getProgramInstructions( void );

		void	fetchInstructions( std::istream& file, bool isFromFile  );
		void	decodeInstructions( void );

		void	push( std::string value );
		void	aassert( std::string value ) const;
		void	pop( void );
		void	dump( void );
		void	add( void );
		void	sub( void );
		void	mul( void );
		void	div( void );
		void	mod( void );
		void	print( void );
		void	exit( void );
		void	invalid( void );

		IOperand const * createOperand(eOperandType type, std::string const & value) const;

	private:
		std::vector< std::vector< std::string > >	_programInstructions;
		std::vector< std::string >				_errors;
		std::map<std::string, int>				_opcodes;

		void	printErrors( void );
		// **************** //
		typedef IOperand const *(AbstractVM::*createFunc)(std::string const & value) const;
		typedef void (AbstractVM::*instructions)(void);

		std::stack<IOperand *>		_stack;
		createFunc					_createFunc[5];
		instructions				_instructions[10];

		IOperand const * createInt8( std::string const & value ) const;
		IOperand const * createInt16( std::string const & value ) const;
		IOperand const * createInt32( std::string const & value ) const;
		IOperand const * createFloat( std::string const & value ) const;
		IOperand const * createDouble( std::string const & value ) const;

};

typedef	std::vector< std::vector< std::string > >::iterator vIter;
void	printList( std::vector< std::vector <std::string> > & v );

#endif
