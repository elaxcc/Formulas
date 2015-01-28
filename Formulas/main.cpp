#include "stdafx.h"

#include "CodeAnalyzer.h"

int _tmain(int argc, _TCHAR* argv[])
{
	std::string str = /*
		" -- - 098hn +== \n"
		"k+j\n"
		"673 jk12e3;";*/
		"1+2*3";
	std::string str1 = "546.";
	std::string str2 = "  +";

	Formula::CodeAnalyzer analyzer;

	analyzer.analysis(str);
	
	return 0; 
}

