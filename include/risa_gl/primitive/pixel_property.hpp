#ifndef RISA_PIXEL_GETTER_HPP_
#define RISA_PIXEL_GETTER_HPP_
#include <risa_gl/risa_types.hpp>
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
			void operator()(result_itor_t, risa_gl::uint32) const
			{
			}
		};

		/**
		 * コンパイル時定数setter
		 */
		template <risa_gl::uint32 value>
		class constant_setter
		{
		public:
			template <typename result_itor_t>
			void operator()(result_itor_t result, risa_gl::uint32) const
			{
				result->set_bit_representation(value);
			}
		};

		/**
		 * 実行時定数setter
		 */
		class dynamic_constant_setter
		{
		private:
			dynamic_constant_setter();
			const risa_gl::uint32 value;
		public:
			dynamic_constant_setter(const dynamic_constant_setter& src):
				value(src.value)
			{}

			dynamic_constant_setter(const risa_gl::uint32 value_):
				value(value_)
			{}

			template <typename result_itor_t>
			void operator()(result_itor_t result, risa_gl::uint32)
			{
				result->set_bit_representation(value);
			}
		};

		/**
		 * set_bit_representationを使って値を設定する
		 */
		class bit_setter
		{
		public:
			template <typename result_itor_t>
			void operator()(result_itor_t result,
							risa_gl::uint32 value) const
			{
				result->set_bit_representation(value);
			}
		};

		/**
		 * 0値を取得するgetter
		 */
		class zero_getter
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t, dest_itor_t) const
			{
				return 0;
			}
		};

		/**
		 * コンパイル定数値を取得するgetter
		 */
		template <risa_gl::uint32 pixel_bits>
		class constant_getter
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t, dest_itor_t) const
			{
				return pixel_bits;
			}
		};

		/**
		 * 実行時定数値を取得するgetter
		 */
		class dynamic_constant_getter
		{
		private:
			dynamic_constant_getter();
			const risa_gl::uint32 value;
		public:
			dynamic_constant_getter(const dynamic_constant_getter& src):
				value(src.value)
			{}

			dynamic_constant_getter(const risa_gl::uint32 value_):
				value(value_)
			{}

			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t,
									   dest_itor_t) const
			{
				return value;
			}
		};

		/**
		 * selectorを利用して対象をbit_representationメソッドを使って
		 * 値を取得するgetter
		 */
		template <typename selector>
		class bits_getter
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t src,
									   dest_itor_t dest) const
			{
				return selector()(src, dest)->get_bit_representation();
			}
		};

		/**
		 * selectorを利用して対象をbit_representationメソッドを使って
		 * 補値を取得するgetter
		 */
		template <typename selector>
		class invert_getter
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t src,
									   dest_itor_t dest) const
			{
				return ~selector()(src, dest)->get_bit_representation();
			}
		};

		template <typename selector, typename method_selecter>
		class alpha_getter
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t src,
									   dest_itor_t dest) const
			{
				return method_selecter()(selector()(src, dest));
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
			risa_gl::uint32 operator()(src_itor_t src,
									   dest_itor_t dest) const
			{
				typename src_itor_t::value_type temp;
				temp.set_bit_representation(stub(src, dest));
				return function(temp);
			}
		};
	}
}

#endif /* RISA_PIXEL_GETTER_HPP_ */
