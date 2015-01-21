#include "stdafx.h"

#include "Errors.h"

namespace Formula
{

	error_list::error_list()
	{
	}

	error_list::~error_list()
	{
		errors_.clear();
	}

	void error_list::add(const std::string& err, unsigned line, unsigned column)
	{
		errors_.push_back(error(err, line, column));
	}

}
