#ifndef PIXEL_TRAITS_HPP_
#define PIXEL_TRAITS_HPP_


/**
 * traiter
 */
namespace traits
{
	/**
	 * ピクセルの差異を埋めるトリーター
	 */
	template <typename pixel_t, int factor_position = pixel_t::alpha_position, typename unit_t = unsigned int>
	struct pixel_traits
	{
		typedef unit_t unit_type;

		enum {
			factor_shift = 8 * factor_position,
			number_of_pixels_per_unit = sizeof(unit_type) / sizeof(pixel_t)
		};

		const unit_type mask;

		pixel_traits():
			mask((0xff << factor_shift))
		{}

		unit_type factor_extract(unit_type src)
		{
			return (src & mask) >> factor_shift;
		}
	};

#ifdef x64
	template <typename pixel_t, int factor_position = pixel_t::alpha_position>
	struct pixel_traits<pixel_t, factor_position, unsigned long long>
	{
		typedef unsigned long long unit_type;

		enum {
			factor_shift = 8 * factor_position,
			number_of_pixels_per_unit = sizeof(unit_type) / sizeof(pixel_t)
		};

		const unit_type mask;

		pixel_traits():
			mask((0xff000000ffULL << factor_shift))
		{}

		unit_type factor_extract(unit_type src)
		{
			return (src & mask) >> factor_shift;
		}
	};
#endif

#ifdef SSE2
	template <typename pixel_t, int factor_position = pixel_t::alpha_position>
	struct pixel_traits<pixel_t, factor_position, _m128>
	{
		typedef _m128 unit_type;

		enum {
			factor_shift = 8 * factor_position,
			number_of_pixels_per_unit = sizeof(unit_type) / sizeof(pixel_t)
		};

		const unit_type mask;

		unit_type gen_mask_pattern()
		{
			unit_type result = 0xff << factor_shift;
			for (int offset = 1; offset < number_of_pixels_per_unit; offset <<= 1)
				result |= result << (sizeof(pixel_t) * 8 * offset);
		}

		pixel_traits():
			mask(gen_mask_pattern())
		{}

		unit_type factor_extract(unit_type src)
		{
			return (src & mask) >> factor_shift;
		}
	};
#endif
}

#endif /* PIXEL_TRAITS_HPP_ */
