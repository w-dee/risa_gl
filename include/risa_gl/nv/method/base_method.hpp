#ifndef BASE_METHODS_HPP_
#define BASE_METHODS_HPP_

namespace method
{
	namespace impl
	{
		/**
		 * getterのデフォルト実装
		 */
		template <typename environ_t,
				  template <typename> class extractor_t,
				  typename selector_t,
				  typename functor_t>
		struct base_getter
		{
			typedef typename environ_t::bit_pattern_type value_type;
			typedef extractor_t<value_type> extractor_type;
			typedef selector_t selector_type;
			typedef functor_t functor_type;

			extractor_type extractor;
			selector_type selector;
			functor_type functor;

			base_getter(const extractor_type& extractor_ =
						extractor_type(),
						const selector_type& selector_ =
						selector_type(),
						const functor_type& functor_ = 
						functor_type()):
				extractor(extractor_),
				selector(selector_),
				functor(functor_)
			{}

			template <typename input_type>
			value_type operator()(input_type src, input_type dest) const
			{
				input_type selected = selector(src, dest);
				value_type extracted = extractor(selected);
				value_type applied = functor(extracted);
				return applied;
			}
		};
}
}

#endif /* BASE_METHODS_HPP_ */
