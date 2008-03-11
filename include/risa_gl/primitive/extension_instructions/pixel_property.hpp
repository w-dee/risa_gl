#ifndef RISA_PRIMITIVE_EXTENSION_INSTRUCTION_PIXEL_PROPERTY_HPP_
#define RISA_PRIMITIVE_EXTENSION_INSTRUCTION_PIXEL_PROPERTY_HPP_
#include <risa_gl/primitive/selector.hpp>

namespace risa_gl
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
			void operator()(result_itor_t, word_type) const
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
			const word_type value;

		public:
			dynamic_constant_setter(const dynamic_constant_setter& src):
				value(src.value)
			{}

			dynamic_constant_setter(const word_type value_):
				value(value_)
			{}

			template <typename result_itor_t>
			void operator()(result_itor_t result, word_type)
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
							word_type value) const
			{
				// @todo movdqaやmovdにならんようなら命令呼び出すラッパ
				// 用意する
				*result = value;
			}
		};

		/**
		 * 0値を取得するgetter
		 */
		class zero_getter
		{
		private:
			const word_type value;

		public:
			zero_getter():
				value(converter().zero())
			{}
			
			zero_getter(const zero_getter& src):
				value(src.value)
			{}

			template <typename src_itor_t,
					  typename dest_itor_t>
			word_type operator()(src_itor_t, dest_itor_t) const
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
			const word_type value;
		public:
			dynamic_constant_getter(const dynamic_constant_getter& src):
				value(src.value)
			{}

			dynamic_constant_getter(const word_type value_):
				value(value_)
			{}

			template <typename src_itor_t,
					  typename dest_itor_t>
			word_type operator()(src_itor_t,
								 dest_itor_t) const
			{
				return value;
			}
		};

		/**
		 */
		template <typename selector>
		class bits_getter
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			const word_type& operator()(src_itor_t src,
										dest_itor_t dest) const
			{
				return *selector()(src, dest);
			}
		};

		/**
		 * selectorを利用して対象をbit_representationメソッドを使って
		 * 補値を取得するgetter
		 */
		template <typename selector>
		class invert_getter
		{
		private:
			virtical_not oper;

		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			word_type operator()(src_itor_t src,
								 dest_itor_t dest) const
			{
				return oper(*selector()(src, dest));
			}
		};

		template <typename selector_t, typename method_selector_t>
		class alpha_getter
		{
		private:
			selector_t selector;
			meothod_selector_t method_selector;

		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			word_type operator()(src_itor_t src,
								 dest_itor_t dest) const
			{
				return method_selector(selector(src, dest));
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
			functional_getter(const function_type& function_ = function_type(),
							  const stub_type& stub_ = stub_type()):
				function(function_),
				stub(stub_)
			{}

			template <typename src_itor_t,
					  typename dest_itor_t>
			word_type operator()(src_itor_t src,
								 dest_itor_t dest) const
			{
				return function(stub(src, dest));
			}
		};
	}
}

#endif /* RISA_PRIMITIVE_EXTENSION_INSTRUCTION_PIXEL_PROPERTY_HPP_ */
