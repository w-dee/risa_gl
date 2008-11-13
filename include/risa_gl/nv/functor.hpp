#ifndef FUNCTOR_HPP_
#define FUNCTOR_HPP_

namespace functor
{
	struct identity
	{
		template <typename input_type>
		input_type operator()(input_type src) const
		{
			return src;
		}
	};

	/**
	 * 補数取得オペレータ
	 */
	template <typename base_functor_t, typename nagate_operator_t>
	struct inverse
	{
		base_functor_t base_functor;
		nagate_operator_t nagate_operator;

		inverse(base_functor_t base_functor_ = base_functor_t(),
				nagate_operator_t nagate_operator_ = nagate_operator_t()):
			base_functor(base_functor_),
			nagate_operator(nagate_operator_)
		{}

		template <typename input_type>
		input_type operator()(input_type src) const
		{
			return base_functor(nagate_operator(src));
		}
	};

	struct bit_nagate_functor
	{
		template <typename input_type>
		input_type operator()(input_type src) const
		{
			return ~src;
		}
	};
}

#endif /* FUNCTOR_HPP_ */
