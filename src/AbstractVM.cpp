#include "AbstractVM.hpp"
#include "IOperand.hpp"
 
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

AbstractVM::~AbstractVM(void)
{
	for_each(_stack.begin(), _stack.end(), [] (IOperand const * ptr) {
		delete ptr;
	});
	_stack.clear();
}

AbstractVM::AbstractVM(AbstractVM const & rhs)
{
	*this = rhs;
}

AbstractVM&	AbstractVM::operator=(AbstractVM const & rhs)
{
	if (this != &rhs)
		_stack = rhs._stack;
	return *this;
}

std::vector< std::vector< std::string > > &	AbstractVM::getProgramInstructions(void)
{
	return (_programInstructions);
}

void	AbstractVM::fetchInstructions(std::istream& stream, bool isFromFile)
{
	std::vector< std::string >	tokens;
	std::string					input;
	std::regex					comments("[ \t]*;.*$");

	while (std::getline(stream, input))
	{
		boost::trim(input);
		if (input[0] == ';' && input[1] == ';' && !isFromFile)
			break ;
		input = std::regex_replace(input, comments, "");
		boost::split(tokens, input, boost::is_any_of(" "), boost::algorithm::token_compress_on);
		_programInstructions.push_back(tokens);
	}
}

bool	AbstractVM::isValid()
{
	return (_errors.empty());
}

void	AbstractVM::lexer(void)
{
	std::string err;

	for (size_t i = 0; i < _programInstructions.size(); i++)
	{
		err.clear();

		// skip deleted comments
		if (_programInstructions[i][0].size() == 0)
			continue ;

		// check if instruction is valid
		int opcode = _opcodes[_programInstructions[i][0]];
		if (!opcode)
		{
			std::string err = "error line " + std::to_string(i+1) + ": invalid instruction \"\033[1;31m" + _programInstructions[i][0] + "\033[0m\"";
			_errors.push_back(err);
			continue ;
		}
		else
			_tokens.push_back(_programInstructions[i][0]);

		// check if `push` and `assert` have only one and valid argument
		if (_programInstructions[i][0] == "push" || _programInstructions[i][0] == "assert")
		{
			std::regex	reg("^(((int(8|16|32))\\(-?[0-9]+\\))|(float|double)\\(-?[0-9]+\\.[0-9]*\\))$");

			// no argument
			if (_programInstructions[i][1].empty())
				err = "error line " + std::to_string(i+1) + ": missing operand";
			// invalid syntax argument
			else if (!std::regex_match(_programInstructions[i][1], reg))
				err = "error line " + std::to_string(i+1) + ": invalid operand \"\033[1;31m" + _programInstructions[i][1] + "\033[0m\"";
			// too many arguments
			else if (_programInstructions[i].size() > 2)
				err = "error line " + std::to_string(i+1) + ": instruction \"\033[1;33m" + _programInstructions[i][0] + "\033[0m\" takes only one parameter";

			if (!err.empty())
				_errors.push_back(err);	
			else
				_tokens.push_back(_programInstructions[i][1]);
		}
		else if (_programInstructions[i].size() > 1)
		{
			err = "error line " + std::to_string(i+1) + ": instruction \"\033[1;33m" + _programInstructions[i][0] + "\033[0m\" takes no parameters";
			_errors.push_back(err);
		}
		if (_programInstructions[i][0] == "exit")
			_exit = true;
	}
	if (_exit == false)
		_errors.push_back("error: instruction \"\033[1;33mEXIT\033[0m\" missing in the program");
	if (!_errors.empty())
		throw LexicalException(_errors);
}

void	AbstractVM::parser()
{
	std::vector< std::string >	parsedOperand;
	std::regex	reg("^(((int(8|16|32))\\(-?[0-9]+\\))|(float|double)\\(-?[0-9]+\\.[0-9]*\\))$");

	for (auto it = _tokens.begin(); it != _tokens.end(); it++)
	{
		int opcode = _opcodes[*it];

		if (opcode == _opcodes["push"] || opcode == _opcodes["assert"])
		{
			it++;
			boost::split(parsedOperand, *it, boost::is_any_of("()"));
			IOperand const * operand = _factory.createOperand(_optype[parsedOperand[0]], parsedOperand[1]);
			opcode == _opcodes["push"] ? push(operand) : aassert(operand);
		}
		else
			(this->*_instructions[opcode])();
	}
}

void	AbstractVM::_printErrors(void)
{
	for (std::vector< std::string >::iterator it = _errors.begin(); it != _errors.end(); it++)
		std::cout << *it;
}
