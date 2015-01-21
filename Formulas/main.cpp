#include "stdafx.h"

#include "CodeAnalyzer.h"

int _tmain(int argc, _TCHAR* argv[])
{
	std::string str = " -- - 098hn +== \nk+j\n673 jk12e3;";
	std::string str1 = "546.";
	std::string str2 = "  +";

	int a = 1;
	int b = 2;
	int k = a+++b;

	Formula::CodeAnalyzer analyzer;

	analyzer.lexical_analysis(str);
	
	return 0; 
}

