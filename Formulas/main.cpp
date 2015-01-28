#include "stdafx.h"

#include "LexicalAnalyzer.h"

int _tmain(int argc, _TCHAR* argv[])
{
	std::string str = /*
		" -- - 098hn +== \n"
		"k+j\n"
		"673 jk12e3;";*/
		"1+2*3";
	std::string str1 = "546.";
	std::string str2 = "  +";

	Formula::LexicalAnalyzer analyzer;

	analyzer.lexical_analysis(str);
	
	return 0; 
}

