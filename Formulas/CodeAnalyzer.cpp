#include "stdafx.h"

#include "CodeAnalyzer.h"

namespace Formula
{

	CodeAnalyzer::CodeAnalyzer()
		: lexixal_analyzer_(errors_ptr_)
		, syntactical_analyzer_(errors_ptr_)
	{
		errors_ptr_ = boost::make_shared<ErrorList>();
	}

	CodeAnalyzer::~CodeAnalyzer()
	{
	}

	void CodeAnalyzer::analysis(const std::string& code)
	{
		lexixal_analyzer_.analysis(code);
		syntactical_analyzer_.analysis(lexixal_analyzer_.get_tokens());
	}

} // Formula
