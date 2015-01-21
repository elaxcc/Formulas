#include "stdafx.h"

#include "CodeAnalyzer.h"

#include "BinarOperators.h"
#include "Operand.h"
#include "UnarOperations.h"

namespace
{

	const std::string regex_separators = "\\s+|[\\W\\S]+|\\w+"; // все не цифровые и не буквенные символы
	const std::string regex_is_number = "\\d*\\.?\\d*"; // число с плавающей точкой
	const std::string regex_not_spaces = "\\S+"; // не пробельные символы
	const std::string regex_spaces = "\\s+"; // пробельные символы

} // namespace

namespace Formula
{

	CodeAnalyzer::CodeAnalyzer()
	{
		operators_list_ = boost::assign::list_of("-")("+")("*")("/");
	}

	CodeAnalyzer::~CodeAnalyzer()
	{
		operators_list_.clear();
		elements_.clear();
		tokens_.clear();
	}

	void CodeAnalyzer::lexical_analysis(const std::string& text_code)
	{
		// разбиваем входной код на лексемы и пробельные символы
		unsigned pos = 0;
		boost::regex regex(regex_separators);
		boost::smatch match;
		std::string::const_iterator itbegin = text_code.begin();
		std::string::const_iterator itend = text_code.end();
		std::vector<unsigned> division_points; // список точек биения текста
		while (boost::regex_search(itbegin, itend, match, regex))
		{
			std::string dummy_str = match.str();

			pos += match.position();
			division_points.push_back(pos); // позиция начала разделителя
			pos += match.str().length();

			itbegin = match[0].second;
		}
		if (division_points.front() != 0) // если в списке точек биения нет начала строки, добавим её
		{
			division_points.insert(division_points.begin(), 0);
		}
		if (division_points.back() != text_code.length()) // если в списке точек биения нет конца стороки, добавим её
		{
			division_points.insert(division_points.end(), text_code.length());
		}

		// Делим текст на лексемы по точкам биения, если лексема состоит только из пробельных
		// символов, то её не включаем в список лексем.
		for (unsigned i = 0; i < division_points.size() - 1; i++)
		{
			// из лексем убираем все пробельные символы
			std::string dirty_lexem = text_code.substr(division_points[i], division_points[i + 1] - division_points[i]);
			if (!is_spaces_only(dirty_lexem))
			{
				tokens_.push_back(dirty_lexem);
			}
		}
	}

	void CodeAnalyzer::parser()
	{

	}

	bool CodeAnalyzer::is_number(const std::string& token)
	{
		boost::regex regex(regex_is_number);
		return boost::regex_match(token, regex);
	}

	bool CodeAnalyzer::is_spaces_only(const std::string& token)
	{
		boost::regex regex(regex_spaces);
		return boost::regex_match(token, regex);
	}

	std::string CodeAnalyzer::remove_whitespace(const std::string& dirty_lexem)
	{
		boost::regex regex(regex_not_spaces);
		boost::smatch match;
		std::string::const_iterator itbegin = dirty_lexem.begin();
		std::string::const_iterator itend = dirty_lexem.end();
		std::vector<std::string> operators;
		while (boost::regex_search(itbegin, itend, match, regex))
		{
			operators.push_back(match.str());

			itbegin = match[0].second;
		}

		if (operators.size() == 1)
		{
			return operators[0];
		}
		//!fixme создать сообщение о том что попалось несколько операторов
		return std::string();
	}

	bool CodeAnalyzer::check_operator(const std::string& found_operator)
	{
		for (unsigned i = 0; i < operators_list_.size(); ++i)
		{
			if (operators_list_[i] == found_operator)
			{
				return true;
			}
		}
		return false;
	}

} // Formula