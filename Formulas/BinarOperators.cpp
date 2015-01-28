#include "stdafx.h"

#include "BinarOperators.h"

namespace Formula
{
	BinarOperation::BinarOperation(const boost::shared_ptr<IElement>& first, const boost::shared_ptr<IElement>& second)
		: first_(first)
		, second_(second)
	{
	}

	BinarOperationFactory::BinarOperationFactory()
	{
	}

	BinarOperationFactory::~BinarOperationFactory()
	{
	}

	boost::shared_ptr<IElement> BinarOperationFactory::Create(const std::string& _operator, boost::shared_ptr<IElement>& first,
		const boost::shared_ptr<IElement>& second)
	{
		boost::shared_ptr<IElement> bin_operator;

		if (_operator == "+")
		{
			bin_operator = boost::make_shared<BinarOperatorPlus>(first, second);
		}
		else if (_operator == "-")
		{
			bin_operator = boost::make_shared<BinarOperatorMinus>(first, second);
		}
		else if (_operator == "*")
		{
			bin_operator = boost::make_shared<BinarOperatorMultiplication>(first, second);
		}
		else if (_operator == "/")
		{
			bin_operator = boost::make_shared<BinarOperatorDivision>(first, second);
		}
		return bin_operator;
	}

} // Formulas
