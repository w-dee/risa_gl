#include <risa_gl/ext/risa_sse2_types.hpp>
#include <risa_gl/ext/functional.hpp>
#include <risa_gl/ext/alpha_factor.hpp>

namespace risa_gl
{
	namespace ext
	{
		namespace sse2
		{
			namespace ext_inst = risa_gl::ext;

			struct source_selector
			{
				template <typename src_itor_t,
						  typename dest_itor_t,
						  typename result_itor_t>
				result_itor_t operator()(src_itor_t src, dest_itor_t) const
				{
					return src;
				}
			};

			struct destination_selector
			{
				template <typename src_itor_t,
						  typename dest_itor_t,
						  typename result_itor_t>
				result_itor_t operator()(src_itor_t, dest_itor_t dest) const
				{
					return dest;
				}
			};

			typedef ext_inst::bits_getter<source_selector>
			source_getter;

			typedef ext_inst::bits_getter<destination_selector> 
			destination_getter;

			typedef vertical_add plus_function;

			typedef alpha_getter<source_selector, alpha_bits_get_method> 
			source_alpha_getter;

			invert_source_alpha_getter;
			not_calculate_policy;
		}
	}
}
