#ifndef RISA_POWER_HPP_
#define RISA_POWER_HPP_

namespace risa_gl
{
	namespace math
	{
		template <typename ValueType, int exponent>
		class power
		{
			typedef ValueType real_type;

		public:
			static real_type value(const real_type base)
			{
				return base * power<real_type, exponent - 1>::value(base);
			}
		};

		template <typename ValueType>
		class power<ValueType, 0>
		{
			typedef ValueType real_type;
		public:
			static real_type value(const real_type base)
			{
				return 1.f;
			}
		};
	}
}

#endif /* RISA_POWER_HPP_ */
