#include "stdafx.h"

#include "Errors.h"

namespace Formula
{

	const std::string Error_list::c_err_invalid_operator_ = "Error A1: Unknown operator ";

	Error_list::Error_list()
	{
	}

	Error_list::~Error_list()
	{
		errors_.clear();
	}

	void Error_list::add(const std::string& err, unsigned line, unsigned column)
	{
		errors_.push_back(Error(err, line, column));
	}

	void Error_list::add_unknown_operator(std::string _operator, unsigned line, unsigned column)
	{
		errors_.push_back(Error(c_err_invalid_operator_ + _operator, line, column));
	}

} // Formulas
