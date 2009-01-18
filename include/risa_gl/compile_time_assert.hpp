#ifndef RISA_COMPILE_TIME_ASSERT_HPP_
#define RISA_COMPILE_TIME_ASSERT_HPP_

namespace risa_gl
{
	template <bool expression> struct compile_time_assert_failure;
	template <> struct compile_time_assert_failure<true> {};

	template <bool expression> struct compile_time_assert :
		public compile_time_assert_failure<expression> {};
}

#define RISA_COMPILE_TIME_ASSERT(x) risa_gl::compile_time_assert<x>()

#endif /* RISA_COMPILE_TIME_ASSERT_HPP_ */
