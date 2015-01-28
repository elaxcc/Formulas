#pragma once

#include "IElement.h"
#include "Errors.h"
#include "Token.h"

namespace Formula
{
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
		bool is_spaces_only(std::string& token);

		bool is_double_digit(Token& token);
		bool is_integer_digit(Token& token);
		bool is_operator(Token& token);
		bool is_exist_operator(Token& token);

	private:
		typedef boost::function<bool(Token&)> CheckFunction;
		typedef std::map<Token::Type, CheckFunction> CheckList;

	private:
		static const std::vector<std::string> operators_list_;
		CheckList check_list_;

	private:
		std::list<Token> tokens_;
		Error_list errors_;
	};

} // Formula
