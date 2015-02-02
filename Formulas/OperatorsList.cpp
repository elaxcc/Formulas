#include "stdafx.h"

#include "OperatorsList.h"

namespace Formula
{

	const std::map<std::string, int> c_operator_list = boost::assign::map_list_of("+", 6)("-", 6)("*", 5)("/", 5);

} // Formula
