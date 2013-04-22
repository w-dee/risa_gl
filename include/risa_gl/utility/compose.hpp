#ifndef RISA_UTILITY_COMPOSE_HPP_
#define RISA_UTILITY_COMPOSE_HPP_

namespace risa_gl
{
	namespace utility
	{
		struct identity
		{
			template <typename arg0_t>
			arg0_t operator()(arg0_t arg0) const
			{
				return arg0;
			}
		};

		template <typename result_t, typename functor_t, typename filter_t>
		class compose1_trait
		{
		private:
			functor_t functor;
			filter_t filter;
		public:
			compose1_trait(functor_t functor_, filter_t filter_):
				functor(functor_),
				filter(filter_)
			{}

			template <typename arg0_t>
			result_t operator()(arg0_t arg0)
			{
				return functor(filter(arg0));
			}
		};

		template <typename result_t,
				  typename functor_t,
				  typename filter0_t,
				  typename filter1_t = identity>
		class compose2_trait
		{
		private:
			functor_t functor;
			filter0_t filter0;
			filter1_t filter1;

		public:
			compose2_trait(functor_t functor_,
						   filter0_t filter0_,
						   filter1_t filter1_ = identity()):
				functor(functor_),
				filter0(filter0_),
				filter1(filter1_)
			{}

			template <typename arg0_t, typename arg1_t>
			result_t operator()(arg0_t arg0, arg1_t arg1)
			{
				return functor(filter0(arg0), filter1(arg1));
			}
		};

		class compose
		{
		public:
			template <typename result_t,
					  typename origin_func, typename compose_func0>
			static compose1_trait<result_t, origin_func, compose_func0>
			compose1(origin_func functor, compose_func0 filter)
			{
				return
					compose1_trait<result_t, origin_func, compose_func0>(
						functor, filter);
			}

			template <typename result_t,
					  typename origin_func,
					  typename compose_func0,
					  typename compose_func1>
			static compose2_trait<result_t,
						   origin_func,
						   compose_func0,
						   compose_func1>
			compose2(origin_func functor,
					 compose_func0 filter0,
					 compose_func1 filter1)
			{
				return compose2_trait<result_t,
									  origin_func,
									  compose_func0,
									  compose_func1>(
										  functor, filter0, filter1);
			}
		};
	}
}

#endif /* RISA_UTILITY_COMPOSE_HPP_ */
