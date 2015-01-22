#pragma once

#include "IElement.h"
#include "Errors.h"

namespace Formula
{
	class Token;
	class Error_list;

	class LexicalAnalyzer
	{
	public:
		LexicalAnalyzer();
		~LexicalAnalyzer();

		void lexical_line_analysis(const std::string& code, unsigned line_num);
		void lexical_analysis(const std::string& code);
		void parser();

	private:

		bool is_spaces_only(const std::string& token);

		bool is_double_digit(const Token& token);
		bool is_integer_digit(const Token& token);
		bool is_operator(const Token& token);


		std::string remove_whitespace(const std::string& token);
		bool check_operator(const std::string& found_operator);

	private:
		std::vector<std::string> operators_list_;
		std::list<Token> tokens_;
		Error_list errors_;
	};

} // Formula
