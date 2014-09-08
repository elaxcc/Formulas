#pragma once

#include "IElement.h"

namespace Formula
{

	class IOperator : public IElement
	{
	public: // IElement
		virtual double get_value() = 0;

	public:
		virtual int prior() = 0;
	};
}
