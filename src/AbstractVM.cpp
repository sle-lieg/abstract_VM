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
		{"push", 10},
		{"assert", 11}
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

	for ( size_t i = 0; i < _programInstructions.size(); i++ )
	{
		// std::cout << "i=" << i << std::endl;
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
			executeInstruction(_programInstructions[i]);
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
	if (!_errors.empty())
		throw LexicalException(_errors);
}

void	AbstractVM::executeInstruction( std::vector< std::string > const & instruct)
{
	std::vector< std::string >	parsedOperand;
	IOperand const * operand = nullptr;
	int opcode = _opcodes[instruct[0]];

	if (opcode == _opcodes["push"] || opcode == _opcodes["assert"])
	{
		boost::split( parsedOperand, instruct[1], boost::is_any_of( "()" ));
		operand = _factory.createOperand(_optype[parsedOperand[0]], parsedOperand[1]);
		if (_errors.empty())
			opcode == _opcodes["push"] ? push(operand) : aassert(operand);
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

// void	AbstractVM::push( IOperand const * operand )
// {
// 	// std::cout << "Value pushed: " << operand << std::endl;
// 	_stack.insert(_stack.begin(), operand);
// }

// void	AbstractVM::aassert( IOperand const * operand ) const
// {
// 	// std::cout << "Value assert: " << operand << std::endl;
// 	if (operand->toString() != _stack.front()->toString())
// 	{
// 		std::string err("AssertException caught: operand value \"\033[1;33m" + operand->toString() + "\033[0m\" != stack top value \"\033[1;33m" + (*_stack.begin())->toString() + "\033[0m\"");
// 		throw AassertException(err);
// 	}
// }

// void	AbstractVM::pop( void )
// {
// 	// std::cout << "POP" << std::endl;
// 	if (_stack.size())
// 		_stack.erase(_stack.begin());
// 	else
// 		throw EmptyStackException("EmptyStackException caught from \033[1;33mPOP\033[0m instruction: Stack is empty");
// }

// void	AbstractVM::dump( void )
// {
// 	// std::cout << "DUMP" << std::endl;
// 	for (auto e: _stack)
// 		std::cout << e->toString() << std::endl;
// }

// void	AbstractVM::add( void )
// {
// 	// std::cout << "ADD" << std::endl;
// 	if (_stack.size() < 2)
// 		throw EmptyStackException("EmptyStackException caught from \033[1;33mADD\033[0m instruction: need minimum 2 values in the stack");
// 	IOperand const * op_a = _stack[0];
// 	IOperand const * op_b = _stack[1];
// 	pop();
// 	pop();
// 	push(*op_a + *op_b);
// 	delete op_a;
// 	delete op_b;
// }

// void	AbstractVM::sub( void )
// {
// 	// std::cout << "SUB" << std::endl;
// 	if (_stack.size() < 2)
// 		throw EmptyStackException("EmptyStackException caught from \033[1;33mADD\033[0m instruction: need minimum 2 values in the stack");
// 	IOperand const * op_a = _stack[0];
// 	IOperand const * op_b = _stack[1];
// 	pop();
// 	pop();
// 	push(*op_a - *op_b);
// 	delete op_a;
// 	delete op_b;
// }

// void	AbstractVM::mul( void )
// {
// 	// std::cout << "MUL" << std::endl;
// 	if (_stack.size() < 2)
// 		throw EmptyStackException("EmptyStackException caught from \033[1;33mADD\033[0m instruction: need minimum 2 values in the stack");
// 	IOperand const * op_a = _stack[0];
// 	IOperand const * op_b = _stack[1];
// 	pop();
// 	pop();
// 	push(*op_a * *op_b);
// 	delete op_a;
// 	delete op_b;
// }

// void	AbstractVM::div( void )
// {
// 	// std::cout << "DIV" << std::endl;
// 	if (_stack.size() < 2)
// 		throw EmptyStackException("EmptyStackException caught from \033[1;33mADD\033[0m instruction: need minimum 2 values in the stack");
// 	IOperand const * op_a = _stack[0];
// 	IOperand const * op_b = _stack[1];
// 	pop();
// 	pop();
// 	push(*op_a / *op_b);
// 	delete op_a;
// 	delete op_b;
// }

// void	AbstractVM::mod( void )
// {
// 	// std::cout << "MOD" << std::endl;
// 	if (_stack.size() < 2)
// 		throw EmptyStackException("EmptyStackException caught from \033[1;33mADD\033[0m instruction: need minimum 2 values in the stack");
// 	IOperand const * op_a = _stack[0];
// 	IOperand const * op_b = _stack[1];
// 	pop();
// 	pop();
// 	push(*op_a % *op_b);
// 	delete op_a;
// 	delete op_b;
// }

// void	AbstractVM::print( void )
// {
// 	std::cout << "PRINT" << std::endl;
// }

// void	AbstractVM::eexit( void )
// {
// 	std::cout << "EXIT" << std::endl;
// }

// void	AbstractVM::invalid( void )
// {
// 	throw std::invalid_argument::invalid_argument("bad instruction");
// }
