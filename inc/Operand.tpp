#ifndef OPERAND_TPP
# define OPERAND_TPP

#include "IOperand.hpp"

template<typename T>
class Operand : public IOperand
{
	public:

		Operand( eOperandType type, int precision, T value ) :
			_type(type), _precision(precision), _value(value), _str_value(std::to_string(value))
		{}

		~Operand( void ) {}

		Operand(Operand<T> const & rhs) { *this = rhs; }

		Operand<T>&	operator=(Operand<T> const & rhs)
		{
			if (this != rhs)
			{
				_type = rhs.getType();
				_precision = rhs.getPrecision();
				_value = std::stod(rhs.toString());
			}
			return *this;
		}

		int				getPrecision( void ) const { return _precision; }
		eOperandType	getType( void ) const { return _type; }

		IOperand const * operator+( IOperand const & rhs ) const
		{
			IOperand const * new_op;

			new_op = _factory.createOperand(std::max(_type, rhs.getType()), std::to_string(_value + std::stod(rhs.toString())));
			return new_op;
		}

		IOperand const * operator-( IOperand const & rhs ) const
		{
			IOperand const * new_op;

			new_op = _factory.createOperand(std::max(_type, rhs.getType()), std::to_string(_value - std::stod(rhs.toString())));
			return new_op;
		}

		IOperand const * operator*( IOperand const & rhs ) const
		{
			IOperand const * new_op;

			new_op = _factory.createOperand(std::max(_type, rhs.getType()), std::to_string(_value * std::stod(rhs.toString())));
			return new_op;
		}

		IOperand const * operator/( IOperand const & rhs ) const
		{
			IOperand const * new_op;

			if (rhs.toString() == "0")
				throw std::logic_error("division by zero");
			new_op = _factory.createOperand(std::max(_type, rhs.getType()), std::to_string(_value / std::stod(rhs.toString())));
			return new_op;
		}

		IOperand const * operator%( IOperand const & rhs ) const
		{
			IOperand const * new_op;

			if (rhs.toString() == "0")
				throw std::logic_error("division by zero");
			new_op = _factory.createOperand(std::max(_type, rhs.getType()), std::to_string(static_cast<int>(_value) % std::stoi(rhs.toString())));
			return new_op;
		}

		std::string const & toString( void ) const
		{
			return _str_value;
		}

	private:
		OperandFactory	_factory;

		eOperandType	_type;
		int				_precision;
		T				_value;
		std::string		_str_value;

		Operand( void )
		{}
};

#endif
