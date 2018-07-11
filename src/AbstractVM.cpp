#include "AbstractVM.hpp"

AbstractVM::AbstractVM() :
	_opcodes{
		{"push", 1},
		{"assert", 2},
		{"pop", 3},
		{"dump", 4},
		{"add", 5},
		{"sub", 6},
		{"mul", 7},
		{"div", 8},
		{"mod", 9},
		{"print", 10},
		{"exit", 11}
	}
{
	_createFunc[0] = &AbstractVM::createInt8;
	_createFunc[1] = &AbstractVM::createInt16;
	_createFunc[2] = &AbstractVM::createInt32;
	_createFunc[3] = &AbstractVM::createFloat;
	_createFunc[4] = &AbstractVM::createDouble;

	_instructions[0] = &AbstractVM::invalid;
	_instructions[1] = &AbstractVM::pop;
	_instructions[2] = &AbstractVM::dump;
	_instructions[3] = &AbstractVM::add;
	_instructions[4] = &AbstractVM::sub;
	_instructions[5] = &AbstractVM::mul;
	_instructions[6] = &AbstractVM::div;
	_instructions[7] = &AbstractVM::mod;
	_instructions[8] = &AbstractVM::print;
	_instructions[9] = &AbstractVM::exit;
}

AbstractVM::~AbstractVM( void )
{}

AbstractVM::AbstractVM(AbstractVM const & rhs)
{
	*this = rhs;
}

AbstractVM&	AbstractVM::operator=(AbstractVM const & rhs)
{
	if (this != &rhs)
	{
		_stack = rhs._stack;
	}
	return *this;
}

std::vector< std::vector< std::string > > &	AbstractVM::getProgramInstructions( void )
{
	return ( _programInstructions );
}

void	AbstractVM::fetchInstructions( std::istream& stream, bool isFromFile )
{
	std::vector< std::string >	tokens;
	std::string					input;

	while ( std::getline( stream, input ) )
	{
		boost::trim( input );
		if ( input[0] == ';' && input[1] == ';' && !isFromFile)
			break ;
		if ( input[0] == ';')
			continue ;
		boost::split( tokens, input, boost::is_any_of( " " ) );
		_programInstructions.push_back( tokens );
	}
}

void	AbstractVM::decodeInstructions( void )
{
	for (int i = 0; i < _programInstructions.size(); i++)
	{
		int opcode = _opcodes[_programInstructions[i][0]];
		if ( !opcode )
		{
			std::string err = "error line " + std::to_string( i ) + ": invalid instruction \033[1;31m" + _programInstructions[i][0] + "\n\033[0m";
			_errors.push_back( err );
			continue ;
		}
		if ( opcode == PUSH || opcode == ASSERT )
		{
			if ( !checkOperand( _programInstructions[i][1] )
			{
			}
			if ( _programInstructions[i].size() > 2 ) )
			{}
		}
	}
}

void	AbstractVM::push( std::string value )
{
	std::cout << "Value pushed: " << value << std::endl;
}

void	AbstractVM::aassert( std::string value ) const
{
	std::cout << "Value assert: " << value << std::endl;	
}

void	AbstractVM::pop( void )
{}

void	AbstractVM::dump( void )
{}

void	AbstractVM::add( void )
{}

void	AbstractVM::sub( void )
{}

void	AbstractVM::mul( void )
{}

void	AbstractVM::div( void )
{}

void	AbstractVM::mod( void )
{}

void	AbstractVM::print( void )
{}

void	AbstractVM::exit( void )
{}

void	AbstractVM::invalid( void )
{
   
	throw std::invalid_argument::invalid_argument("bad instruction");
}

IOperand const * AbstractVM::createInt8( std::string const & ) const
{
	return ( nullptr );
}

IOperand const * AbstractVM::createInt16( std::string const & ) const
{
	return ( nullptr );	
}

IOperand const * AbstractVM::createInt32( std::string const & ) const
{
	return ( nullptr );	
}

IOperand const * AbstractVM::createFloat( std::string const & ) const
{
	return ( nullptr );	
}

IOperand const * AbstractVM::createDouble( std::string const & ) const
{
	return ( nullptr );	
}
