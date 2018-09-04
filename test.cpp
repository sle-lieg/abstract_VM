// example on extraction
#include <iostream>     // std::cin, std::cout, std::hex
#include <fstream>

void	testing(std::istream & ost)
{
	// ost >> std::noskipws;
	// std::string tok;
	char c;
	while (ost.get(c))
	{
		// ost >> tok;
		if (c == '\n')
			std::cout << "POUET";
		std::cout << c;
	}
}

int main () {

	// std::ifstream ifs;
	// ifs.exceptions(std::ifstream::badbit);
	// ifs.open("progs/pdf.avm");
	// testing(ifs);
	// ifs.close();
	testing(std::cin);
//   int n;

//   std::cout << "Enter a number: ";
//   std::cin >> n;
//   std::cout << "You have entered: " << n << '\n';

//   std::cout << "Enter a hexadecimal number: ";
//   std::cin >> std::hex >> n;         // manipulator
//   std::cout << "Its decimal equivalent is: " << n << '\n';

  return 0;
}