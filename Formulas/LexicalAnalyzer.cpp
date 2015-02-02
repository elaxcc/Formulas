#include "stdafx.h"

#include "LexicalAnalyzer.h"

#include "Operand.h"
#include "OperatorsBinar.h"
#include "OperatorsList.h"
#include "OperatorsUnar.h"

namespace
{

	const std::string regex_separators = "\\s+|[\\W\\S]+|\\w+"; // регулярное выражение для поиска лексем
	const std::string regex_spaces = "\\s+"; // пробельные символы

	const std::string regex_is_double_digit = "\\d*\\.\\d*"; // число с плавающей точкой
	const std::string regex_is_integer_digit = "\\d+"; // целое число
	const std::string regex_is_operator = "[\\W|\\S]+"; // оператор, т.е. все символы, кроме буквенных, цифровых и пробельных

} // namespace

namespace Formula
{

	LexicalAnalyzer::LexicalAnalyzer()
	{
		check_list_.insert(std::make_pair(Token::Type_IntegerDigit, boost::bind(&LexicalAnalyzer::is_integer_digit, this, _1)));
		check_list_.insert(std::make_pair(Token::Type_DoubleDigit, boost::bind(&LexicalAnalyzer::is_double_digit, this, _1)));
		check_list_.insert(std::make_pair(Token::Type_Operator, boost::bind(&LexicalAnalyzer::is_operator, this, _1)));

		tokens_ptr_ = boost::make_shared<TokensList>();
	}

	LexicalAnalyzer::~LexicalAnalyzer()
	{
		tokens_ptr_->clear();
	}

	void LexicalAnalyzer::line_analysis(const std::string& code, unsigned line_num)
	{
		// разбиваем входной код на лексемы и пробельные символы
		unsigned pos = 0;
		boost::regex regex(regex_separators);
		boost::smatch match;
		std::string::const_iterator itbegin = code.begin();
		std::string::const_iterator itend = code.end();
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
		if (division_points.back() != code.length()) // если в списке точек биения нет конца стороки, добавим её
		{
			division_points.insert(division_points.end(), code.length());
		}

		// Делим текст на лексемы по точкам биения, если лексема состоит только из пробельных
		// символов, то её не включаем в список лексем.
		for (unsigned i = 0; i < division_points.size() - 1; i++)
		{
			std::string lexem = code.substr(division_points[i], division_points[i + 1] - division_points[i]);
			if (!is_spaces_only(lexem))
			{
				Token token(lexem, line_num, division_points[i]);

				// проходимся по списку возможных типов лексемы
				CheckList::const_iterator checker = check_list_.begin();
				for (; checker != check_list_.end(); ++checker)
				{
					if (checker->second(token))
					{
						token.type_ = checker->first;
						break;
					}
				}

				// если лексемой оказался токен состоящий из символов,
				// используемых операторами, то есть вероятность, что
				// в этой лексеме несколько операторов, проверим это
				if (token.type_ == Token::Type_Operator && !is_exist_operator(token))
				{
					while (!token.str_.empty())
					{
						// Попробуем разбить на несколько операторов.
						// Правило разбития: сначала ищим операторы максимальной длинны
						// в начале лексемы из существующих. Потом для остатка лексемы
						// повторяем эти действия. Итак пока строка не закончится либо пока
						// ни найдём несуществующий оператор.
						unsigned cur_pos_in_lexem = 0;
						std::string temp_str;
						OperatorsList::const_iterator op_it = c_operator_list.begin();
						for (; op_it != c_operator_list.end(); ++op_it)
						{
							if (token.str_.find(op_it->first) == 0) // нашли оператор и он вначеле
							{
								// длинна найдинного оператора больше найденного ранее
								if (temp_str.length() < op_it->first.length())
								{
									temp_str = op_it->first;
								}
							}
						}
						// если нашли оператор (temp_str - не пустая строка), то ложим текущий оператор
						// в список токенов, удаляем оператор из начала лексемы
						if (!temp_str.empty())
						{
							tokens_ptr_->push_back(Token(temp_str, token.line_,
								token.column_ + cur_pos_in_lexem, Token::Type_Operator));
							cur_pos_in_lexem = temp_str.length();

							token.str_ = token.str_.substr(temp_str.length());
						}
					}
				}
				else
				{
					if (token.type_ != Token::Type_Unknown)
					{
						tokens_ptr_->push_back(token);
					}
					else
					{
						//!fixme add error
					}
				}
			}
		}
	}

	void LexicalAnalyzer::analysis(const std::string& code)
	{
		// анализ проводим построчно, так как если встретим ошибку то
		// то её нужно выделить по строке и позиции

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
				line_analysis(line, current_line_num);

				current_text_code_pos = found_pos + 1;
				current_line_num++;
			}
		} while (found_pos != std::string::npos);
		line = code.substr(current_text_code_pos, code.length() - current_text_code_pos);
		line_analysis(line, current_line_num);
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
		return boost::regex_match(token.str_, regex);
	}

	bool LexicalAnalyzer::is_exist_operator(Token& token)
	{
		OperatorsList::const_iterator it = c_operator_list.begin();
		for (; it != c_operator_list.end(); ++it)
		{
			if (it->first == token.str_)
			{
				return true;
			}
		}
		return false;
	}

} // Formula
