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

		// {{{ pixel_getter
		// {{{ source
		typedef bits_getter<source_selector> source_getter;
		// }}}
		// {{{ destination
		typedef bits_getter<destination_selector> destination_getter;
		// }}}
		// }}}
		
		// {{{ alpha getters
		typedef alpha_factor<source_selector,
							 get_alpha_method_selector>
		source_alpha_getter;
		typedef alpha_factor<destination_selector,
							 get_alpha_method_selector>
		destination_alpha_getter;
		// }}}

		// {{{ invert alpha getter
		typedef invert_alpha_factor<source_selector,
									get_alpha_method_selector>
		invert_source_alpha_getter;
		typedef invert_alpha_factor<destination_selector,
									get_alpha_method_selector>
		invert_destination_alpha_getter;
		// }}}

		// {{{ multiply factor and factor.
		template <typename source_type, typename multiply_type>
		class multiply_factor
		{
		private:
			source_type source_factor;
			multiply_type multiply;

		public:
			multiply_factor(const source_type& source_ = source_type(),
							const multiply_type& multiply_ = multiply_type()):
				source_factor(source_),
				multiply(multiply_)
			{}

			multiply_factor(const multiply_factor& src):
				source_factor(src.source),
				multiply(src.multiply)
			{}
			
			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t src,
									   dest_itor_t dest) const
			{
				return multiply_type(src, dest, source_factor(src, dest));
			}
		};
		// }}}

		// {{{ constant multiply factor
		/**
		 * src_typeを適用した結果をoperator()の引数にかけて返す
		 */
		template <typename src_type>
		class multiply_type_factor
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t src,
									   dest_itor_t dest,
									   risa_gl::uint32 value) const
			{
				return (src_type()(src, dest) * value) >> 8;
			}
		};
		// }}}

		// {{{ scaled opacity getters.
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

		// {{{ invert scaled opacity getter
		template <int min, int max,
				  int projection_min, int projection_max>
		class scaled_invert_source_opacity_getter
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
				return projection_max - scaler_type()(src, dest);
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
				return projection_max - scaler_type()(src, dest);
			}
		};
		// }}}

		// {{{ multiply factor
		typedef multiply_factor<
			invert_source_alpha_getter,
			multiply_type_factor<destination_alpha_getter> >
		multiply_invert_source_alpha_and_destination_alpha_getter;

		template <int min, int max, int projection_min, int projection_max>
		class multiply_constant_and_scaled_source_opacity_getter
		{
		private:
			typedef multiply_factor<
				constant_alpha_factor,
				scaled_source_opacity_getter<
				min, max, 
				projection_min, projection_max> > mult_const_and_scaled_opacity_type;

			mult_const_and_scaled_opacity_type oper;

		public:
			multiply_constant_and_scaled_source_opacity_getter(const int constant):
				oper(constant_alpha_factor(constant))
			{}

			multiply_constant_and_scaled_source_opacity_getter(
				const multiply_constant_and_scaled_source_opacity_getter& src):
				oper(src.oper)
			{}

			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							dest_itor_t dest,
							result_itor_t result) const
			{
				oper(src, dest, result);
			}
		};
				
		
		template <int min, int max, int projection_min, int projection_max>
		class multiply_invert_constant_and_scaled_source_opacity_getter
		{
		private:
			typedef multiply_factor<
				constant_alpha_factor,
				scaled_source_opacity_getter<
				min, max, 
				projection_min, projection_max> > mult_const_and_scaled_opacity_type;

			mult_const_and_scaled_opacity_type oper;

		public:
			multiply_invert_constant_and_scaled_source_opacity_getter(const int constant):
				oper(constant_alpha_factor(257 - constant))
			{}

			multiply_invert_constant_and_scaled_source_opacity_getter(
				const multiply_invert_constant_and_scaled_source_opacity_getter& src):
				oper(src.oper)
			{}

			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							dest_itor_t dest,
							result_itor_t result) const
			{
				oper(src, dest, result);
			}
		};
		// }}}

		// invert scaled opacity getter

		// {{{ opacity getter
		typedef alpha_factor<source_selector,
							 get_opacity_method_selector>
		source_opacity_getter;
		typedef alpha_factor<destination_selector,
							 get_opacity_method_selector>
		destination_opacity_getter;
		// }}}

		// {{{ invert opacity getter
		typedef invert_alpha_factor<source_selector,
									get_opacity_method_selector>
		invert_source_opacity_getter;
		typedef invert_alpha_factor<destination_selector,
									get_opacity_method_selector>
		invert_destination_opacity_getter;
		// }}}

		// {{{ multiply alpha and alpha policy
		template <typename source_getter,
				  typename destination_getter>
		class multiply_alpha_and_alpha_policy
		{
		private:
			template <typename source_getter_type,
					  typename destination_getter_type>
			struct alpha_and_alpha_calculator
			{
				template <typename src_itor_t,
						  typename dest_itor_t>
				unsigned int operator()(
					src_itor_t src,
					dest_itor_t dest) const
				{
					const int src_alpha = 
						source_getter_type()(src, dest);
					const int dest_alpha =
						destination_getter_type()(src, dest);

					/**
					 * mean to
					 *  src.a + dest.a - src.a * dest.a 
					 */
					return src_alpha + dest_alpha - ((src_alpha * dest_alpha) >> 8);
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
					source_getter,
					destination_getter> >()(result, src, dest);
			}
		};
		// }}}
	}
}

#endif /* RISA_BUILDING_BLOCKS_HPP_ */
