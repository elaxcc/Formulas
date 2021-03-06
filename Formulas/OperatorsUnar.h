#pragma once

#include "IOperator.h"

namespace Formula
{

	class IOperatorUnar : public IOperator
	{
	public:
		IOperatorUnar(const boost::shared_ptr<IElement>& first)
			: first_(first)
		{
		}

	protected:
	public: // IElement
		virtual double get_value() = 0;

	public: // IOperator
		virtual int prior() = 0;

	protected:
		boost::shared_ptr<IElement> first_;
	};

	class OperatorUnarMinus : public IOperatorUnar
	{
	public:
		OperatorUnarMinus(const boost::shared_ptr<IElement>& first)
			: IOperatorUnar(first)
		{
		}

	public: // IElement
		virtual double get_value()
		{
			return -(first_->get_value());
		}

	public: // IOperator
		virtual int get_prior() { return 2; }
	};

} // Formula
