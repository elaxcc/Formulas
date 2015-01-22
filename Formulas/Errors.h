#pragma once

namespace Formula
{

	struct Error
	{
		std::string text_;
		unsigned line_;
		unsigned column_;

		Error(const std::string& text, unsigned line, unsigned column)
			: text_(text)
			, line_(line)
			, column_(column)
		{
		}
	};

	class Error_list
	{
	public:
		Error_list();
		~Error_list();

	void add(const std::string& err, unsigned line, unsigned column);

	private:
		std::list<Error> errors_;
	};
}
