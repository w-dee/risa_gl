
namespace risa_gl
{
	namespace primitive
	{
		class not_calculate
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

		template <typename calulator>
		class alpha_calculate
		{
		public:
			template <typename result_itor_t,
					  typename src_itor_t,
					  typename dest_itor_t>
			void operator()(result_itor_t,
							src_itor_t,
							dest_itor_t) const
			{
				result->set_alpha(calculator()(src, dest));
			}
		};

	};
};
