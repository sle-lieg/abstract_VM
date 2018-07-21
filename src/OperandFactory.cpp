#include "OperandFactory.hpp"
#include <boost/lexical_cast.hpp>
#include "Operand.tpp"

OperandFactory::OperandFactory( void )
{
	_createFunc[0] = &OperandFactory::createInt8;
	_createFunc[1] = &OperandFactory::createInt16;
	_createFunc[2] = &OperandFactory::createInt32;
	_createFunc[3] = &OperandFactory::createFloat;
	_createFunc[4] = &OperandFactory::createDouble;
}

OperandFactory::~OperandFactory( void ) {}

IOperand const * OperandFactory::createOperand(eOperandType type, std::string const & value) const
{
	IOperand const * operand = (this->*_createFunc[type])(value);
	return (operand);
}

IOperand const * OperandFactory::createInt8( std::string const & value) const
{
	int n = 0;

	try {
		n = boost::lexical_cast<int>(value);
		if (n < CHAR_MIN || n > CHAR_MAX)
			throw boost::bad_lexical_cast();
	} catch(boost::bad_lexical_cast const & e) {
		if (value[0] == '-')
			throw std::underflow_error("value " + value + " is lower than INT8_MIN " + std::to_string(INT8_MIN));
		else
			throw std::overflow_error("value " + value + " is lower than INT8_MAX " + std::to_string(INT8_MAX));
	}
	IOperand * op = new Operand<int8_t>(INT8, INT8, static_cast<int8_t>(n));

	return (op);
}

IOperand const * OperandFactory::createInt16( std::string const & value) const
{
	int16_t n = 0;

	try {
		n = boost::lexical_cast<int16_t>(value);
	} catch(boost::bad_lexical_cast const & e) {
		if (value[0] == '-')
			throw std::underflow_error("value " + value + " is lower than INT16_MIN " + std::to_string(INT16_MIN));
		else
			throw std::overflow_error("value " + value + " is lower than INT16_MAX " + std::to_string(INT16_MAX));
	}
	IOperand * op = new Operand<int16_t>(INT16, INT16, n);

	return (op);
}

IOperand const * OperandFactory::createInt32( std::string const & value) const
{
	int32_t n = 0;

	try {
		n = boost::lexical_cast<int32_t>(value);
	} catch(boost::bad_lexical_cast const & e) {
		if (value[0] == '-')
			throw std::underflow_error("value " + value + " is lower than INT32_MIN " + std::to_string(INT32_MIN));
		else
			throw std::overflow_error("value " + value + " is lower than INT32_MAX " + std::to_string(INT32_MAX));
	}
	IOperand * op = new Operand<int32_t>(INT32, INT32, n);

	return (op);
}

IOperand const * OperandFactory::createFloat( std::string const & value) const
{
	float n = 0;

	try {
		n = boost::lexical_cast<float>(value);
	} catch(boost::bad_lexical_cast const & e) {
		if (value[0] == '-')
			throw std::underflow_error("value " + value + " is lower than FLOAT_MIN " + std::to_string(FLT_MIN));
		else
			throw std::overflow_error("value " + value + " is lower than FLOAT_MAX " + std::to_string(FLT_MAX));
	}
	IOperand * op = new Operand<float>(FLOAT, FLOAT, n);

	return (op);
}

IOperand const * OperandFactory::createDouble( std::string const & value) const
{
	double n = 0;

	try {
		n = boost::lexical_cast<double>(value);
	} catch(boost::bad_lexical_cast const & e) {
		if (value[0] == '-')
			throw std::underflow_error("value " + value + " is lower than DOUBLE_MIN " + std::to_string(DBL_MIN));
		else
			throw std::overflow_error("value " + value + " is lower than DOUBLE_MAX " + std::to_string(DBL_MAX));
	}
	IOperand * op = new Operand<double>(DOUBLE, DOUBLE, n);

	return (op);
}