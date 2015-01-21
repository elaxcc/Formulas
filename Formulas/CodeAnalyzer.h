#pragma once

#include "IElement.h"

namespace Formula
{
	class Token;

	class CodeAnalyzer
	{
	public:
		CodeAnalyzer();
		~CodeAnalyzer();

		void lexical_text_line_analysis(const std::string& text_code, unsigned line_num);
		void lexical_analysis(const std::string& text_code);
		void parser();

	private:

		bool is_number(const std::string& token);
		bool is_spaces_only(const std::string& token);

		std::string remove_whitespace(const std::string& token);
		bool check_operator(const std::string& found_operator);

	private:
		std::vector<std::string> operators_list_;
		std::list<boost::shared_ptr<IElement>> elements_;
		std::list<Token> tokens_;
	};

} // Formula
