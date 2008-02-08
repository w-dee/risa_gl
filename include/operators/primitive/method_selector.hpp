#ifndef RISA_METHOD_SELECTOR_HPP_
#define RISA_METHOD_SELECTOR_HPP_

#include <risa_gl/risa_types.hpp>

namespace risa_gl
{
	namespace primitive
	{
		class get_alpha_method_selector
		{
		public:
			template <typename itor_t>
			int operator()(itor_t itor) const
			{
				return itor->get_alpha();
			}
		};

		class get_opacity_method_selector
		{
		public:
			template <typename itor_t>
			int operator()(itor_t itor) const
			{
				return itor->get_opacity();
			}
		};
	}
}
#endif /* RISA_METHOD_SELECTOR_HPP_ */
