#include "stdafx.h"

#include "Errors.h"

namespace Formula
{

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

}
