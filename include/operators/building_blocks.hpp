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
		public:
			
			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t src,
									   dest_itor_t dest) const
			{
				return multiply_type(src, dest)(source_type()(src, dest));
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
		private:
			risa_gl::uint32 factor;

		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			multiply_type_factor(src_itor_t src, dest_itor_t dest):
				factor(src_type()(src, dest))
			{}

			risa_gl::uint32 operator()(risa_gl::uint32 value) const
			{
				return (factor * value) >> 8;
			}
		};
		// }}}

		// {{{ multiply factor
		typedef multiply_factor<
			invert_source_alpha_getter,
			multiply_type_factor<destination_alpha_getter> >
		multiply_invert_source_alpha_and_destination_alpha_getter;
		// }}}

		// invert scaled opacity getter

		// {{{ with opacity channel alpha operators.
		template <typename selector_type, typename method_selector>
		class alpha_getter_with_opacity
		{
			typedef alpha_factor<selector_type,
								 method_selector> operator_type;

			const int opacity;
			operator_type operator_method;

		public:
			const int get_opacity() const
			{
				return opacity;
			}

			alpha_getter_with_opacity():
				opacity(256)
			{}

			alpha_getter_with_opacity(const alpha_getter_with_opacity& src):
				opacity(src.opacity),
				operator_method(src.operator_method)
			{}

			alpha_getter_with_opacity(const int opacity_):
				opacity(opacity_)
			{}

			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t src,
									   dest_itor_t dest) const
			{
				return (operator_method(src, dest) * opacity) >> 8;
			}
		};

		template <typename selector_type, typename method_selector>
		class invert_alpha_getter_with_opacity
		{
			typedef alpha_factor<selector_type,
								 method_selector> operator_type;

			const int opacity;
			operator_type operator_method;

		public:
			const int get_opacity() const
			{
				return opacity;
			}

			invert_alpha_getter_with_opacity():
				opacity(256)
			{}

			invert_alpha_getter_with_opacity(
				const invert_alpha_getter_with_opacity& src):
				opacity(src.opacity),
				operator_method(src.operator_method)
			{}

			invert_alpha_getter_with_opacity(const int opacity_):
				opacity(opacity_)
			{}

			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t src,
									   dest_itor_t dest) const
			{
				return 256 - ((operator_method(src, dest) * opacity) >> 8);
			}
		};
		// }}}

		// {{{ target alpha getter with opacities.
		class source_alpha_getter_with_opacity :
			public alpha_getter_with_opacity<source_selector,
			get_alpha_method_selector>
		{
			typedef alpha_getter_with_opacity<source_selector,
											  get_alpha_method_selector>
			parent_type;

		public:
			source_alpha_getter_with_opacity():
				parent_type()
			{}

			source_alpha_getter_with_opacity(
				const source_alpha_getter_with_opacity& src):
				parent_type(src)
			{}

			source_alpha_getter_with_opacity(const int opacity_):
				parent_type(opacity_)
			{}
		};

		class destination_alpha_getter_with_opacity :
			public alpha_getter_with_opacity<destination_selector,
			get_alpha_method_selector>
		{
			typedef alpha_getter_with_opacity<destination_selector,
											  get_alpha_method_selector>
			parent_type;

		public:
			destination_alpha_getter_with_opacity():
				parent_type()
			{}

			destination_alpha_getter_with_opacity(
				const destination_alpha_getter_with_opacity& src):
				parent_type(src)
			{}

			destination_alpha_getter_with_opacity(const int opacity_):
				parent_type(opacity_)
			{}
		};

		class source_opacity_getter_with_opacity :
			public alpha_getter_with_opacity<source_selector,
			primitive::get_opacity_method_selector>
		{
			typedef alpha_getter_with_opacity<
				source_selector,
				primitive::get_opacity_method_selector>
			parent_type;

		public:
			source_opacity_getter_with_opacity():
				parent_type()
			{}

			source_opacity_getter_with_opacity(
				const source_opacity_getter_with_opacity& src):
				parent_type(src.get_opacity())
			{}

			source_opacity_getter_with_opacity(const int opacity_):
				parent_type(opacity_)
			{}
		};

		class destination_opacity_getter_with_opacity :
			public alpha_getter_with_opacity<destination_selector,
			get_opacity_method_selector>
		{
			typedef alpha_getter_with_opacity<
				destination_selector,
				get_opacity_method_selector>
			parent_type;

		public:
			destination_opacity_getter_with_opacity():
				parent_type()
			{}

			destination_opacity_getter_with_opacity(
				const destination_alpha_getter_with_opacity& src):
				parent_type(src.get_opacity())
			{}

			destination_opacity_getter_with_opacity(const int opacity_):
				parent_type(opacity_)
			{}
		};
		// }}}

		// {{{ invert target alpha getter with opacities
		class invert_source_alpha_getter_with_opacity :
			public invert_alpha_getter_with_opacity<source_selector,
			get_alpha_method_selector>
		{
			typedef invert_alpha_getter_with_opacity<source_selector,
													 get_alpha_method_selector>
			parent_type;

		public:
			invert_source_alpha_getter_with_opacity():
				parent_type()
			{}

			invert_source_alpha_getter_with_opacity(
				const source_alpha_getter_with_opacity& src):
				parent_type(src.get_opacity())
			{}

			invert_source_alpha_getter_with_opacity(const int opacity_):
				parent_type(opacity_)
			{}
		};

		class invert_destination_alpha_getter_with_opacity :
			public invert_alpha_getter_with_opacity<destination_selector,
			get_alpha_method_selector>
		{
			typedef invert_alpha_getter_with_opacity<destination_selector,
													 get_alpha_method_selector>
			parent_type;

		public:
			invert_destination_alpha_getter_with_opacity():
				parent_type()
			{}

			invert_destination_alpha_getter_with_opacity(
				const invert_destination_alpha_getter_with_opacity& src):
				parent_type(src.get_opacity())
			{}

			invert_destination_alpha_getter_with_opacity(const int opacity_):
				parent_type(opacity_)
			{}
		};

		class invert_source_opacity_getter_with_opacity :
			public invert_alpha_getter_with_opacity<source_selector,
			get_opacity_method_selector>
		{
			typedef invert_alpha_getter_with_opacity<
				source_selector,
				get_opacity_method_selector>
			parent_type;

		public:
			invert_source_opacity_getter_with_opacity():
				parent_type()
			{}

			invert_source_opacity_getter_with_opacity(
				const source_alpha_getter_with_opacity& src):
				parent_type(src.get_opacity())
			{}

			invert_source_opacity_getter_with_opacity(const int opacity_):
				parent_type(opacity_)
			{}
		};

		class invert_destination_opacity_getter_with_opacity :
			public invert_alpha_getter_with_opacity<destination_selector,
			get_opacity_method_selector>
		{
			typedef invert_alpha_getter_with_opacity<
				destination_selector,
				get_opacity_method_selector>
			parent_type;

		public:
			invert_destination_opacity_getter_with_opacity():
				parent_type()
			{}

			invert_destination_opacity_getter_with_opacity(
				const destination_alpha_getter_with_opacity& src):
				parent_type(src.get_opacity())
			{}

			invert_destination_opacity_getter_with_opacity(const int opacity_):
				parent_type(opacity_)
			{}
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

		template <int min, int max,
				  int projection_min, int projection_max>
		class scaled_source_opacity_getter_with_opacity
		{
			typedef scaled_alpha_selector<min,
										  max,
										  projection_min,
										  projection_max,
										  source_selector,
										  get_opacity_method_selector>
			scaler_type;
			
			const int opacity;

		public:
			const int get_opacity() const
			{
				return opacity;
			}

			scaled_source_opacity_getter_with_opacity():
				opacity(256)
			{}

			scaled_source_opacity_getter_with_opacity(const int opacity_):
				opacity(opacity_)
			{}

			scaled_source_opacity_getter_with_opacity(
				const scaled_source_opacity_getter_with_opacity& src):
				opacity(src.get_opacity())
			{}
				
			template <typename src_itor_t, typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t src,
									   dest_itor_t dest) const
			{
				return (scaler_type()(src, dest) * opacity) >> 8;
			}
		};

		template <int min, int max,
				  int projection_min, int projection_max>
		class scaled_destination_opacity_getter_with_opacity
		{
			typedef scaled_alpha_selector<min,
										  max,
										  projection_min,
										  projection_max,
										  destination_selector,
										  get_opacity_method_selector>
			scaler_type;
			
			const int opacity;

		public:
			const int get_opacity() const
			{
				return opacity;
			}

			scaled_destination_opacity_getter_with_opacity():
				opacity(256)
			{}

			scaled_destination_opacity_getter_with_opacity(const int opacity_):
				opacity(opacity_)
			{}

			scaled_destination_opacity_getter_with_opacity(
				const scaled_destination_opacity_getter_with_opacity& src):
				opacity(src.get_opacity())
			{}
				
			template <typename src_itor_t, typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t src,
									   dest_itor_t dest) const
			{
				return (scaler_type()(src, dest) * opacity) >> 8;
			}
		};
		// }}}

		// {{{ invert scaled opacity getter
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

		// {{{ invert scaled opacity getter with opacity
		template <int min, int max,
				  int projection_min, int projection_max>
		class scaled_invert_source_opacity_getter_with_opacity
		{
			typedef scaled_invert_alpha_selector<min,
												 max,
												 projection_min,
												 projection_max,
												 source_selector,
												 get_opacity_method_selector>
			scaler_type;

			const int opacity;

		public:
			const int get_opacity() 
			{
				return opacity;
			}

			scaled_invert_source_opacity_getter_with_opacity():
				opacity(256)
			{}

			scaled_invert_source_opacity_getter_with_opacity(const int opacity_):
				opacity(opacity_)
			{}

			scaled_invert_source_opacity_getter_with_opacity(
				const scaled_invert_source_opacity_getter_with_opacity& src):
				opacity(src.get_opacity())
			{}

			template <typename src_itor_t, typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t src,
									   dest_itor_t dest) const
			{
				return (scaler_type()(src, dest) * opacity) >> 8;
			}
		};

		template <int min, int max,
				  int projection_min, int projection_max>
		class scaled_invert_destination_opacity_getter_with_opacity
		{
			typedef scaled_invert_alpha_selector<min,
												 max,
												 projection_min,
												 projection_max,
												 destination_selector,
												 get_opacity_method_selector>
			scaler_type;

			const int opacity;

		public:
			const int get_opacity() 
			{
				return opacity;
			}

			scaled_invert_destination_opacity_getter_with_opacity():
				opacity(256)
			{}

			scaled_invert_destination_opacity_getter_with_opacity(const int opacity_):
				opacity(opacity_)
			{}

			scaled_invert_destination_opacity_getter_with_opacity(
				const scaled_invert_destination_opacity_getter_with_opacity& src):
				opacity(src.get_opacity())
			{}

			template <typename src_itor_t, typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t src,
									   dest_itor_t dest) const
			{
				return (scaler_type()(src, dest) * opacity) >> 8;
			}
		};
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
					source_getter,
					destination_getter> >()(result, src, dest);
			}
		};
		// }}}
	}
}

#endif /* RISA_BUILDING_BLOCKS_HPP_ */
