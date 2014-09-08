#pragma once

#include "IElement.h"

namespace Formula
{

	class Operand : public IElement
	{
	public:
		Operand(double value);

	public: // IElement
		virtual double get_value();

	private:
		double value_;
	};

} // Formula
