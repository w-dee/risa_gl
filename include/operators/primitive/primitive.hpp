#ifndef RISA_PRIMITIVE_HPP_
#define RISA_PRIMITIVE_HPP_
#include "iterator.hpp"

namespace risa_gl
{
	namespace primitives
	{

		/**
		 *・clear
		 *色、透過成分ともに初期化。
		 *Cd = 0
		 *Ad = 0
		 */
		class clear
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t,
							dest_itor_t,
							result_itor_t result) const
			{
				*result = typename result_itor_t::value_type(0, 0, 0, 0);
			}
		};

		/**
		 * ・src
		 * ソースの成分をコピー
		 * Cd = Cs
		 * Ad = As
		 */
		class source
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							dest_itor_t,
							result_itor_t result) const
			{
				*result = *src;
			}
		};

		/**
		 * ・dest
		 * ディスティネーションの成分をコピー
		 * Cd = Cd
		 * Ad = Ad
		 */
		class destination
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t,
							dest_itor_t dest,
							result_itor_t result) const
			{
				*result = *dest;
			}
		};

		/**
		 * ・src over
		 * ディスティネーションの上にソースをアルファブレンドでコピー
		 * # porter-duff source over destination rule.
		 * Cd = Cs + Cd*(1-As)
		 * Ad = As + Ad*(1-As)
		 */
		class source_over
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							dest_itor_t dest,
							result_itor_t result) const
			{
				const float fd = (255 - src->get_alpha()) / (255.0f * 2.0f);
				result->set_red((src->get_red() >> 1) +
								dest->get_red() * fd);
				result->set_green((src->get_green() >> 1) +
								  dest->get_green() * fd);
				result->set_blue((src->get_blue() >> 1) +
								 dest->get_blue() * fd);
				result->set_alpha((src->get_alpha() >> 1) +
								  dest->get_alpha() * fd);
			}
		};

		/**
		 * ・dest over
		 * ソースの上にディスティネーションをアルファブレンドでコピー
		 * src overのパラメータを転置するだけ
		 * # porter-duff destination over source rule.
		 * Fs = (1-Ad), Fd=1
		 * Cd = Cs*(1-Ad) + Cd
		 * Ad = As*(1-Ad) + Ad
		 */
		class destination_over
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							dest_itor_t dest,
							result_itor_t result) const
			{
				const float fs = (255 - dest->get_alpha()) / (255.0f * 2.0f);
				result->set_red(src->get_red() * fs +
								(dest->get_red() >> 1));
				result->set_green(src->get_green() * fs +
								  (dest->get_green() >> 1));
				result->set_blue(src->get_blue() * fs +
								 (dest->get_blue() >> 1));
				result->set_alpha(src->get_alpha() * fs +
								  (dest->get_alpha() >> 1));
			}
		};

		/**
		 * ・src in
		 * ソースをディスティネーションのアルファ成分で処理してコピー
		 * # porter-duff source in destination rule.
		 * Fs = Ad, Fd = 0
		 * Cd = Cs*Ad
		 * Ad = As*Ad
		 */
		class source_in
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							dest_itor_t dest,
							result_itor_t result) const
			{
				const float fs = dest->get_alpha() / 255.0f;
				result->set_red(src->get_red() * fs);
				result->set_green(src->get_green() * fs);
				result->set_blue(src->get_blue() * fs);
				result->set_alpha(src->get_alpha() * fs);
			}
		};

		/**
		 * ・dest in
		 * ディスティネーションをソースのアルファ成分で処理してコピー
		 * src inのパラメータ置換で実装可能
		 * # porter-duff destination in source rule.
		 * Fs = 0, Fd = As
		 * Cd = Cd*As
		 * Ad = Ad*As
		 */
		class destination_in
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							dest_itor_t dest,
							result_itor_t result) const
			{
				const float fd = src->get_alpha() / 255.0f;
				result->set_red(dest->get_red() * fd);
				result->set_green(dest->get_green() * fd);
				result->set_blue(dest->get_blue() * fd);
				result->set_alpha(dest->get_alpha() * fd);
			}
		};

		/**
		 * ・src out
		 * # porter-duff source held out by destination rule.
		 * Fs = (1-Ad), Fd = 0
		 * Cd = Cs*(1-Ad)
		 * Ad = As*(1-Ad)
		 */
		class source_out
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							dest_itor_t dest,
							result_itor_t result) const
			{
				const float fs = (255 - dest->get_alpha()) / 255.0f;
				result->set_red(src->get_red() * fs);
				result->set_green(src->get_green() * fs);
				result->set_blue(src->get_blue() * fs);
				result->set_alpha(src->get_alpha() * fs);
			}
		};

		/**
		 * ・dest out
		 * porter-duff destination held out by source rule.
		 * Fs = 0, Fd = (1-As)
		 * Cd = Cd*(1-As)
		 * Ad = Ad*(1-As)
		 */
		class destination_out
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							dest_itor_t dest,
							result_itor_t result) const
			{
				const float fs = (255 - src->get_alpha()) / 255.0f;
				result->set_red(dest->get_red() * fs);
				result->set_green(dest->get_green() * fs);
				result->set_blue(dest->get_blue() * fs);
				result->set_alpha(dest->get_alpha() * fs);
			}
		};

		/**
		 * ・src atop
		 * # porter-duff source atop destination rule.
		 * Fs = Ad, Fd = (1-As)
		 * Cd = Cs*Ad + Cd*(1-As)
		 * Ad = As*Ad + Ad*(1-As) = Ad
		 */
		class source_atop
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							dest_itor_t dest,
							result_itor_t result) const
			{
				const float fs = dest->get_alpha() / 255.0f;
				const float fd = (255 - src->get_alpha()) / 255.0f;

				result->set_red((src->get_red() >> 1) * fs +
								(dest->get_red() >> 1) * fd);
				result->set_green((src->get_green() >> 1) * fs +
								  (dest->get_green() >> 1) * fd);
				result->set_blue((src->get_blue() >> 1) * fs +
								 (dest->get_blue() >> 1) * fd);
				result->set_alpha(dest->get_alpha());
			}
		};

		/**
		 * ・Dest Atop
		 * # porter-duff destination atop source rule.
		 * Fs = (1-Ad), Fd = As
		 * Cd = Cs*(1-Ad) + Cd*As
		 * Ad = As*(1-Ad) + Ad*As = As
		 */
		class destination_atop
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							dest_itor_t dest,
							result_itor_t result) const
			{
				const float fs = (255 - dest->get_alpha()) / 255.0f;
				const float fd = src->get_alpha() / 255.0f;

				result->set_red((src->get_red() >> 1) * fs +
								(dest->get_red() >> 1) * fd);
				result->set_green((src->get_green() >> 1) * fs +
								  (dest->get_green() >> 1) * fd);
				result->set_blue((src->get_blue() >> 1) * fs +
								 (dest->get_blue() >> 1) * fd);
				result->set_alpha(src->get_alpha());
			}
		};

		/**
		 * ・xor
		 * # porter-duff source xor destination rule.
		 * Fs=(1-Ad), Fd=(1-As)
		 * Cd = Cs*(1-Ad) + Cd*(1-As)
		 * Ad = As*(1-Ad) + Ad*(1-As)
		 */
		class exclusive_or
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							dest_itor_t dest,
							result_itor_t result) const
			{
				const float fs = (255 - dest->get_alpha()) / 255.0f * 2.0f;
				const float fd = (255 - src->get_alpha()) / 255.0f * 2.0f;

				result->set_red(src->get_red() * fs +
								dest->get_red() * fd);
				result->set_green(src->get_green() * fs +
								  dest->get_green() * fd);
				result->set_blue(src->get_blue() * fs +
								 dest->get_blue() * fd);
				result->set_alpha(src->get_alpha() * fs +
								  dest->get_alpha() * fd);
			}
		};
	};
};

#endif /* RISA_PRIMITIVE_HPP_ */
