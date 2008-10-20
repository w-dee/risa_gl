#ifndef TYPES_HPP_
#define TYPES_HPP_

namespace types
{
	template <typename pixel_t, typename environment_t>
	struct environment_context
	{
		typedef environment_t::bit_pattern_type bit_pattern_type;
		typedef environment_t::basic_input_type basic_input_type;
	};
}



#endif /* TYPES_HPP_ */
