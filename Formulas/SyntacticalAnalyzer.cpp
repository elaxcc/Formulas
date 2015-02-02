#include "stdafx.h"

#include "SyntacticalAnalyzer.h"

namespace Formula
{

	SyntacticalAnalyzer::SyntacticalAnalyzer()
	{
	}

	SyntacticalAnalyzer::~SyntacticalAnalyzer()
	{
	}

	void SyntacticalAnalyzer::analysis_expr(const boost::shared_ptr<std::list<Token>>& tokens)
	{
		//!fixme придумать как в случае ошибок в лексическом анализе
		// продолжить работу синтаксического анализатора
		if (errors_ptr_->is_empty())
		{
			TokensList::iterator it = tokens->begin();
			for (; it != tokens->end(); ++it)
			{
				if (it->type_ == Token::Type_DoubleDigit || it->type_ == Token::Type_IntegerDigit)
				{
					tmp_tokens_stack_.push(*it);
				}
				else if (it->type_ == Token::Type_Operator)
				{

				}
			}
		}
	}

} // Formulas
