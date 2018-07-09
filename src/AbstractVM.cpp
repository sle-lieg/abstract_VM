#include "AbstractVM.hpp"

AbstractVM::AbstractVM() :
	_opcode{
		{"pop", 1},
		{"dump", 2},
		{"add", 3},
		{"sub", 4},
		{"mul", 5},
		{"div", 6},
		{"mod", 7},
		{"print", 8},
		{"exit", 9}
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

// // todo: remove
// static void printT( std::vector <std::string> & v )
// {
// 	for (size_t n = 0; n < v.size(); n++)
// 		std::cout << "\"" << v[ n ] << "\"\n";
// 	std::cout << std::endl;
// }

void	AbstractVM::fetchInstruction( std::istream& stream )
{
	std::vector<std::string> tokens;
	std::string input;

	while ( std::getline( stream, input ) )
	{
		boost::split( tokens, input, boost::is_any_of( " " ) );
		// std::cout << input << std::endl;
		// printT(tokens);
		if ( tokens[0] == "push" )
			push( tokens[1] );
		else if ( tokens[0] == "assert" )
			aassert( tokens[1] );
		else
		{
			int opcode = _opcode[tokens[0]];
			std::cout << "int= " << opcode << std::endl;
			(this->*_instructions[opcode])();
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
