#ifndef RISA_BUILDING_BLOCKS_HPP_
#define RISA_BUILDING_BLOCKS_HPP_

#include <operators/primitive/alpha_policy.hpp>
#include <operators/primitive/compute_factor.hpp>
#include <operators/primitive/alpha_factor.hpp>
#include <operators/primitive/pixel_property.hpp>
#include <operators/primitive/selector.hpp>
#include <operators/primitive/method_selector.hpp>


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

		// invert scaled opacity getter

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

		// invert scaled opacity getter
		template <int min, int max,
				  int projection_min, int projection_max>
		class scaled_invert_source_opacity_getter
		{
			typedef scaled_invert_alpha_selector<min,
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
		class scaled_invert_destination_opacity_getter
		{
			typedef scaled_invert_alpha_selector<min,
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
		invert_destination_opacity_getter;


		template <typename source_selector,
				  typename source_method_selector,
				  typename destination_selector,
				  typename destination_method_selector>
		class multiply_alpha_and_alpha_policy
		{
		private:
			template <typename source_selector_type,
					  typename source_method_selector_type,
					  typename destination_selector_type,
					  typename destination_method_selector_type>
			struct alpha_and_alpha_calculator
			{
				template <typename src_itor_t,
						  typename dest_itor_t>
				unsigned int operator()(
					src_itor_t src,
					dest_itor_t dest) const
				{
					const int src_alpha = 
						source_method_selector_type()(
							source_selector_type()(src, dest));
					const int dest_alpha =
						destination_method_selector_type()(
							destination_selector_type()(src, dest));

					/**
					 * mean to
					 *  src.a * src.a + dest.a * (identity - src.a)
					 *
					 *  src.a(src.a - dest.a) + dest.a * identity
					 */
					return ((src_alpha *
							 (src_alpha - dest_alpha)) >> 8) + dest_alpha;
				}
			};
		public:
			template <typename result_itor_t,
					  typename src_itor_t,
					  typename dest_itor_t>
			void operator()(result_itor_t result,
							src_itor_t src,
							dest_itor_t dest) const
			{
				alpha_calculate_policy<
					alpha_and_alpha_calculator<
					source_selector,
					source_method_selector,
					destination_selector,
					destination_method_selector> >()(result, src, dest);
			}
		};
	};
};

#endif /* RISA_BUILDING_BLOCKS_HPP_ */
