#include "stdafx.h"

#include "Errors.h"

namespace Formula
{

	const std::string ErrorList::c_err_invalid_operator_ = "Error A1: Unknown operator ";

	ErrorList::ErrorList()
	{
	}

	ErrorList::~ErrorList()
	{
		errors_.clear();
	}

	void ErrorList::add(const std::string& err, unsigned line, unsigned column)
	{
		errors_.push_back(Error(err, line, column));
	}

	void ErrorList::add_unknown_operator(std::string _operator, unsigned line, unsigned column)
	{
		errors_.push_back(Error(c_err_invalid_operator_ + _operator, line, column));
	}

} // Formulas
