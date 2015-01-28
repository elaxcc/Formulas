#pragma once

#include "Token.h"
#include "Errors.h"

namespace Formula
{

	class SyntacticalAnalyzer
	{
	public:
		SyntacticalAnalyzer(const ErrorListPtr& errors_ptr);
		~SyntacticalAnalyzer();

		void analysis(const boost::shared_ptr<std::list<Token>>& tokens);

	private:
		void process_digit(const Token& token);
		void process_operator(const Token& token);

	private:
		std::stack<Token> tmp_tokens_stack_;
		ErrorListPtr errors_ptr_;
	};

} // Formula
