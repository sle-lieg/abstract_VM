#include "AbstractVM.hpp"
#include "Operand.tpp"

#include <cmath>

void	AbstractVM::push( IOperand const * operand )
{
	// std::cout << "Value pushed: " << operand << std::endl;
	_stack.insert(_stack.begin(), operand);
}

void	AbstractVM::aassert( IOperand const * operand ) const
{
	// std::cout << "Value assert: " << operand << std::endl;
	if (_stack.empty())
		throw EmptyStackException("EmptyStackException caught from \033[1;33mASSERT\033[0m instruction: Stack is empty");
	if (operand->toString() != _stack.front()->toString())
	{
		std::string err("AssertException caught: operand value \"\033[1;33m" + operand->toString() + "\033[0m\" != stack top value \"\033[1;33m" + (*_stack.begin())->toString() + "\033[0m\"");
		throw AassertException(err);
	}
}

void	AbstractVM::pop( void )
{
	// std::cout << "POP" << std::endl;
	if (_stack.empty())
		throw EmptyStackException("EmptyStackException caught from \033[1;33mPOP\033[0m instruction: Stack is empty");
	_stack.erase(_stack.begin());
}

void	AbstractVM::dump( void )
{
	std::cout << "DUMP" << std::endl;
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
	push(*op_b - *op_a);
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
	push(*op_b / *op_a);
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
	push(*op_b % *op_a);
	delete op_a;
	delete op_b;
}

void	AbstractVM::print( void )
{
	// std::cout << "PRINT" << std::endl;
	if (_stack.empty())
		throw EmptyStackException("EmptyStackException caught from \033[1;33mPRINT\033[0m instruction: stack is empty");
	if (_stack[0]->getType() > INT8)
	{
		std::string err("AssertException caught from \033[1;33mPRINT\033[0m instruction: value need to be an INT8 integer");
		throw AassertException(err);
	}
	std::cout << char(static_cast<char>(stoi(_stack[0]->toString())));
}

void	AbstractVM::eexit( void )
{
	// std::cout << "EXIT" << std::endl;
	_exit = true;
}

void	AbstractVM::reverse( void )
{
	std::reverse(begin(_stack), end(_stack));
}

void	AbstractVM::get_max( void )
{
	std::cout << "MAX" << std::endl;
	if (_stack.size() < 1)
		throw EmptyStackException("EmptyStackException caught from \033[1;33mMAX\033[0m instruction: stack is empty");
	std::vector<IOperand const *>::iterator max_elem(begin(_stack));
	for (auto op = begin(_stack)+1; op != end(_stack); op++)
	{
		if (stod((*op)->toString()) > stod((*max_elem)->toString()))
			max_elem = op;
	}
	_stack.insert(begin(_stack), *max_elem);
	_stack.erase(++max_elem);
}

void	AbstractVM::get_min( void )
{
	std::cout << "MIN" << std::endl;
	if (_stack.size() < 1)
		throw EmptyStackException("EmptyStackException caught from \033[1;33mMIN\033[0m instruction: stack is empty");
	std::vector<IOperand const *>::iterator min_elem(begin(_stack));
	for (auto op = begin(_stack)+1; op != end(_stack); op++)
	{
		if (stod((*op)->toString()) < stod((*min_elem)->toString()))
			min_elem = op;
	}
	_stack.insert(begin(_stack), *min_elem);
	_stack.erase(++min_elem);
}

void	AbstractVM::clear( void )
{
	std::cout << "CLEAR" << std::endl;
	_stack.clear();
}

void	AbstractVM::power( void )
{
	std::cout << "POWER" << std::endl;
	if (_stack.size() < 2)
		throw EmptyStackException("EmptyStackException caught from \033[1;33mPOWER\033[0m instruction: need minimum 2 values in the stack");
	IOperand const * op_a = _stack[0];
	IOperand const * op_b = _stack[1];
	pop();
	pop();
	double v1 = stod(op_a->toString());
	double v2 = stod(op_b->toString());

	push(_factory.createOperand(std::max(op_a->getType(), op_b->getType()), std::to_string(pow(v2, v1))));

	delete op_a;
	delete op_b;
}

void	AbstractVM::logic_and( void )
{
	std::cout << "LOGIC_AND" << std::endl;
	if (_stack.size() < 2)
		throw EmptyStackException("EmptyStackException caught from \033[1;33mLOGIC_AND\033[0m instruction: need minimum 2 values in the stack");
	IOperand const * op_a = _stack[0];
	IOperand const * op_b = _stack[1];
	pop();
	pop();

	push(*op_b & *op_a);

	delete op_a;
	delete op_b;
}

void	AbstractVM::logic_or( void )
{
	std::cout << "LOGIC_OR" << std::endl;
	if (_stack.size() < 2)
		throw EmptyStackException("EmptyStackException caught from \033[1;33mLOGIC_OR\033[0m instruction: need minimum 2 values in the stack");
	IOperand const * op_a = _stack[0];
	IOperand const * op_b = _stack[1];
	pop();
	pop();

	push(*op_b | *op_a);

	delete op_a;
	delete op_b;
}

void	AbstractVM::logic_xor( void )
{
	std::cout << "LOGIC_XOR" << std::endl;
	if (_stack.size() < 2)
		throw EmptyStackException("EmptyStackException caught from \033[1;33mLOGIC_XOR\033[0m instruction: need minimum 2 values in the stack");
	IOperand const * op_a = _stack[0];
	IOperand const * op_b = _stack[1];
	pop();
	pop();

	push(*op_b ^ *op_a);

	delete op_a;
	delete op_b;
}

void	AbstractVM::invalid( void )
{
	throw std::invalid_argument::invalid_argument("bad instruction");
}