#ifndef RISA_ENDIAN_TRAITS_HPP_
#define RISA_ENDIAN_TRAITS_HPP_

#include <cassert>

namespace risa_gl
{
	template <typename base_type>
	class endian_traits
	{
		friend class endian_traits_test;

	public:
		typedef enum
		{
			big_endian,
			little_endian
		}  endian_type;

	private:
		const size_t base_type_size;

		static const int* get_endian_test_value()
		{
			static const int test_value = 0x00000001;
			return &test_value;
		}

		static endian_type get_current_endian()
		{
			if (*reinterpret_cast<const char*>(get_endian_test_value()) == 0)
				return big_endian;
			return little_endian;
		}

	public:
		endian_traits():
			base_type_size(sizeof(base_type))
		{}

		const size_t another_endian_offset(const size_t offset) const
		{
			assert(offset < base_type_size);

			return base_type_size - 1 - offset;
		}

		const size_t big_to_current_offset(const size_t big_offset) const
		{
			assert(big_offset < base_type_size);

			return 
				get_current_endian() == big_endian ?
				big_offset : another_endian_offset(big_offset);
		}

		const size_t little_to_current_offset(const size_t little_offset) const
		{
			assert(little_offset < base_type_size);
			
			return
				get_current_endian() == little_endian ?
				little_offset : another_endian_offset(little_offset);
		}
	};
}

#endif /* RISA_ENDIAN_TRAITS_HPP_ */
