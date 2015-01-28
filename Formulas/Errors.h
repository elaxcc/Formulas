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

	class ErrorList
	{
	public:
		static const std::string c_err_invalid_operator_;

	public:
		ErrorList();
		~ErrorList();

		bool is_empty() { return errors_.empty(); }

		void add(const std::string& err, unsigned line, unsigned column);
		void add_unknown_operator(std::string _operator, unsigned line, unsigned column);

	private:
		std::list<Error> errors_;
	};
	typedef boost::shared_ptr<ErrorList> ErrorListPtr;

} // Formula
