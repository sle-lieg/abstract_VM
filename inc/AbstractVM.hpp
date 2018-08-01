#ifndef ABSTRACT_VM_HPP
# define ABSTRACT_VM_HPP

#include <vector>
#include <map>
#include <algorithm>
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
		void	lexer( void );
		void	parser( std::vector< std::string > const & instruct );

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

		void	reverse( void );
		void	get_max( void );
		void	get_min( void );
		void	clear( void );
		void	power( void );
		void	logic_and( void );
		void	logic_or( void );
		void	logic_xor( void );

		void	invalid( void );

	private:
		typedef void (AbstractVM::*instructions)(void);

		OperandFactory								_factory;

		std::vector< std::vector< std::string > >	_programInstructions;
		std::vector< std::string >					_errors;
		std::map< std::string, int >				_opcodes;
		std::map< std::string, eOperandType >		_optype;
		instructions								_instructions[18];
		std::vector<IOperand const *>				_stack;
		bool										_exit;

		void	_printErrors( void );
};

typedef	std::vector< std::vector< std::string > >::iterator vIter;
void	printList( std::vector< std::vector <std::string> > & v );
void	printVector( std::vector<std::string> & v );

#endif
