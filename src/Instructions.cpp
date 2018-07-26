#include "AbstractVM.hpp"
#include "Operand.tpp"

void	AbstractVM::push( IOperand const * operand )
{
	// std::cout << "Value pushed: " << operand << std::endl;
	_stack.insert(_stack.begin(), operand);
}

void	AbstractVM::aassert( IOperand const * operand ) const
{
	// std::cout << "Value assert: " << operand << std::endl;
	if (operand->toString() != _stack.front()->toString())
	{
		std::string err("AssertException caught: operand value \"\033[1;33m" + operand->toString() + "\033[0m\" != stack top value \"\033[1;33m" + (*_stack.begin())->toString() + "\033[0m\"");
		throw AassertException(err);
	}
}

void	AbstractVM::pop( void )
{
	// std::cout << "POP" << std::endl;
	if (_stack.size())
		_stack.erase(_stack.begin());
	else
		throw EmptyStackException("EmptyStackException caught from \033[1;33mPOP\033[0m instruction: Stack is empty");
}

void	AbstractVM::dump( void )
{
	// std::cout << "DUMP" << std::endl;
	for (auto e: _stack)
		std::cout << e->toString() << std::endl;
}

void	AbstractVM::add( void )
{
	// std::cout << "ADD" << std::endl;
	if (_stack.size() < 2)
		throw EmptyStackException("EmptyStackException caught from \033[1;33mADD\033[0m instruction: need minimum 2 values in the stack");
	IOperand const * op_a = _stack[0];
	IOperand const * op_b = _stack[1];
	pop();
	pop();
	push(*op_a + *op_b);
	delete op_a;
	delete op_b;
}

void	AbstractVM::sub( void )
{
	// std::cout << "SUB" << std::endl;
	if (_stack.size() < 2)
		throw EmptyStackException("EmptyStackException caught from \033[1;33mADD\033[0m instruction: need minimum 2 values in the stack");
	IOperand const * op_a = _stack[0];
	IOperand const * op_b = _stack[1];
	pop();
	pop();
	push(*op_a - *op_b);
	delete op_a;
	delete op_b;
}

void	AbstractVM::mul( void )
{
	// std::cout << "MUL" << std::endl;
	if (_stack.size() < 2)
		throw EmptyStackException("EmptyStackException caught from \033[1;33mADD\033[0m instruction: need minimum 2 values in the stack");
	IOperand const * op_a = _stack[0];
	IOperand const * op_b = _stack[1];
	pop();
	pop();
	push(*op_a * *op_b);
	delete op_a;
	delete op_b;
}

void	AbstractVM::div( void )
{
	// std::cout << "DIV" << std::endl;
	if (_stack.size() < 2)
		throw EmptyStackException("EmptyStackException caught from \033[1;33mADD\033[0m instruction: need minimum 2 values in the stack");
	IOperand const * op_a = _stack[0];
	IOperand const * op_b = _stack[1];
	pop();
	pop();
	push(*op_a / *op_b);
	delete op_a;
	delete op_b;
}

void	AbstractVM::mod( void )
{
	// std::cout << "MOD" << std::endl;
	if (_stack.size() < 2)
		throw EmptyStackException("EmptyStackException caught from \033[1;33mADD\033[0m instruction: need minimum 2 values in the stack");
	IOperand const * op_a = _stack[0];
	IOperand const * op_b = _stack[1];
	pop();
	pop();
	push(*op_a % *op_b);
	delete op_a;
	delete op_b;
}

void	AbstractVM::print( void )
{
	// std::cout << "PRINT" << std::endl;
	if (_stack.size() == 0)
		throw EmptyStackException("EmptyStackException caught from \033[1;33mPRINT\033[0m instruction: stack is empty");
	if (_stack[0]->getType() > INT8)
	{
		std::string err("AssertException caught from \033[1;33mPRINT\033[0m instruction: value need to an INT8 integer");
		throw AassertException(err);
	}
	std::string c = _stack[0]->toString();
	std::cout << char(c) << std::endl;
}

void	AbstractVM::eexit( void )
{
	std::cout << "EXIT" << std::endl;
}

void	AbstractVM::invalid( void )
{
	throw std::invalid_argument::invalid_argument("bad instruction");
}