#ifndef ABSTRACT_VM_HPP
# define ABSTRACT_VM_HPP

#include <vector>
#include <map>
#include <stack>
#include <regex>
#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include "AVMExceptions.hpp"


#include "OperandFactory.hpp"

class IOperand;
class AbstractVM
{
	public:
		AbstractVM( void );
		~AbstractVM( void );
		AbstractVM( AbstractVM const & );
		AbstractVM&	operator=( AbstractVM const & );

		std::vector< std::vector< std::string > >	&	getProgramInstructions( void );
		double											get_operand_value( void ) const;

		void	fetchInstructions( std::istream& file, bool isFromFile  );
		void	decodeInstructions( void );
		void	executeInstruction( std::vector< std::string > const & instruct );

		void	push( IOperand const * value );
		void	aassert( IOperand const * value ) const;
		void	pop( void );
		void	dump( void );
		void	add( void );
		void	sub( void );
		void	mul( void );
		void	div( void );
		void	mod( void );
		void	print( void );
		void	eexit( void );
		void	invalid( void );

	private:
		typedef void (AbstractVM::*instructions)(void);

		OperandFactory								_factory;

		std::vector< std::vector< std::string > >	_programInstructions;
		std::vector< std::string >					_errors;
		std::map< std::string, int >				_opcodes;
		std::map< std::string, eOperandType >		_optype;
		instructions								_instructions[10];
		std::stack<IOperand *>						_stack;

		void	_printErrors( void );
};

typedef	std::vector< std::vector< std::string > >::iterator vIter;
void	printList( std::vector< std::vector <std::string> > & v );
void	printVector( std::vector<std::string> & v );

#endif
