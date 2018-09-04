#ifndef OPERANDFACTORY_HPP
# define OPERANDFACTORY_HPP

#include <iostream>
#include <climits>

enum	eOperandType {
	INT8, INT16, INT32, FLOAT, DOUBLE
};

class IOperand;
class OperandFactory
{
	public:
		OperandFactory(void);
		~OperandFactory(void);
		IOperand const * createOperand(eOperandType type, std::string const & value) const;

	private:
		typedef IOperand const *(OperandFactory::*createFunc)(std::string const & value) const;
		createFunc	_createFunc[5];

		IOperand const * createInt8(std::string const & value) const;
		IOperand const * createInt16(std::string const & value) const;
		IOperand const * createInt32(std::string const & value) const;
		IOperand const * createFloat(std::string const & value) const;
		IOperand const * createDouble(std::string const & value) const;

		OperandFactory(OperandFactory const &);
		OperandFactory&	operator=(OperandFactory const &);
};

#endif
