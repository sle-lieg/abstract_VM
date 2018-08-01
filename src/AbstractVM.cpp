#include "AbstractVM.hpp"
// #include "Operand.tpp"
 
AbstractVM::AbstractVM() :
	_opcodes{
		{"pop", 1},
		{"dump", 2},
		{"add", 3},
		{"sub", 4},
		{"mul", 5},
		{"div", 6},
		{"mod", 7},
		{"print", 8},
		{"exit", 9},

		{"reverse", 10},
		{"get_max", 11},
		{"get_min", 12},
		{"clear", 13},
		{"pow", 14},
		{"and", 15},
		{"or", 16},
		{"xor", 17},

		{"push", 18},
		{"assert", 19}
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
	_instructions[10] = &AbstractVM::reverse;
	_instructions[11] = &AbstractVM::get_max;
	_instructions[12] = &AbstractVM::get_min;
	_instructions[13] = &AbstractVM::clear;
	_instructions[14] = &AbstractVM::power;
	_instructions[15] = &AbstractVM::logic_and;
	_instructions[16] = &AbstractVM::logic_or;
	_instructions[17] = &AbstractVM::logic_xor;
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
		boost::split( tokens, input, boost::is_any_of( " " ), boost::algorithm::token_compress_on );
		_programInstructions.push_back( tokens );
	}
}

void	AbstractVM::lexer( void )
{
	std::string err;

	for ( size_t i = 0; i < _programInstructions.size(); i++ )
	{
		err = "";

		if (_programInstructions[i][0].size() == 0)
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
			std::regex	reg("^(((int(8|16|32))\\(-?[0-9]+\\))|(float|double)\\(-?[0-9]+\\.[0-9]*\\))$");

			if (_programInstructions[i][1].empty())
				err = "error line " + std::to_string( i+1 ) + ": missing operand";
			else if (!std::regex_match(_programInstructions[i][1], reg))
				err = "error line " + std::to_string( i+1 ) + ": invalid operand \"\033[1;31m" + _programInstructions[i][1] + "\033[0m\"";
			if (err.size())
				_errors.push_back( err );
		}
		else if (_programInstructions[i].size() > 1)
		{
			err = "error line " + std::to_string( i+1 ) + ": instruction \"\033[1;33m" + _programInstructions[i][0] + "\033[0m\" takes no parameters";
			_errors.push_back(err);
		}
		try {
			parser(_programInstructions[i]);
		} catch (std::runtime_error const & e) {
			err = "error line " + std::to_string( i+1 ) + ": " + e.what();
			_errors.push_back( err );
		} catch (std::logic_error const & e) {
			err = "error line " + std::to_string( i+1 ) + ": " + e.what();
			_errors.push_back( err );
		} catch (std::exception const & e) {
			err = "error line " + std::to_string( i+1 ) + ": " + e.what();
			_errors.push_back( err );
		}
	}
	if (_exit == false)
		_errors.push_back("error: instruction \"\033[1;33mEXIT\033[0m\" missing in the program");
	if (!_errors.empty())
		throw LexicalException(_errors);
}

void	AbstractVM::parser( std::vector< std::string > const & instruct)
{
	std::vector< std::string >	parsedOperand;
	IOperand const * operand = nullptr;
	int opcode = _opcodes[instruct[0]];
	std::regex	reg("^(((int(8|16|32))\\(-?[0-9]+\\))|(float|double)\\(-?[0-9]+\\.[0-9]*\\))$");

	if ((opcode == _opcodes["push"] || opcode == _opcodes["assert"]) && std::regex_match(instruct[1], reg))
	{
		boost::split( parsedOperand, instruct[1], boost::is_any_of( "()" ));
		operand = _factory.createOperand(_optype[parsedOperand[0]], parsedOperand[1]);
		if (_errors.empty() && !_exit)
			opcode == _opcodes["push"] ? push(operand) : aassert(operand);
	}
	else
		if ((_errors.empty() && !_exit) || opcode == _opcodes["exit"])
			(this->*_instructions[opcode])();
}

void	AbstractVM::_printErrors( void )
{
	for (std::vector< std::string >::iterator it = _errors.begin(); it != _errors.end(); it++)
		std::cout << *it;
}
