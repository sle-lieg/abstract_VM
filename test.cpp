#include <iostream>
#include <sstream>
#include <boost/lexical_cast.hpp>

int main()
{
	int f1 = 10;
	float f2 = 2;
	float f3 = f1 ^ f2;
	std::cout << f1 << " / " << f2 << " = " << f3 << std::endl;
//   double f = 3.14159;

//   std::cout.unsetf ( std::ios::floatfield );                // floatfield not set
//   std::cout.precision(5);
//   std::cout << f << '\n';
//   std::cout.precision(7);
//   std::cout << f << '\n';
//   std::cout.setf( std::ios::fixed, std:: ios::floatfield ); // floatfield set to fixed
//   std::cout << f << '\n';
  return 0;
}