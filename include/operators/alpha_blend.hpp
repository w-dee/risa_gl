#ifndef RISA_ALPHA_BLEND_HPP_
#define RISA_ALPHA_BLEND_HPP_

#include "operators/primitive/primitive.hpp"

namespace risa_gl
{
	namespace operators
	{
		class alpha_blend_operator
		{
		public:
			typedef primitive::blend<source_alpha_factor,
									 zero_factor,
									 one_minus_source_alpha_factor,
									 identity_factor>
			alpha_blend;

			template <typename src_itor_t,
					  typename dest_itor_,
					  typename result_itor_t>
			void opearator()(src_itor_t src,
							 dest_itor_t dest,
							 result_itor_t result) const
			{
				alpha_blend()(src, dest, result);
			}
		};

		class reverse_alpha_blend_operator
		{
		public:
			typedef primitive::blend<one_minus_destination_alpha_factor,
									 identity_factor,
									 destination_alpha_factor,
									 identity_factor>
			alpha_blend;

			template <typename src_itor_t,
					  typename dest_itor_,
					  typename result_itor_t>
			void opearator()(src_itor_t src,
							 dest_itor_t dest,
							 result_itor_t result) const
			{
				alpha_blend()(src, dest, result);
			}
		};
	};
};

#endif /* RISA_ALPHA_BLEND_HPP_ */
