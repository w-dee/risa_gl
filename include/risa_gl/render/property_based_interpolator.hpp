#ifndef RISA_RENDER_PROPERTY_BASED_INTERPOLATOR_HPP_
#define RISA_RENDER_PROPERTY_BASED_INTERPOLATOR_HPP_

#include <cassert>

namespace risa_gl
{
	namespace render
	{
		template <typename value_t,
				  typename property_extractor_t,
				  typename scalar_t = typename value_t::value_type>
		class property_based_interpolator
		{
		public:
			typedef property_extractor_t property_extractor_type;
			typedef value_t value_type;
			typedef scalar_t scalar_type;

		private:
			const value_type head;
			const value_type tail;
			const value_type stepping;

			value_type get_stepping(
				const value_type& head_,
				const value_type& tail_,
				const property_extractor_type& extractor =
				property_extractor_type()) const
			{
				return (tail_ - head_) /
					(extractor(tail_) - extractor(head_)); 
			}

		public:
			property_based_interpolator(
				const value_type& head_,
				const value_type& tail_,
				const property_extractor_type& extractor =
				property_extractor_type()):
				head(head_),
				tail(tail_),
				stepping(get_stepping(head_, tail_))
			{}
			
			value_type get_stepping() const
			{
				return stepping;
			}

			scalar_type get_division() const
			{
				property_extractor_type extractor;
				return extractor(tail - head);
			}

			value_type operator()(
				int offset,
				const property_extractor_type& extractor =
				property_extractor_type()) const
			{
				assert (offset >= 0);
				;
				assert (extractor(head + stepping * scalar_type(offset)) <=
						extractor(tail));
				
				return head + stepping * scalar_type(offset);
			}
		};
	}
}

#endif /* RISA_RENDER_PROPERTY_BASED_INTERPOLATOR_HPP_ */
