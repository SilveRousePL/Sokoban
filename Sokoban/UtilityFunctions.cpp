#include "UtilityFunctions.hpp"

std::string UtilityFunctions::IntToString(int value)
{
	std::stringstream ss;
	ss << value;
	return ss.str();
}
