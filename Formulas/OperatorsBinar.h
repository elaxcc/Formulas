#pragma once

#include "IOperator.h"

namespace Formula
{

	class OperatorBinar : public IOperator
	{
	public:
		OperatorBinar(const boost::shared_ptr<IElement>& first, const boost::shared_ptr<IElement>& second);

	public: // IElement
		virtual double get_value() { return 0; };

	public: // IOperator
		virtual int prior() { return 0; };

	protected:
		boost::shared_ptr<IElement> first_;
		boost::shared_ptr<IElement> second_;
	};

	class OperatorBinarMinus : public OperatorBinar
	{
	public:
		OperatorBinarMinus(const boost::shared_ptr<IElement>& first, const boost::shared_ptr<IElement>& second)
			: OperatorBinar(first, second)
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

	class OperatorBinarPlus : public OperatorBinar
	{
	public:
		OperatorBinarPlus(const boost::shared_ptr<IElement>& first, const boost::shared_ptr<IElement>& second)
			: OperatorBinar(first, second)
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

	class OperatorBinarMultiplication : public OperatorBinar
	{
	public:
		OperatorBinarMultiplication(const boost::shared_ptr<IElement>& first, const boost::shared_ptr<IElement>& second)
			: OperatorBinar(first, second)
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

	class OperatorBinarDivision : public OperatorBinar
	{
	public:
		OperatorBinarDivision(const boost::shared_ptr<IElement>& first, const boost::shared_ptr<IElement>& second)
			: OperatorBinar(first, second)
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

	class OperatorBinarFactory
	{
	public:
		OperatorBinarFactory();
		~OperatorBinarFactory();

		boost::shared_ptr<IElement> Create(const std::string& _operator,  boost::shared_ptr<IElement>& first,
			const boost::shared_ptr<IElement>& second);
	};

} // Formula
