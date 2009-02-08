#ifndef EXTRACTOR_HPP_
#define EXTRACTOR_HPP_

#include <risa_gl/nv/pixel_traits.hpp>
#include <risa_gl/nv/template_functions.hpp>

/**
 * 型変換および抽出を行うファンクタ
 *
 * 画素型(risa_gl::pixel_type)や画素集合型
 * (risa_gl::fragments<risa_gl::pixel_type>)から計算単位データ型へ変換
 * を行う。その際、抽出が必要であればそれも行う(アルファのみ取り出し等)
 */
namespace extractor
{
	/**
	 * 引数をそのまま抽出するエキストラクタ
	 */
	template <typename pixel_value_t>
	struct identity
	{
		typedef pixel_value_t result_type;
		
		template <typename input_type>
		input_type operator()(input_type src) const
		{
			return src;
		}
	};

	template <template <typename> class composite_fx,
			  template <typename> class composite_gx>
	struct composite
	{
		template <typename pixel_value_t>
		struct type
		{
			typedef
			 typename composite_fx<pixel_value_t>::result_type result_type;

			template <typename input_type>
			result_type
			operator()(input_type src) const
			{
				composite_fx<input_type> fx;
				composite_gx<input_type> gx;
				return fx(gx(src));
			}
		};
	};

	/**
	 * 参照外しをおこなう抽出子
	 */
	template <typename pixel_value_t>
	struct dereference
	{
		typedef pixel_value_t result_type;
		
		template <typename input_type>
		result_type operator()(input_type src) const
		{
			return *reinterpret_cast<pixel_value_t*>(src);
		}
	};

	/**
	 * 引数のビットを再解釈して値として捕らえる抽出子
	 */
	template <typename pixel_value_t>
	struct reinterpretor
	{
		typedef pixel_value_t result_type;

		template <typename input_type>
		result_type operator()(input_type src) const
		{
			return *reinterpret_cast<result_type*>(&src);
		}
	};

	/**
	 * 単独要素(channel)を抽出するエキストラクタ
	 * @args pixel_value_t 処理対象となるピクセル型
	 * @args channel_position 抽出するchannelの位置オフセット
	 */
	template <typename pixel_value_t, int channel_position>
	struct factor
	{
		typedef pixel_value_t result_type;
		typedef reinterpretor<pixel_value_t> reinterpretor_type;
		
		template <typename input_type>
		pixel_value_t operator()(input_type src) const
		{
			typedef	traits::pixel_traits<result_type,
				channel_position,
				pixel_value_t> traits_type;

			reinterpretor_type reinterpretor;
			traits_type traits;

			return traits.factor_extract(reinterpretor(src));
		}
	};

	/**
	 * red channelの取り出し
	 */
	template <typename pixel_value_t, typename pixel_type_t>
	struct red_factor :
		public factor<pixel_value_t, pixel_type_t::red_position>
	{};

	/**
	 * green channelの取り出し
	 */
	template <typename pixel_value_t, typename pixel_type_t>
	struct green_factor :
		public factor<pixel_value_t, pixel_type_t::green_position>
	{};

	/**
	 * blue channelの取り出し
	 */
	template <typename pixel_value_t, typename pixel_type_t>
	struct blue_factor :
		public factor<pixel_value_t, pixel_type_t::blue_position>
	{};

	/**
	 * alpha channelの取り出し
	 */
	template <typename pixel_value_t, typename pixel_type_t>
	struct alpha_factor :
		public factor<pixel_value_t, pixel_type_t::alpha_position>
	{};

	template <typename pixel_value_t>
	struct channel_element_factor :
		public factor<pixel_value_t, 0>
	{};


	/**
	 * コンパイル時定数の取り出し
	 */
	template <unsigned int pixel_value>
	struct constant_value
	{
		template <typename input_type>
		input_type operator()(input_type) const
		{
			using template_functions::filler;

			return
				filler<input_type, unsigned int, pixel_value>::value();
		}
	};

	/**
	 * 実行時に値を束縛する定数抽出子
	 */
	template <typename value_type>
	struct dynamic_value
	{
		const value_type value;

		dynamic_value(value_type value_):
			value(value_)
		{}

		template <typename input_type>
		value_type operator()(input_type) const
		{
			return value;
		}
	};
}

#endif /* EXTRACTOR_HPP_ */
