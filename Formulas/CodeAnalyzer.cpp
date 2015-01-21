#include "stdafx.h"

#include "CodeAnalyzer.h"

#include "BinarOperators.h"
#include "Operand.h"
#include "UnarOperations.h"

namespace
{

	const std::string regex_separators = "\\s+|[\\W\\S]+|\\w+"; // ��� �� �������� � �� ��������� �������
	const std::string regex_is_number = "\\d*\\.?\\d*"; // ����� � ��������� ������
	const std::string regex_not_spaces = "\\S+"; // �� ���������� �������
	const std::string regex_spaces = "\\s+"; // ���������� �������

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
		// ��������� ������� ��� �� ������� � ���������� �������
		unsigned pos = 0;
		boost::regex regex(regex_separators);
		boost::smatch match;
		std::string::const_iterator itbegin = text_code.begin();
		std::string::const_iterator itend = text_code.end();
		std::vector<unsigned> division_points; // ������ ����� ������ ������
		while (boost::regex_search(itbegin, itend, match, regex))
		{
			std::string dummy_str = match.str();

			pos += match.position();
			division_points.push_back(pos); // ������� ������ �����������
			pos += match.str().length();

			itbegin = match[0].second;
		}
		if (division_points.front() != 0) // ���� � ������ ����� ������ ��� ������ ������, ������� �
		{
			division_points.insert(division_points.begin(), 0);
		}
		if (division_points.back() != text_code.length()) // ���� � ������ ����� ������ ��� ����� �������, ������� �
		{
			division_points.insert(division_points.end(), text_code.length());
		}

		// ����� ����� �� ������� �� ������ ������, ���� ������� ������� ������ �� ����������
		// ��������, �� � �� �������� � ������ ������.
		for (unsigned i = 0; i < division_points.size() - 1; i++)
		{
			// �� ������ ������� ��� ���������� �������
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
		//!fixme ������� ��������� � ��� ��� �������� ��������� ����������
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