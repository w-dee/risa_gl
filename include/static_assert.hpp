#ifndef RISA_STATIC_ASSERT_HPP_
#define RISA_STATIC_ASSERT_HPP_

namespace risa_gl
{
	template <bool expression> struct static_assert_failure;
	template <> struct static_assert_failure<true> {};

	template <bool expression> struct static_assert :
		public static_assert_failure<expression> {};
}

#define RISA_STATIC_ASSERT(x) risa_gl::static_assert<x>()

#endif /* RISA_STATIC_ASSERT_HPP_ */
