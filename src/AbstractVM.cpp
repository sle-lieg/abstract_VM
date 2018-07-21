#include "AbstractVM.hpp"
// #include "Operand.tpp"
 
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
	},
	_optype{
		{"int8", INT8},
		{"int16", INT16},
		{"int32", INT32},
		{"float", FLOAT},
		{"double", DOUBLE}
	}
{
	_instructions[0] = &AbstractVM::invalid;
	_instructions[1] = &AbstractVM::pop;
	_instructions[2] = &AbstractVM::dump;
	_instructions[3] = &AbstractVM::add;
	_instructions[4] = &AbstractVM::sub;
	_instructions[5] = &AbstractVM::mul;
	_instructions[6] = &AbstractVM::div;
	_instructions[7] = &AbstractVM::mod;
	_instructions[8] = &AbstractVM::print;
	_instructions[9] = &AbstractVM::eexit;
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
	std::regex					comments("[ \t]*;.*$");

	while ( std::getline( stream, input ) )
	{
		boost::trim( input );
		if ( input[0] == ';' && input[1] == ';' && !isFromFile)
			break ;
		input = std::regex_replace(input, comments, "");
		if ( input.empty() )
		{
			_programInstructions.push_back( std::vector< std::string >() );
			continue ;
		}
		boost::split( tokens, input, boost::is_any_of( " " ), boost::algorithm::token_compress_on );
		_programInstructions.push_back( tokens );
	}
}

void	AbstractVM::decodeInstructions( void )
{
	std::string err;

	std::cout << _programInstructions.size() << std::endl;
	for ( size_t i = 0; i < _programInstructions.size(); i++ )
	{
		std::cout << "i=" << i << std::endl;
		err = "";

		if (_programInstructions[i].size() == 0)
			continue ;
		int opcode = _opcodes[_programInstructions[i][0]];
		if ( !opcode )
		{
			std::string err = "error line " + std::to_string( i+1 ) + ": invalid instruction \"\033[1;31m" + _programInstructions[i][0] + "\033[0m\"";
			_errors.push_back( err );
			continue ;
		}
		if ( _programInstructions[i][0] == "push" || _programInstructions[i][0] == "assert" )
		{
			std::regex	reg("^(((int8|int16|int32)\\([0-9]+\\))|(float|double)\\([0-9]+\\.[0-9]*\\))$");

			if (_programInstructions[i][1].empty())
				err = "error line " + std::to_string( i+1 ) + ": missing operand";
			else if (!std::regex_match(_programInstructions[i][1], reg))
				err = "error line " + std::to_string( i+1 ) + ": invalid operand \"\033[1;31m" + _programInstructions[i][1] + "\033[0m\"";
			if (err.size())
				_errors.push_back( err );
		}
		try {
			executeInstruction(_programInstructions[i]);
		} catch (std::runtime_error const & e) {
			err = "error line " + std::to_string( i+1 ) + ": " + e.what();
			_errors.push_back( err );
		}
		catch (std::logic_error const & e) {
			err = "error line " + std::to_string( i+1 ) + ": " + e.what();
			_errors.push_back( err );
		}
	}
	if (!_errors.empty())
		throw LexicalException(_errors);
}

void	AbstractVM::executeInstruction( std::vector< std::string > const & instruct)
{
	std::vector< std::string >	parsedOperand;
	IOperand const * operand = nullptr;
	int opcode = _opcodes[instruct[0]];

	if (opcode == 1 || opcode == 2)
	{
		boost::split( parsedOperand, instruct[1], boost::is_any_of( "()" ));
		operand = _factory.createOperand(_optype[parsedOperand[0]], parsedOperand[1]);
		if (_errors.empty())
			opcode == 1 ? push(operand) : aassert(operand);
	}
	else
		if (_errors.empty())
			(this->*_instructions[opcode])();
}

void	AbstractVM::_printErrors( void )
{
	for (std::vector< std::string >::iterator it = _errors.begin(); it != _errors.end(); it++)
		std::cout << *it;
}

void	AbstractVM::push( IOperand const * value )
{
	std::cout << "Value pushed: " << value << std::endl;
}

void	AbstractVM::aassert( IOperand const * value ) const
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

void	AbstractVM::eexit( void )
{}

void	AbstractVM::invalid( void )
{
	throw std::invalid_argument::invalid_argument("bad instruction");
}
