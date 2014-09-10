#pragma once

#include "IElement.h"

namespace Formula
{

	class CodeAnalyzer
	{
	public:
		CodeAnalyzer();
		~CodeAnalyzer();

		void lexical_analysis(const std::string& text_code);
		void parser();

	private:
		typedef std::string Tocken;

		bool is_number(const std::string& tocken);
		bool is_spaces_only(const std::string& tocken);

		std::string remove_whitespace(const std::string& tocken);
		bool check_operator(const std::string& found_operator);

	private:
		std::vector<std::string> operators_list_;
		std::list<boost::shared_ptr<IElement>> elements_;
		std::list<Tocken> tockens_;
	};

} // Formula
