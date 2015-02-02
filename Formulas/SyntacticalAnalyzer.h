#pragma once

#include "Token.h"
#include "Errors.h"
#include "Tree.h"

namespace Formula
{

	class SyntacticalAnalyzer
	{
	public:
		SyntacticalAnalyzer();
		~SyntacticalAnalyzer();

		void set_error_list(const ErrorListPtr& errors_ptr) { errors_ptr_ = errors_ptr; }

		void analysis_expr(const boost::shared_ptr<std::list<Token>>& tokens);

	private:
		std::stack<Token> tmp_tokens_stack_;
		TreeNode parse_tree_;

		ErrorListPtr errors_ptr_;
	};

} // Formula
