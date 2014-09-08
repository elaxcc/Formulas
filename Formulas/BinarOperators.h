#pragma once

#include "IOperator.h"

namespace Formula
{
	class BinarOperation : public IOperator
	{
	public:
		BinarOperation(const boost::shared_ptr<IElement>& first, const boost::shared_ptr<IElement>& second);

	public: // IElement
		virtual double get_value() { return 0; };

	public: // IOperator
		virtual int prior() { return 0; };

	protected:
		boost::shared_ptr<IElement> first_;
		boost::shared_ptr<IElement> second_;
	};

	class BinarOperatorMinus : public BinarOperation
	{
	public:
		BinarOperatorMinus(const boost::shared_ptr<IElement>& first, const boost::shared_ptr<IElement>& second)
			: BinarOperation(first, second)
		{
		}

	public: // IElement
		virtual double get_value()
		{
			return first_->get_value() - second_->get_value();
		}

	public: // BinarOperation
		virtual int get_prior() { return 2; }
	};

	class BinarOperatorPlus : public BinarOperation
	{
	public:
		BinarOperatorPlus(const boost::shared_ptr<IElement>& first, const boost::shared_ptr<IElement>& second)
			: BinarOperation(first, second)
		{
		}

	public: // IElement
		virtual double get_value()
		{
			return first_->get_value() + second_->get_value();
		}

	public: // BinarOperation
		virtual int get_prior() { return 2; }
	};

	class BinarOperatorMultiplication : public BinarOperation
	{
	public:
		BinarOperatorMultiplication(const boost::shared_ptr<IElement>& first, const boost::shared_ptr<IElement>& second)
			: BinarOperation(first, second)
		{
		}

	public: // IElement
		virtual double get_value()
		{
			return first_->get_value() * second_->get_value();
		}

	public: // BinarOperation
		virtual int get_prior() { return 1; }
	};

	class BinarOperatorDivision : public BinarOperation
	{
	public:
		BinarOperatorDivision(const boost::shared_ptr<IElement>& first, const boost::shared_ptr<IElement>& second)
			: BinarOperation(first, second)
		{
		}

	public: // IElement
		virtual double get_value()
		{
			//!fixme добавить проверку "деление на ноль"

			return first_->get_value() / second_->get_value();
		}

	public: // BinarOperation
		virtual int get_prior() { return 1; }
	};

	class BinarOperationFactory
	{
	public:
		BinarOperationFactory();
		~BinarOperationFactory();

		boost::shared_ptr<IElement> Create(const std::string& _operator,  boost::shared_ptr<IElement>& first,
			const boost::shared_ptr<IElement>& second);
	};
}
