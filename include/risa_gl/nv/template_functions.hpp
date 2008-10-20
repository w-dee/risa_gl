#ifndef TEMPLATE_FUNCTIONS_HPP_
#define TEMPLATE_FUNCTIONS_HPP_

namespace template_functions
{
	template <typename value_t,
			  typename base_t,
			  base_t bit_pattern,
			  int fill_count = sizeof(value_t) / sizeof(base_t)>
	struct filler
	{
		
		static value_t value()
		{
			return
				(static_cast<value_t>(bit_pattern) <<
				 ((fill_count - 1) * sizeof(base_t) * 8)) |
				filler<value_t,
				base_t,
				bit_pattern, fill_count - 1>::value();
		}

	};

	template <typename value_t, typename base_t, base_t bit_pattern>
	struct filler<value_t, base_t, bit_pattern, 0>
	{
		static value_t value()
		{
			return static_cast<value_t>(0);
		}
	};

	template <typename second_type,
			  template <typename,typename> class currying_type>
	struct bind_2nd
	{
		template <typename first_type>
		struct currying :
			public currying_type<first_type,
								 second_type>
		{
			typedef currying_type<first_type,
								  second_type> type;
		};
	};
}
#endif /* TEMPLATE_FUNCTIONS_HPP_ */
