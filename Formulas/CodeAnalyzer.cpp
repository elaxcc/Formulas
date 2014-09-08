#include "stdafx.h"

#include "CodeAnalyzer.h"

#include "BinarOperators.h"
#include "Operand.h"
#include "UnarOperations.h"

namespace
{

	const std::string regex_separators = "\\W+";
	const std::string regex_is_number = "\\d*\\.?\\d*";
	const std::string regex_find_operator = "\\S+"; // оператор в разделителе может быть только один и несколько пробельных символов!

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
		lexem_.clear();
	}

	double CodeAnalyzer::calculate()
	{
		return 0.0;
	}

	void CodeAnalyzer::parse(const std::string& text)
	{
		// ищем разделители (не буквенно-цифровые символы) лексем, по ним запоминаем точки биения текста
		unsigned pos = 0;
		boost::regex regex(regex_separators);
		boost::smatch match;
		std::string::const_iterator itbegin = text.begin();
		std::string::const_iterator itend = text.end();
		std::vector<unsigned> devision_points; // список точек биения текста
		while (boost::regex_search(itbegin, itend, match, regex))
		{
			pos += match.position();
			devision_points.push_back(pos); // позиция начала разделителя
			pos += match.str().length();
			devision_points.push_back(pos); // позиция конца делителя

			itbegin = match[0].second;
		}
		if (devision_points.front() != 0) // если в списке точек биения нет начала строки, добавим её
		{
			devision_points.insert(devision_points.begin(), 0);
		}
		if (devision_points.back() != text.length()) // если в списке точек биения нет конца стороки, добавим её
		{
			devision_points.insert(devision_points.begin(), text.length());
		}

		// делим текст на лексемы по точкам биения
		for (unsigned i = 0; i < devision_points.size() - 1; i++)
		{
			lexem_.push_back(Lexem(text.substr(devision_points[i], devision_points[i + 1] - devision_points[i])));
		}

		// анализируем лексемы
		for (std::list<Lexem>::iterator iter = lexem_.begin(); iter != lexem_.end(); ++iter)
		{
			std::string tmp;
			if (is_number(*iter)) // если число
			{

			}
			else if ((tmp = get_operator(*iter)) != std::string()) // если оператор
			{

			}
		}
	}

	bool CodeAnalyzer::is_number(const std::string& lexem)
	{
		boost::regex regex(regex_is_number);
		return boost::regex_match(lexem, regex);
	}

	std::string CodeAnalyzer::get_operator(const std::string& lexem)
	{
		// в одном разделителе лексем может быть только один оператор и несколько пробельных символов

		boost::regex regex(regex_find_operator);
		boost::smatch match;
		std::string::const_iterator itbegin = lexem.begin();
		std::string::const_iterator itend = lexem.end();
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