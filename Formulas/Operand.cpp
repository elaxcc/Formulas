#include "stdafx.h"

#include "Operand.h"

namespace Formula
{

	Operand::Operand(double value)
		: value_(value_)
	{
	}

	double Operand::get_value()
	{
		return value_;
	}

} // Formulas