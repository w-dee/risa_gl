#ifndef SCATTER_HPP_
#define SCATTER_HPP_

/**
 * odd word, even word(32bit per pixelŽž)‚âfirst pixel, second
 * pixel(64bitŽž) ‚È‚Ç‚É•ªŠ„‚·‚é‚½‚ß‚Ìscatter
 */
namespace scatter
{
	namespace
	{
		// utility functions.
		template <typename mask_type>
		mask_type gen_lower_mask()
		{
			int num_of_bytes = sizeof(mask_type);
			mask_type result = 0xff;

			for (int count = 2; count <= (num_of_bytes + 1) / 2; ++count)
			{
				result = result << 8 | result;
			}

			return result;
 		};

		template <typename mask_type>
		mask_type gen_higher_mask()
		{
			mask_type lower_mask = gen_lower_mask<mask_type>();
			int num_of_bytes = sizeof(mask_type);
			int shift_of_bytes = num_of_bytes - (num_of_bytes + 1) / 2;
			return lower_mask << (shift_of_bytes * 8);
		};

		template <typename mask_type>
		mask_type gen_odd_mask()
		{
			int num_of_bytes = sizeof(mask_type);
			mask_type result = 0xff;
			
			for (int count = 2; count < num_of_bytes; count *= 2)
				result |= result << 16;

			return result;
		}

		template <typename mask_type>
		mask_type gen_even_mask()
		{
			return gen_odd_mask<mask_type>() << 8;
		}

		template <typename mask_type>
		mask_type gen_first_mask()
		{
			int num_of_bytes = sizeof(mask_type);
			mask_type result = 0xff;

			for (int count = 1; count < (num_of_bytes / 2); ++count)
				result |= result << 8;

			return result;
		}

		template <typename mask_type>
		mask_type gen_second_mask()
		{
			int num_of_bytes = sizeof(mask_type);
			return gen_first_mask<mask_type>() << (num_of_bytes * 4);
		}
	}

	template <typename value_t>
	struct through
	{
	public:
		typedef value_t result_type;
		typedef const value_t& input_type;

		result_type operator()(input_type source) const
		{
			return source;
		}
	};

	template <typename value_t>
	struct lower
	{
	public:
		typedef value_t result_type;
		typedef const value_t& input_type;
		typedef const value_t mask_type;

	private:
		mask_type mask;

	public:
		lower():
			mask(gen_lower_mask<value_t>())
		{}

		result_type operator()(input_type source) const
		{
			return (mask & source);
		}
	};

	template <typename value_t>
	struct higher
	{
	public:
		typedef value_t result_type;
		typedef const value_t& input_type;
		typedef const value_t mask_type;

	private:
		mask_type mask;
		const int shift_of_bytes;

	public:
		higher():
			mask(gen_higher_mask<value_t>()),
			shift_of_bytes(sizeof(value_t) - (sizeof(value_t) + 1) / 2)
		{}

		result_type operator()(input_type source) const
		{
			return (mask & source) >> (shift_of_bytes * 8);
		}
	};

	template <typename value_t>
	struct odd
	{
	public:
		typedef value_t result_type;
		typedef const value_t& input_type;
		typedef const value_t mask_type;

	private:
		mask_type mask;

	public:
		odd():
			mask(gen_odd_mask<value_t>())
		{}

		result_type operator()(input_type source) const
		{
			return source & mask;
		}
	};

	template <typename value_t>
	struct even
	{
	public:
		typedef value_t result_type;
		typedef const value_t& input_type;
		typedef const value_t mask_type;

	private:
		mask_type mask;

	public:
		even():
			mask(gen_even_mask<value_t>())
		{}

		result_type operator()(input_type source) const
		{
			return (source & mask) >> 8;
		}
	};

	template <typename value_t>
	struct first
	{
	public:
		typedef value_t result_type;
		typedef const value_t& input_type;
		typedef const value_t mask_type;

	private:
		mask_type mask;

	public:
		first():
			mask(gen_first_mask<value_t>())
		{}

		result_type operator()(input_type source) const
		{
			return source & mask;
		}
	};

	template <typename value_t>
	struct second
	{
	public:
		typedef value_t result_type;
		typedef const value_t& input_type;
		typedef const value_t mask_type;

	private:
		mask_type mask;

	public:
		second():
			mask(gen_second_mask<value_t>())
		{}

		result_type operator()(input_type source) const
		{
			return (source & mask) >> (sizeof(value_t) * 4);
		}
	};
}

#endif /* SCATTER_HPP_ */

