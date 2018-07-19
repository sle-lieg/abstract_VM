#include <iostream>
#include <sstream>
#include <boost/lexical_cast.hpp>

int main()
{
	std::string s("2147483647");
	double d = 0;

	d = boost::lexical_cast<double>(s);
	std::cout << (int)d << std::endl;

	
	// int8_t int8;
	// int16_t int16;
	// int32_t int32;

	// try {
	// 	std::string s("5");
	// 	int8 = boost::lexical_cast<int8_t>(s);
	// 	std::cout << "OK " << std::endl;
	// 	s = "50";
	// 	int8 = boost::lexical_cast<int8_t>(s);
	// 	std::cout << "OK " << std::endl;
	// 	s = "260";
	// 	int8 = boost::lexical_cast<char>(s);
	// 	std::cout << "OK " << std::endl;
	// } catch(std::exception const & e) {
	// 	std::cout << "exception: ";
	// 	std::cout << e.what() << std::endl;
	// } catch(boost::bad_lexical_cast const & e) {
	// 	std::cout << "lexical_cast: ";
	// 	std::cout << e.what() << std::endl;
	// }
	return(0);
}