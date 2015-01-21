#pragma once

namespace Formula
{

	struct error
	{
		std::string text_;
		unsigned line_;
		unsigned column_;

		error(const std::string& text, unsigned line, unsigned column)
			: text_(text)
			, line_(line)
			, column_(column)
		{
		}
	};

	class error_list
	{
	public:
		error_list();
		~error_list();

	void add(const std::string& err, unsigned line, unsigned column);

	private:
		std::list<error> errors_;
	};
}
