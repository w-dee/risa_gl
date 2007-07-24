#ifndef RISA_BUILDING_BLOCKS_HPP_
#define RISA_BUILDING_BLOCKS_HPP_

#include "operators/primitive/alpha_policy.hpp"
#include "operators/primitive/compute_factor.hpp"
#include "operators/primitive/alpha_factor.hpp"
#include "operators/primitive/pixel_property.hpp"
#include "operators/primitive/selector.hpp"
#include "operators/primitive/method_selector.hpp"


namespace risa_gl
{
	namespace operators
	{
		using namespace risa_gl::primitive;

		// getters(pixel value)
		typedef bits_getter<source_selector> source_getter;
		typedef bits_getter<destination_selector> destination_getter;
		
		// alpha getters
		typedef alpha_factor<source_selector,
							 get_alpha_method_selector>
		source_alpha_getter;
		typedef alpha_factor<destination_selector,
							 get_alpha_method_selector>
		destination_alpha_getter;

		// invert alpha getter
		typedef invert_alpha_factor<source_selector,
									get_alpha_method_selector>
		invert_source_alpha_getter;
		typedef invert_alpha_factor<destination_selector,
									get_alpha_method_selector>
		invert_destination_alpha_getter;

		// opacity getter
		typedef alpha_factor<source_selector,
							 get_opacity_method_selector>
		source_opacity_getter;
		typedef alpha_factor<destination_selector,
							 get_opacity_method_selector>
		destination_opacity_getter;

		template <int min, int max,
				  int projection_min, int projection_max>
		class scaled_source_opacity_getter
		{
			typedef scaled_alpha_selector<min,
										  max,
										  projection_min,
										  projection_max,
										  source_selector,
										  get_opacity_method_selector>
			scaler_type;
		public:
			template <typename src_itor_t, typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t src,
									   dest_itor_t dest) const
			{
				return scaler_type()(src, dest);
			}
		};

		template <int min, int max,
				  int projection_min, int projection_max>
		class scaled_destination_opacity_getter
		{
			typedef scaled_alpha_selector<min,
										  max,
										  projection_min,
										  projection_max,
										  destination_selector,
										  get_opacity_method_selector>
			scaler_type;
		public:
			template <typename src_itor_t, typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t src,
									   dest_itor_t dest) const
			{
				return scaler_type()(src, dest);
			}
		};

		// invert opacity getter
		typedef invert_alpha_factor<source_selector,
									get_opacity_method_selector>
		invert_source_opacity_getter;
		typedef invert_alpha_factor<destination_selector,
									get_opacity_method_selector>
		incert_destination_opacity_getter;
		
	};
};

#endif /* RISA_BUILDING_BLOCKS_HPP_ */
