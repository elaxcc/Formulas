#pragma once

#include "LexicalAnalyzer.h"
#include "SyntacticalAnalyzer.h"
#include "Errors.h"

namespace Formula
{

	class CodeAnalyzer
	{
	public:
		CodeAnalyzer();
		~CodeAnalyzer();

		void analysis(const std::string& code);

	private:
		LexicalAnalyzer lexixal_analyzer_;
		SyntacticalAnalyzer syntactical_analyzer_;
		ErrorListPtr errors_ptr_;
	};

} // Formula
