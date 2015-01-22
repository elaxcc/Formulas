#pragma once

namespace Formula
{

	class Token
	{
	public:
		enum Type
		{
			Type_Unknown,
			Type_DoubleDigit,
			Type_IntegerDigit,
			Type_Operator
		};
		
		std::string str_;
		unsigned line_;
		unsigned column_;
		Type type_;


		Token(const std::string& str, unsigned line, unsigned column)
			: str_(str)
			, line_(line)
			, column_(column)
		{
		}

		Token(const Token& token)
			: str_(token.str_)
			, line_(token.line_)
			, column_(token.column_)
		{
		}
	};

}
