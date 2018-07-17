#ifndef OPERAND_HPP
# define OPERAND_HPP

#include "IOperand.hpp"

template<typename T>
class Operand : public IOperand
{
	public:
		Operand( void )
		{}

		~Operand( void )
		{}

		Operand(Operand< T > const & rhs)
		{}

		Operand< t >&	operator=(Operand< T > const & rhs)
		{}

		int getPrecision( void ) const
		{}

		eOperandType getType( void ) const
		{}

		IOperand const * operator+( IOperand const & rhs ) const
		{}

		IOperand const * operator-( IOperand const & rhs ) const
		{}

		IOperand const * operator*( IOperand const & rhs ) const
		{}

		IOperand const * operator/( IOperand const & rhs ) const
		{}

		IOperand const * operator%( IOperand const & rhs ) const
		{}

		std::string const & toString( void ) const
		{}

	private:

};

#endif
