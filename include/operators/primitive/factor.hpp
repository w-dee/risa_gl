#ifndef RISA_FACTOR_HPP_
#define RISA_FACTOR_HPP_

namespace risa_gl
{
	namespace primitive
	{
		/*
		 * ファクターテンプレート
		 */

		/**
		 * identity 変化させない値を返す
		 */
		class identity_factor
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			word operator()(src_itor_t src,
							dest_itor_t dest)
			{
				return 256;
			}
		};

		/**
		 * zero 値をゼロにする
		 */
		class zero_factor
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			word operator()(src_itor_t src,
							dest_itor_t dest)
			{
				return 0;
			}
		};

		/**
		 * ソースのアルファ値を返す
		 */
		class source_alpha_factor
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			word operator()(src_itor_t src,
							dest_itor_t)
			{
				return src->get_alpha();
			}			
		};

		/**
		 * ソースのアルファ値を不透明値から引いて返す
		 */
		class one_minus_source_alpha_factor
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			word operator()(src_itor_t src,
							dest_itor_t)
			{
				return 256 - src->get_alpha();
			}			
		};

		/**
		 * デスティネーションのアルファ値を返す
		 */
		class destination_alpha_factor
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			word operator()(src_itor_t,
							dest_itor_t destination)
			{
				return destination->get_alpha();
			}
		};

		/**
		 * デスティネーションのアルファ値を不透明値から引いて返す
		 */
		class one_minus_destination_alpha_factor
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			word operator()(src_itor_t,
							dest_itor_t destination)
			{
				return 256 - destination->get_alpha();
			}
		};
	};
};
#endif /* RISA_FACTOR_HPP_ */
