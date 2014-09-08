#pragma once

#include "IElement.h"

namespace Formula
{

	class CodeAnalyzer
	{
	public:
		CodeAnalyzer();
		~CodeAnalyzer();

		double calculate();
		void parse(const std::string& text);

	private:
		typedef std::string Lexem;

	public:
		bool is_number(const std::string& lexem);

		std::string get_operator(const std::string& lexem);
		bool check_operator(const std::string& found_operator);

	private:
		std::vector<std::string> operators_list_;
		std::list<boost::shared_ptr<IElement>> elements_;
		std::list<Lexem> lexem_;
	};

} // Formula
