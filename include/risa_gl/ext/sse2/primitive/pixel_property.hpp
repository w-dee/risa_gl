#ifndef RISA_EXT_SSE2_PRIMITIVE_PIXEL_PROPERTY_HPP_
#define RISA_EXT_SSE2_PRIMITIVE_PIXEL_PROPERTY_HPP_

namespace risa_gl
{
	namespace ext
	{
		namespace sse2
		{
			namespace primitive
			{

				/**
				 * 何もしないsetter
				 */
				class nop_setter
				{
				public:
					template <typename result_itor_t>
					void operator()(result_itor_t, aligned_wideword_type) const
					{
					}
				};

				/**
				 * 実行時定数setter
				 */
				class dynamic_constant_setter
				{
				private:
					dynamic_constant_setter();
					const aligned_wideword_type value;

				public:
					dynamic_constant_setter(const dynamic_constant_setter& src):
						value(src.value)
					{}

					dynamic_constant_setter(const aligned_wideword_type value_):
						value(value_)
					{}

					template <typename result_itor_t>
					void operator()(result_itor_t result, aligned_wideword_type)
					{
						*result = value;
					}
				};

				/**
				 */
				class bit_setter
				{
				public:
					template <typename result_itor_t>
					void operator()(result_itor_t result,
									aligned_wideword_type value) const
					{
						// @todo movdqaやmovdにならんようなら命令呼び出
						// すラッパ用意する
						*result = value;
					}
				};

				/**
				 * 0値を取得するgetter
				 */
				class zero_getter
				{
				private:
					const aligned_wideword_type value;

					static aligned_wideword_type zero()
					{
						return _mm_setzero_si128();
					}
				public:
					zero_getter():
						value(zero())
					{}
			
					zero_getter(const zero_getter& src):
						value(src.value)
					{}

					template <typename src_itor_t,
							  typename dest_itor_t>
					aligned_wideword_type operator()(
						src_itor_t, dest_itor_t) const
					{
						return value;
					}
				};

				/**
				 * 実行時定数値を取得するgetter
				 */
				class dynamic_constant_getter
				{
				private:
					dynamic_constant_getter();
					const aligned_wideword_type value;
				public:
					dynamic_constant_getter(const dynamic_constant_getter& src):
						value(src.value)
					{}

					dynamic_constant_getter(const aligned_wideword_type value_):
						value(value_)
					{}

					template <typename src_itor_t,
							  typename dest_itor_t>
					aligned_wideword_type operator()(src_itor_t,
													 dest_itor_t) const
					{
						return value;
					}
				};

				/**
				 * ビット値を取得するgetter
				 */
				template <typename selector>
				class bits_getter
				{
				public:
					template <typename src_itor_t,
							  typename dest_itor_t>
					aligned_wideword_type operator()(
						src_itor_t src,
						dest_itor_t dest) const
					{
						return *(selector()(src, dest));
					}
				};

				/**
				 * selectorを利用して対象の
				 * 補値を取得するgetter
				 */
				template <typename selector>
				class invert_getter
				{
				private:
					vertical_not oper;

				public:
					template <typename src_itor_t,
							  typename dest_itor_t>
					aligned_wideword_type operator()(src_itor_t src,
													 dest_itor_t dest) const
					{
						return oper(*selector()(src, dest));
					}
				};

				template <typename function_t, typename stub_t>
				class functional_getter
				{
				public:
					typedef function_t function_type;
					typedef stub_t stub_type;

				private:
					function_type function;
					stub_type stub;

				public:
					functional_getter(const function_type& function_ =
									  function_type(),
									  const stub_type& stub_ = stub_type()):
						function(function_),
						stub(stub_)
					{}

					template <typename src_itor_t,
							  typename dest_itor_t>
					aligned_wideword_type operator()(src_itor_t src,
													 dest_itor_t dest) const
					{
						return function(stub(src, dest));
					}
				};
			}
		}
	}
}

#endif /* RISA_EXT_SSE2_PRIMITIVE_PIXEL_PROPERTY_HPP_ */
