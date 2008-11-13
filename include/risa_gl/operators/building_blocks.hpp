#ifndef RISA_BUILDING_BLOCKS_HPP_
#define RISA_BUILDING_BLOCKS_HPP_

#include <risa_gl/primitive/alpha_policy.hpp>
#include <risa_gl/primitive/compute_function.hpp>
#include <risa_gl/primitive/alpha_factor.hpp>
#include <risa_gl/primitive/pixel_property.hpp>
#include <risa_gl/primitive/selector.hpp>
#include <risa_gl/primitive/method_selector.hpp>

namespace risa_gl
{
	namespace operators
	{
		using namespace risa_gl::primitive;

		// {{{ photoshop_blend
		/**
		 * photoshop互換用ブレンドヘルパ
		 */
		template <typename stub_operator,
				  typename blend_operator>
		class photoshop_blend
		{
		private:
			stub_operator stub;
			blend_operator blender;

		public:
			photoshop_blend(stub_operator stub_ = stub_operator(),
							blend_operator blender_ = blend_operator()):
				stub(stub_), blender(blender_)
			{}

			photoshop_blend(const photoshop_blend& src):
				stub(src.stub), blender(src.blender)
			{}

			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							dest_itor_t dest,
							result_itor_t result) const
			{
				typename result_itor_t::value_type temp_result;
				stub(src, dest, &temp_result);
				blender(&temp_result, dest, result);
			}			
		};
		// }}}

		// {{{ pixel_getter
		// {{{ source
		typedef bits_getter<source_selector> source_getter;
		// }}}
		// {{{ destination
		typedef bits_getter<destination_selector> destination_getter;

		typedef invert_getter<source_selector> invert_source_getter;
		typedef invert_getter<destination_selector> invert_destination_getter;
		// }}}
		// }}}
		
		// {{{ alpha getters
		typedef alpha_factor<source_selector,
							 get_alpha_method_selector>
		source_alpha_getter;
		typedef alpha_factor<destination_selector,
							 get_alpha_method_selector>
		destination_alpha_getter;

		typedef inverse_alpha_factor<source_selector,
									 get_alpha_method_selector>
		inverse_source_alpha_getter;
		typedef inverse_alpha_factor<destination_selector,
									 get_alpha_method_selector>
		inverse_destination_alpha_getter;
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
				source_factor(src.source_factor),
				multiply(src.multiply)
			{}
			
			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t src,
									   dest_itor_t dest) const
			{
				return multiply(src, dest, source_factor(src, dest));
			}
		};
		// }}}

		// {{{ constant multiply factor
		/**
		 * src_typeを適用した結果をoperator()の引数にかけて返す
		 */
		template <typename src_type, int divisor = 256>
		class multiply_type_factor
		{
		private:
			src_type source;

		public:
			multiply_type_factor(const src_type& source_ = src_type()):
				source(source_)
			{}

			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename value_type_t>
			risa_gl::uint32 operator()(src_itor_t src,
									   dest_itor_t dest,
									   value_type_t value) const
			{
				return (source(src, dest) * value) / divisor;
			}
		};
		// }}}

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

		typedef multiply_factor<
			invert_source_alpha_getter,
			multiply_type_factor<constant_alpha_factor> >
		multiply_invert_source_alpha_and_constant_alpha_getter;

		class multiply_constant_and_source_opacity_getter
		{
		private:
			typedef multiply_factor<
				constant_alpha_factor,
				multiply_type_factor<source_opacity_getter> >
			mult_const_and_opacity_type;

			mult_const_and_opacity_type oper;

		public:
			multiply_constant_and_source_opacity_getter(
				const int constant):
				oper(constant_alpha_factor(constant))
			{}

			multiply_constant_and_source_opacity_getter(
				const multiply_constant_and_source_opacity_getter& src):
				oper(src.oper)
			{}

			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32  operator()(src_itor_t src,
										dest_itor_t dest) const

			{
				return oper(src, dest);
			}
		};

		template <int min, int max, int projection_min, int projection_max>
		class multiply_constant_and_scaled_source_opacity_getter
		{
		private:
			typedef multiply_factor<
				constant_alpha_factor,
				multiply_type_factor<
				scaled_source_opacity_getter<
				min, max, 
				projection_min, projection_max> > >
			mult_const_and_scaled_opacity_type;

			mult_const_and_scaled_opacity_type oper;

		public:
			multiply_constant_and_scaled_source_opacity_getter(
				const int constant):
				oper(constant_alpha_factor(constant))
			{}

			multiply_constant_and_scaled_source_opacity_getter(
				const multiply_constant_and_scaled_source_opacity_getter& src):
				oper(src.oper)
			{}

			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32  operator()(src_itor_t src,
										dest_itor_t dest) const

			{
				return oper(src, dest);
			}
		};
				
		class multiply_invert_constant_and_source_opacity_getter
		{
		private:
			typedef multiply_factor<
				constant_alpha_factor,
				multiply_type_factor<source_opacity_getter> >
			mult_const_and_opacity_type;

			mult_const_and_opacity_type oper;

		public:
			multiply_invert_constant_and_source_opacity_getter(
				const int constant):
				oper(constant_alpha_factor(constant))
			{}

			multiply_invert_constant_and_source_opacity_getter(
				const multiply_invert_constant_and_source_opacity_getter& src):
				oper(src.oper)
			{}

			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32  operator()(src_itor_t src,
										dest_itor_t dest) const

			{
				return 257 - oper(src, dest);
			}
		};
		
		template <int min, int max, int projection_min, int projection_max>
		class multiply_invert_constant_and_scaled_source_opacity_getter
		{
		private:
			typedef multiply_factor<
				constant_alpha_factor,
				multiply_type_factor<
				scaled_source_opacity_getter<
				min, max, 
				projection_min, projection_max> > >
			mult_const_and_scaled_opacity_type;

			mult_const_and_scaled_opacity_type oper;

		public:
			multiply_invert_constant_and_scaled_source_opacity_getter(
				const int constant):
				oper(constant_alpha_factor(257 - constant))
			{}

			multiply_invert_constant_and_scaled_source_opacity_getter(
				const multiply_invert_constant_and_scaled_source_opacity_getter& src):
				oper(src.oper)
			{}

			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t src,
									   dest_itor_t dest) const
			{
				return oper(src, dest);
			}
		};
		// }}}

		// {{{ multiply alpha and alpha policy
		template <typename source_getter_type,
				  typename destination_getter_type>
		class multiply_alpha_and_alpha_policy
		{
		private:
			template <typename source_getter_t,
					  typename destination_getter_t>
			struct alpha_and_alpha_calculator
			{
				source_getter_t source_getter;
				destination_getter_t destination_getter;

				alpha_and_alpha_calculator(
					source_getter_t source_getter_ =
					source_getter_t(),
					destination_getter_t destination_getter_ =
					destination_getter_t()):
					source_getter(source_getter_),
					destination_getter(destination_getter_)
				{}
					
				template <typename src_itor_t,
						  typename dest_itor_t>
				risa_gl::uint32 operator()(src_itor_t src,
										   dest_itor_t dest) const
				{
					const int src_alpha = 
						source_getter(src, dest);
					const int dest_alpha =
						destination_getter(src, dest);

					/**
					 * mean to
					 *  src.a + dest.a - src.a * dest.a 
					 */
					return src_alpha + dest_alpha -
						((src_alpha * dest_alpha) >> 8);
				}
			};

			typedef alpha_and_alpha_calculator<source_getter_type,
										   destination_getter_type>
			alpha_and_alpha_type;
			typedef alpha_calculate_policy<alpha_and_alpha_type>
			alpha_setter_type;

			alpha_setter_type alpha_setter;

		public:
			multiply_alpha_and_alpha_policy(
				source_getter_type source_getter_ =
				source_getter_type(),
				destination_getter_type destination_getter_ =
				destination_getter_type()):
				alpha_setter(
					alpha_and_alpha_type(source_getter_, destination_getter_))
			{}


			template <typename bit_t,
					  typename result_itor_t,
					  typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32  operator()(bit_t bits,
										result_itor_t result,
										src_itor_t src,
										dest_itor_t dest) const
			{
				return alpha_setter(bits, result, src, dest);
			}
		};
		// }}}
	}
}

#endif /* RISA_BUILDING_BLOCKS_HPP_ */
