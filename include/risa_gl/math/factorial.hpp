#ifndef RISA_FACTORIAL_HPP_
#define RISA_FACTORIAL_HPP_

namespace risa_gl
{
	namespace math
	{
		template <int depth>
		struct factorial
		{
			enum
			{
				value = depth * factorial<depth - 1>::value
			};
		};

		template <>
		struct factorial<1>
		{
			enum
			{
				value = 1
			};
		};
	}
}
#endif /* RISA_FACTORIAL_HPP_ */
