#include "stdafx.h"

#include "CodeAnalyzer.h"

int _tmain(int argc, _TCHAR* argv[])
{
	std::string str = "-- - 098hn +==";
	std::string str1 = "546.";
	std::string str2 = "  +";

	Formula::CodeAnalyzer analyzer;

	analyzer.parse(str);
	bool is_number = analyzer.is_number(str1);
	std::string op1 = analyzer.get_operator(str2);
	bool op1_valid = analyzer.check_operator(op1);
	
	return 0; 
}

