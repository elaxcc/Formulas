#include "stdafx.h"

#include "CodeAnalyzer.h"

namespace Formula
{

	CodeAnalyzer::CodeAnalyzer()
	{
		errors_ptr_ = boost::make_shared<ErrorList>();
		lexixal_analyzer_.set_error_list(errors_ptr_);
		syntactical_analyzer_.set_error_list(errors_ptr_);
	}

	CodeAnalyzer::~CodeAnalyzer()
	{
	}

	void CodeAnalyzer::analysis(const std::string& code)
	{
		lexixal_analyzer_.analysis(code);
		syntactical_analyzer_.analysis_expr(lexixal_analyzer_.get_tokens());
	}

} // Formula
