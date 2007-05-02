#ifndef RISA_EXCEPTION_HPP_
#define RISA_EXCEPTION_HPP_

#include <stdexcept>

namespace risa_gl
{
	/**
	 * アラインメント例外
	 */
	class alignment_error : public std::runtime_error
	{
	public:
		alignment_error():
			std::runtime_error("alignment error")
		{}

		alignment_error(const std::string& reason):
			std::runtime_error(reason)
		{}

		virtual ~alignment_error() throw()
		{}

		virtual const char* what() const throw()
		{
			return std::runtime_error::what();
		}
	};

};
#endif /* RISA_EXCEPTION_HPP_ */
