#include "stdafx.h"

#include "CodeAnalyzer.h"

#include "BinarOperators.h"
#include "Operand.h"
#include "UnarOperations.h"

namespace
{

	const std::string regex_separators = "\\W+";
	const std::string regex_is_number = "\\d*\\.?\\d*";
	const std::string regex_find_operator = "\\S+"; // �������� � ����������� ����� ���� ������ ���� � ��������� ���������� ��������!

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
		// ���� ����������� (�� ��������-�������� �������) ������, �� ��� ���������� ����� ������ ������
		unsigned pos = 0;
		boost::regex regex(regex_separators);
		boost::smatch match;
		std::string::const_iterator itbegin = text.begin();
		std::string::const_iterator itend = text.end();
		std::vector<unsigned> devision_points; // ������ ����� ������ ������
		while (boost::regex_search(itbegin, itend, match, regex))
		{
			pos += match.position();
			devision_points.push_back(pos); // ������� ������ �����������
			pos += match.str().length();
			devision_points.push_back(pos); // ������� ����� ��������

			itbegin = match[0].second;
		}
		if (devision_points.front() != 0) // ���� � ������ ����� ������ ��� ������ ������, ������� �
		{
			devision_points.insert(devision_points.begin(), 0);
		}
		if (devision_points.back() != text.length()) // ���� � ������ ����� ������ ��� ����� �������, ������� �
		{
			devision_points.insert(devision_points.begin(), text.length());
		}

		// ����� ����� �� ������� �� ������ ������
		for (unsigned i = 0; i < devision_points.size() - 1; i++)
		{
			lexem_.push_back(Lexem(text.substr(devision_points[i], devision_points[i + 1] - devision_points[i])));
		}

		// ����������� �������
		for (std::list<Lexem>::iterator iter = lexem_.begin(); iter != lexem_.end(); ++iter)
		{
			std::string tmp;
			if (is_number(*iter)) // ���� �����
			{

			}
			else if ((tmp = get_operator(*iter)) != std::string()) // ���� ��������
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
		// � ����� ����������� ������ ����� ���� ������ ���� �������� � ��������� ���������� ��������

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