#include "stdafx.h"

#include "LexicalAnalyzer.h"

#include "BinarOperators.h"
#include "Operand.h"
#include "UnarOperations.h"

namespace
{

	const std::string regex_separators = "\\s+|[\\W\\S]+|\\w+"; // регул€рное выражение дл€ поиска лексем
	const std::string regex_spaces = "\\s+"; // пробельные символы

	const std::string regex_is_double_digit = "\\d*\\.\\d*"; // число с плавающей точкой
	const std::string regex_is_integer_digit = "\\d+"; // целое число
	const std::string regex_is_operator = "[\\W|\\S]+"; // оператор, т.е. все символы, кроме буквенных, цифровых и пробельных

} // namespace

namespace Formula
{
	const std::vector<std::string> LexicalAnalyzer::operators_list_ = boost::assign::list_of("-")("+")("*")("/");

	LexicalAnalyzer::LexicalAnalyzer()
	{
		check_list_.insert(std::make_pair(Token::Type_IntegerDigit, boost::bind(&LexicalAnalyzer::is_integer_digit, this, _1)));
		check_list_.insert(std::make_pair(Token::Type_DoubleDigit, boost::bind(&LexicalAnalyzer::is_double_digit, this, _1)));
		check_list_.insert(std::make_pair(Token::Type_Operator, boost::bind(&LexicalAnalyzer::is_operator, this, _1)));
	}

	LexicalAnalyzer::~LexicalAnalyzer()
	{
		tokens_.clear();
	}

	void LexicalAnalyzer::lexical_line_analysis(const std::string& code, unsigned line_num)
	{
		// разбиваем входной код на лексемы и пробельные символы
		unsigned pos = 0;
		boost::regex regex(regex_separators);
		boost::smatch match;
		std::string::const_iterator itbegin = code.begin();
		std::string::const_iterator itend = code.end();
		std::vector<unsigned> division_points; // список точек биени€ текста
		while (boost::regex_search(itbegin, itend, match, regex))
		{
			std::string dummy_str = match.str();

			pos += match.position();
			division_points.push_back(pos); // позици€ начала разделител€
			pos += match.str().length();

			itbegin = match[0].second;
		}
		if (division_points.front() != 0) // если в списке точек биени€ нет начала строки, добавим еЄ
		{
			division_points.insert(division_points.begin(), 0);
		}
		if (division_points.back() != code.length()) // если в списке точек биени€ нет конца стороки, добавим еЄ
		{
			division_points.insert(division_points.end(), code.length());
		}

		// ƒелим текст на лексемы по точкам биени€, если лексема состоит только из пробельных
		// символов, то еЄ не включаем в список лексем.
		for (unsigned i = 0; i < division_points.size() - 1; i++)
		{
			// из лексем убираем все пробельные символы
			std::string lexem = code.substr(division_points[i], division_points[i + 1] - division_points[i]);
			if (!is_spaces_only(lexem))
			{
				tokens_.push_back(Token(lexem, line_num, division_points[i]));
			}
		}
	}

	void LexicalAnalyzer::lexical_analysis(const std::string& code)
	{
		// анализ проводим построчно, так как если встретим ошибку то
		// то еЄ нужно выделить по строке и позиции

		std::string line;
		unsigned current_line_num = 0;
		size_t current_text_code_pos = 0;
		size_t found_pos = 0;
		do
		{
			found_pos = code.find("\n", current_text_code_pos);
			if (found_pos != std::string::npos)
			{
				line = code.substr(current_text_code_pos, found_pos - current_text_code_pos);
				lexical_line_analysis(line, current_line_num);

				current_text_code_pos = found_pos + 1;
				current_line_num++;
			}
		} while (found_pos != std::string::npos);
		line = code.substr(current_text_code_pos, code.length() - current_text_code_pos);
		lexical_line_analysis(line, current_line_num);

		// определ€ем тип лексемы и указываем в токене
		std::list<Token>::iterator it = tokens_.begin();
		for (; it != tokens_.end(); it++)
		{
			// проходимс€ по списку возможных типов лексемы
			CheckList::const_iterator checker = check_list_.begin();
			for (; checker != check_list_.end(); ++checker)
			{
				if (checker->second(*it))
				{
					it->type_ = checker->first;
					break;
				}
			}

			// если тип лексемы осталс€ Token::Type_Unknown, значит нужно сформировать ошибку
			if (it->type_ == Token::Type_Unknown)
			{
				//!fixme add error
			}
		}
	}

	void LexicalAnalyzer::parser()
	{

	}

	bool LexicalAnalyzer::is_spaces_only(std::string& token)
	{
		boost::regex regex(regex_spaces);
		return boost::regex_match(token, regex);
	}

	bool LexicalAnalyzer::is_double_digit(Token& token)
	{
		boost::regex regex(regex_is_double_digit);
		return boost::regex_match(token.str_, regex);
	}

	bool LexicalAnalyzer::is_integer_digit(Token& token)
	{
		boost::regex regex(regex_is_integer_digit);
		return boost::regex_match(token.str_, regex);
	}

	bool LexicalAnalyzer::is_operator(Token& token)
	{
		boost::regex regex(regex_is_operator);
		return boost::regex_match(token.str_, regex) && is_exist_operator(token);

		if (boost::regex_match(token.str_, regex))
		{
			if (is_exist_operator(token))
			{
				return true;
			}
			errors_.add_unknown_operator(token.str_, token.line_, token.column_);
		}
		return false;
	}

	bool LexicalAnalyzer::is_exist_operator(Token& token)
	{
		for (unsigned i = 0; i < operators_list_.size(); ++i)
		{
			if (operators_list_[i] == token.str_)
			{
				return true;
			}
		}
		return false;
	}

} // Formula
