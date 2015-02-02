#include "stdafx.h"

#include "OperatorsBinar.h"

namespace Formula
{
	OperatorBinar::OperatorBinar(const boost::shared_ptr<IElement>& first, const boost::shared_ptr<IElement>& second)
		: first_(first)
		, second_(second)
	{
	}

	OperatorBinarFactory::OperatorBinarFactory()
	{
	}

	OperatorBinarFactory::~OperatorBinarFactory()
	{
	}

	boost::shared_ptr<IElement> OperatorBinarFactory::Create(const std::string& _operator, boost::shared_ptr<IElement>& first,
		const boost::shared_ptr<IElement>& second)
	{
		boost::shared_ptr<IElement> bin_operator;

		if (_operator == "+")
		{
			bin_operator = boost::make_shared<OperatorBinarPlus>(first, second);
		}
		else if (_operator == "-")
		{
			bin_operator = boost::make_shared<OperatorBinarMinus>(first, second);
		}
		else if (_operator == "*")
		{
			bin_operator = boost::make_shared<OperatorBinarMultiplication>(first, second);
		}
		else if (_operator == "/")
		{
			bin_operator = boost::make_shared<OperatorBinarDivision>(first, second);
		}
		return bin_operator;
	}

} // Formulas
