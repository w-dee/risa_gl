#ifndef RISA_EXT_SSE2_PRIMITIVE_ALPHA_FACTOR_HPP_
#define RISA_EXT_SSE2_PRIMITIVE_ALPHA_FACTOR_HPP_

#include <risa_gl/ext/sse2/risa_types.hpp>
#include <risa_gl/ext/sse2/primitive/functional.hpp>
#include <risa_gl/endian_traits.hpp>
#include <risa_gl/endian_reverser.hpp>

namespace risa_gl
{
	namespace ext
	{
		namespace sse2
		{
			namespace primitive
			{
				class identity_alpha_factor
				{
				private:
					const aligned_wideword_type identity_value;
				
					static aligned_wideword_type identity_init()
					{
						
						int init_value = byte_endian_reverser<256>::value;
						return _mm_set1_epi32(init_value);
					}
				public:
					identity_alpha_factor():
						identity_value(identity_init())
					{}

					template <typename src_itor_t,
							  typename dest_itor_t>
					aligned_wideword_type operator()(src_itor_t src,
													 dest_itor_t dest) const
					{
						return identity_value;
					}
				};

				class zero_alpha_factor
				{
				public:
					template <typename src_itor_t,
							  typename dest_itor_t>
					aligned_wideword_type operator()(src_itor_t src,
													 dest_itor_t dest) const
					{
						return _mm_setzero_si128();
					}
				};

				/**
				 * 選択型アルファファクタ
				 * @param selector srcかdestを指定するselector
				 * @param method_selector アルファ値を取り出すmethod_selector
				 */
				template <typename selector,
						  typename method_selector>
				class alpha_factor
				{
				public:
					template <typename src_itor_t,
							  typename dest_itor_t>
					aligned_wideword_type
					operator()(src_itor_t src,
							   dest_itor_t dest) const
					{
						return method_selector()(selector()(src, dest));
					}
				};

				/**
				 * selectorを利用して対象からalpha値を取り出し、逆数を返す
				 * @param
				 */
				template <typename selector,
						  typename method_selector>
				class inverse_alpha_factor
				{
				private:
					__m128 base;
				
				public:
					inverse_alpha_factor():
						base(_mm_set1_ps(256.f))
					{}

					template <typename src_itor_t,
							  typename dest_itor_t>
					aligned_wideword_type
					operator()(src_itor_t src,
							   dest_itor_t dest) const
					{
						__m128 float_values = _mm_cvtepi32_ps(method_selector()(selector()(src, dest)));
						__m128 invert_float_values = _mm_rcp_ps(float_values);
						__m128 result = _mm_mul_ps(base, invert_float_values);
						return _mm_cvttps_epi32(result);
					}
				};

				template <risa_gl::uint32 min, risa_gl::uint32 max,
						  risa_gl::uint32 projection_min, risa_gl::uint32 projection_max>
				class scale_factor
				{
				private:
					__m128i min_values;
					__m128i projection_min_values;
					__m128i projection_range_div_range;

					__m128i compute(risa_gl::uint32 projection_range,
									risa_gl::uint32 range) const
					{
						risa_gl::uint32 factor = projection_range / range;
						return _mm_set1_epi32(factor);
					}

				public:
					scale_factor():
						min_values(_mm_set1_epi32(min)),
						projection_min_values(_mm_set1_epi32(projection_min)),
						projection_range_div_range(
							compute(projection_max - projection_min,
									max - min))
					{}

					aligned_wideword_type
					operator()(aligned_wideword_type value) const
					{
						return
							_mm_add_epi32(
								_mm_mullo_epi16(_mm_sub_epi32(value, min_values),
												projection_range_div_range),
								projection_min_values);
					}
				};

				/**
				 * 写像スケーリングつきalpha_selector
				 * @param min 元のalpha値の最小値
				 * @param max 元のalpha値の最大値
				 * @param projection_min alpha値の最小値
				 * @param projection_max alpha値の最大値
				 */
				template <int min, int max, int projection_min, int projection_max,
						  typename selector, typename method_selector>
				class scaled_alpha_selector
				{
					typedef alpha_factor<selector, method_selector> stub_type;
					typedef scale_factor<min, max, projection_min, projection_max>
					scaler;

				public:
			
					template <typename src_itor_t,
							  typename dest_itor_t>
					aligned_wideword_type
					operator()(src_itor_t src,
							   dest_itor_t dest) const
					{
						return scaler()(stub_type()(src, dest));
					}
				};

				/**
				 * 対象の補値をアルファ値として扱うアルファファクタ
				 * @param selector srcかdestを指定するselector
				 * @param method_selector アルファ値を取り出すmethod_selector
				 */
				template <typename selector,
						  typename method_selector>
				class invert_alpha_factor
				{
				private:
					aligned_wideword_type base;

				public:
					invert_alpha_factor():
						base(_mm_set1_epi32(257))
					{}

					template <typename src_itor_t,
							  typename dest_itor_t>
					aligned_wideword_type operator()(src_itor_t src,
													 dest_itor_t dest) const
					{
						return _mm_sub_epi32(base, method_selector()(selector()(src, dest)));
					}
				};

				/**
				 * 写像スケーリングつきinvert_alpha_selector
				 * @param min 元のalpha値の最小値
				 * @param max 元のalpha値の最大値
				 * @param projection_min alpha値の最小値
				 * @param projection_max alpha値の最大値
				 */
				template <int min, int max, int projection_min, int projection_max,
						  typename selector, typename method_selector>
				class scaled_invert_alpha_selector
				{
					typedef invert_alpha_factor<selector, method_selector> stub_type;
					typedef scale_factor<min, max, projection_min, projection_max>
					scaler;
				public:
			
					template <typename src_itor_t,
							  typename dest_itor_t>
					aligned_wideword_type
					operator()(src_itor_t src,
							   dest_itor_t dest) const
					{
						return scaler()(stub_type()(src, dest));
					}
				};

				class full_transparent_alpha_factor
				{
				public:
					template <typename src_itor_t,
							  typename dest_itor_t>
					aligned_wideword_type
					operator()(src_itor_t,
							   dest_itor_t) const
					{
						return _mm_set1_epi32(1);
					}
				};

				/**
				 * 実行時にセットされた定数を返すalpha factor
				 */
				// {{{ constant_alpha_factor
				class constant_alpha_factor
				{
				private:
					const __m128i value;

				public:
					constant_alpha_factor():
						value(_mm_set1_epi32(256))
					{}

					constant_alpha_factor(const int value_):
					value(_mm_set1_epi32(value_))
					{}

					template <typename src_itor_t,
							  typename dest_itor_t>
					aligned_wideword_type
					operator()(src_itor_t,
							   dest_itor_t) const
					{
						return value;
					}
				};
				// }}}

				/**
				 * 実行時にセットされた定数の補数を返すalpha factor
				 */
				// {{{ invert_constant_alpha_factor
				class invert_constant_alpha_factor :
					public constant_alpha_factor
				{
				public:
					invert_constant_alpha_factor():
						constant_alpha_factor(1)
					{}

					invert_constant_alpha_factor(const int value_):
					constant_alpha_factor(257 - value_)
					{}
				};
				// }}}


				template <typename selector_type,
						  typename bit_get_method_type>
				class alpha_getter
				{
				private:
					selector_type selector;
					bit_get_method_type bit_get_method;

				public:
					alpha_getter():
						selector(),
						bit_get_method()
					{}

					template <typename src_itor_t,
							  typename dest_itor_t>
					aligned_wideword_type operator()(src_itor_t src,
													 dest_itor_t dest) const
					{
						aligned_wideword_type value =
							_mm_load_si128(
								reinterpret_cast<aligned_wideword_type*>(
									&*selector(src, dest)));
						return bit_get_method(value);
					}
				};

				template <typename selector_type, typename bit_get_method>
				class invert_alpha_getter
				{
				public:
					typedef typename bit_get_method::pixel_type pixel_type;
					typedef
					alpha_getter<selector_type, bit_get_method>
					alpha_getter_type;

				private:
					alpha_getter_type getter;
					aligned_wideword_type base_alpha;

					static aligned_wideword_type init_base_alpha()
					{
						return _mm_set1_epi16(255);
					}

				public:
					invert_alpha_getter():
						getter(),
						base_alpha(init_base_alpha())
					{}

					template <typename src_itor_t,
							  typename dest_itor_t>
					aligned_wideword_type operator()(src_itor_t src,
													 dest_itor_t dest) const
					{
						return _mm_sub_epi8(base_alpha,
											getter(src, dest));
					}
				};

				template <typename pixel_t>
				struct alpha_bits_get_method
				{
				public:
					typedef pixel_t pixel_type;

				private:
					aligned_wideword_type alpha_mask;

					static aligned_wideword_type get_mask() 
					{
						const int mask =
							0xff << (pixel_type::alpha_position * 8);
						return _mm_set1_epi32(mask);
					}

				public:
					alpha_bits_get_method():
						alpha_mask(get_mask())
					{}

					aligned_wideword_type operator()(
						aligned_wideword_type value) const
					{
						aligned_wideword_type alpha_bit = 
							_mm_srli_si128(
								_mm_and_si128(value, alpha_mask),
								pixel_type::alpha_position);
						
						return
							_mm_or_si128(alpha_bit,
										 _mm_slli_si128(alpha_bit, 2));
					}
				};
			}
		}
	}
}

#endif /* RISA_EXT_SSE2_PRIMITIVE_ALPHA_FACTOR_HPP_ */
