#ifndef GETTERS_HPP_
#define GETTERS_HPP_

#include <risa_gl/nv/method/base_method.hpp>
#include <risa_gl/nv/extractor.hpp>
#include <risa_gl/nv/selector.hpp>
#include <risa_gl/nv/functor.hpp>
#include <risa_gl/nv/template_functions.hpp>

namespace method
{
	namespace templ_func = template_functions;


	template <typename selector_t>
	struct getter_currying_selector
	{
		template <typename environ_t> 
		struct type :
			public impl::base_getter<environ_t,
									 extractor::dereference,
									 selector_t,
									 functor::identity>
		{};
	};

	/**
	 * color getter method.
	 */
	template <typename environ_t>
	struct source_color_getter : 
		public getter_currying_selector<
		selector::source_selector>::type<environ_t>
	{};

	template <typename environ_t>
	struct destination_color_getter : 
		public getter_currying_selector<
		selector::destination_selector>::type<environ_t>
	{};

	template <typename selector_t>
	struct alpha_getter_currying_selector
	{
		template <typename environ_t> 
		struct type :
			public impl::base_getter<environ_t,
									 templ_func::bind_2nd<
										 typename environ_t::basic_input_type,
										 extractor::alpha_factor>::template currying,
									 selector_t,
									 functor::identity>
		{};
	};

	/**
	 * alpha getter methods
	 *
	 */
	template <typename environ_t>
	struct source_alpha_getter :
		public alpha_getter_currying_selector<
		selector::source_selector>::type<environ_t>
	{};

	template <typename environ_t>
	struct destination_alpha_getter :
		public alpha_getter_currying_selector<
		selector::destination_selector>::type<environ_t>
	{};


	template <typename selector_t>
	struct inverse_alpha_getter_currying_selector
	{
		template <typename environ_t> 
		struct type :
			public impl::base_getter<environ_t,
									 templ_func::bind_2nd<
										 typename environ_t::basic_input_type,
										 extractor::alpha_factor>::
									 template currying,
									 selector_t,
									 functor::inverse<
										 extractor::channel_element_factor<
											 typename environ_t::
											 bit_pattern_type>,
										 functor::bit_nagate_functor> >
		{};
	};

	/**
	 * inverse alpha getter methods.
	 *
	 */
	template <typename environ_t>
	struct inverse_source_alpha_getter :
		public inverse_alpha_getter_currying_selector<
		selector::source_selector>::type<environ_t>
	{};

	template <typename environ_t>
	struct inverse_destination_alpha_getter :
		public inverse_alpha_getter_currying_selector<
		selector::destination_selector>::type<environ_t>
	{};
}

#endif /* GETTERS_HPP_ */
