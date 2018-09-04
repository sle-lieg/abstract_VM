#include "AbstractVM.hpp"
#include "Operand.tpp"

#include <cmath>

void	AbstractVM::push(IOperand const * operand)
{
	_stack.insert(_stack.begin(), operand);
}

void	AbstractVM::aassert(IOperand const * operand) const
{
	if (_stack.empty())
	{
		delete operand;
		throw EmptyStackException("EmptyStackException caught from \033[1;33mASSERT\033[0m instruction: Stack is empty");
	}
	if (operand->toString() != _stack.front()->toString())
	{
		std::string err("AssertException caught: operand value \"\033[1;33m" + operand->toString() + "\033[0m\" != stack top value \"\033[1;33m" + (*_stack.begin())->toString() + "\033[0m\"");
		delete operand;
		throw AassertException(err);
	}
	delete operand;
}

void	AbstractVM::pop(void)
{
	if (_stack.empty())
		throw EmptyStackException("EmptyStackException caught from \033[1;33mPOP\033[0m instruction: Stack is empty");
	delete _stack[0];
	_stack.erase(_stack.begin());
}

void	AbstractVM::dump(void)
{
	for (auto e: _stack)
		std::cout << e->toString() << std::endl;
}

void	AbstractVM::add(void)
{
	if (_stack.size() < 2)
		throw EmptyStackException("EmptyStackException caught from \033[1;33mADD\033[0m instruction: need minimum 2 values in the stack");
	IOperand const * op_a = _stack[0];
	IOperand const * op_b = _stack[1];
	IOperand const * op_c {*op_b + *op_a};
	pop();
	pop();
	push(op_c);
}

void	AbstractVM::sub(void)
{
	if (_stack.size() < 2)
		throw EmptyStackException("EmptyStackException caught from \033[1;33mADD\033[0m instruction: need minimum 2 values in the stack");
	IOperand const * op_a = _stack[0];
	IOperand const * op_b = _stack[1];
	IOperand const * op_c {*op_b - *op_a};
	pop();
	pop();
	push(op_c);
}

void	AbstractVM::mul(void)
{
	if (_stack.size() < 2)
		throw EmptyStackException("EmptyStackException caught from \033[1;33mADD\033[0m instruction: need minimum 2 values in the stack");
	IOperand const * op_a = _stack[0];
	IOperand const * op_b = _stack[1];
	IOperand const * op_c {*op_b * *op_a};
	pop();
	pop();
	push(op_c);
}

void	AbstractVM::div(void)
{
	if (_stack.size() < 2)
		throw EmptyStackException("EmptyStackException caught from \033[1;33mADD\033[0m instruction: need minimum 2 values in the stack");
	IOperand const * op_a = _stack[0];
	IOperand const * op_b = _stack[1];
	IOperand const * op_c {*op_b / *op_a};
	pop();
	pop();
	push(op_c);
}

void	AbstractVM::mod(void)
{
	if (_stack.size() < 2)
		throw EmptyStackException("EmptyStackException caught from \033[1;33mADD\033[0m instruction: need minimum 2 values in the stack");
	IOperand const * op_a = _stack[0];
	IOperand const * op_b = _stack[1];
	IOperand const * op_c {*op_b % *op_a};
	pop();
	pop();
	push(op_c);
}

void	AbstractVM::print(void)
{
	if (_stack.empty())
		throw EmptyStackException("EmptyStackException caught from \033[1;33mPRINT\033[0m instruction: stack is empty");
	if (_stack[0]->getType() > INT8)
	{
		std::string err("AssertException caught from \033[1;33mPRINT\033[0m instruction: value need to be an INT8 integer");
		throw AassertException(err);
	}
	std::cout << static_cast<char>(stoi(_stack[0]->toString()));
}

void	AbstractVM::eexit(void)
{
	_exit = true;
}

void	AbstractVM::reverse(void)
{
	std::reverse(begin(_stack), end(_stack));
}

void	AbstractVM::get_max(void)
{
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

void	AbstractVM::get_min(void)
{
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

void	AbstractVM::clear(void)
{
	for_each(_stack.begin(), _stack.end(), [] (IOperand const * ptr) {
		delete ptr;
	});
	_stack.clear();
}

void	AbstractVM::power(void)
{
	if (_stack.size() < 2)
		throw EmptyStackException("EmptyStackException caught from \033[1;33mPOWER\033[0m instruction: need minimum 2 values in the stack");
	IOperand const * op_a = _stack[0];
	IOperand const * op_b = _stack[1];
	double v1 = stod(op_a->toString());
	double v2 = stod(op_b->toString());
	IOperand const * op_c = _factory.createOperand(std::max(op_a->getType(), op_b->getType()), std::to_string(pow(v2, v1)));
	pop();
	pop();
	push(op_c);
}

void	AbstractVM::logic_and(void)
{
	if (_stack.size() < 2)
		throw EmptyStackException("EmptyStackException caught from \033[1;33mLOGIC_AND\033[0m instruction: need minimum 2 values in the stack");
	IOperand const * op_a = _stack[0];
	IOperand const * op_b = _stack[1];
	IOperand const * op_c = *op_b & *op_a;
	pop();
	pop();
	push(op_c);
}

void	AbstractVM::logic_or(void)
{
	if (_stack.size() < 2)
		throw EmptyStackException("EmptyStackException caught from \033[1;33mLOGIC_OR\033[0m instruction: need minimum 2 values in the stack");
	IOperand const * op_a = _stack[0];
	IOperand const * op_b = _stack[1];
	IOperand const * op_c = *op_b | *op_a;
	pop();
	pop();
	push(op_c);
}

void	AbstractVM::logic_xor(void)
{
	if (_stack.size() < 2)
		throw EmptyStackException("EmptyStackException caught from \033[1;33mLOGIC_XOR\033[0m instruction: need minimum 2 values in the stack");
	IOperand const * op_a = _stack[0];
	IOperand const * op_b = _stack[1];
	IOperand const * op_c = *op_b ^ *op_a;
	pop();
	pop();
	push(op_c);
}

void	AbstractVM::invalid(void)
{
	throw std::invalid_argument::invalid_argument("bad instruction");
}