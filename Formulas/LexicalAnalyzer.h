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
		LexicalAnalyzer(const ErrorListPtr& errors_ptr);
		~LexicalAnalyzer();

		void line_analysis(const std::string& code, unsigned line_num);
		void analysis(const std::string& code);

		TokensListPtr get_tokens() { return tokens_ptr_; }
		ErrorListPtr get_errors() { return errors_ptr_; }

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
		TokensListPtr tokens_ptr_;
		ErrorListPtr errors_ptr_;
	};

} // Formula
