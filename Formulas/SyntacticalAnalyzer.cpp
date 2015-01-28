#include "stdafx.h"

#include "SyntacticalAnalyzer.h"

namespace Formula
{

	SyntacticalAnalyzer::SyntacticalAnalyzer(const ErrorListPtr& errors_ptr)
		: errors_ptr_(errors_ptr)
	{
	}

	SyntacticalAnalyzer::~SyntacticalAnalyzer()
	{
	}

	void SyntacticalAnalyzer::analysis(const boost::shared_ptr<std::list<Token>>& tokens)
	{
		//!fixme придумать как в случае ошибок в лексическом анализе
		// продолжить работу синтаксического анализатора
		if (errors_ptr_->is_empty())
		{
			TokensList::iterator it = tokens->begin();
			for (; it != tokens->end(); ++it)
			{
				switch (it->type_)
				{
					case Token::Type_IntegerDigit :
					case Token::Type_DoubleDigit :
					{
						process_digit(*it);
						break;
					}
					case Token::Type_Operator :
					{
						process_operator(*it);
						break;
					}
					case Token::Type_Unknown :
					{
						//!fixme не должен сюда попадать
						break;
					}
				}
			}
		}
	}

	void process_digit(const Token& token)
	{

	}

	void process_operator(const Token& token)
	{

	}

} // Formulas
