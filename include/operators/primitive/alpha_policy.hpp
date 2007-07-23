
namespace risa_gl
{
	namespace primitive
	{
		/**
		 * アルファ値非計算ポリシー
		 */
		class not_calculate_policy
		{
		public:
			template <typename result_itor_t,
					  typename src_itor_t,
					  typename dest_itor_t>
			void operator()(result_itor_t,
							src_itor_t,
							dest_itor_t) const
			{}
		};

		/**
		 * アルファ値計算ポリシー
		 * @param calculator
		 */
		template <typename calculator>
		class alpha_calculate_policy
		{
		public:
			template <typename result_itor_t,
					  typename src_itor_t,
					  typename dest_itor_t>
			void operator()(result_itor_t result,
							src_itor_t src,
							dest_itor_t dest) const
			{
				result->set_alpha(calculator()(src, dest));
			}
		};

	};
};
