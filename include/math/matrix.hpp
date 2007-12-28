#ifndef RISA_MATRIX_HPP_
#define RISA_MATRIX_HPP_
#include <static_array.hpp>

namespace risa_gl
{
	namespace math
	{
		template <typename BaseType, int RowSize, int ColumnSize>
		class matrix
		{
		public:
			enum
			{
				max_rows = RowSize,
				max_columns = ColumnSize,
				max_elements = RowSize * ColumnSize
			};
			
			typedef BaseType value_type;
			typedef
			risa_gl::static_array<value_type, max_elements>	elements_type;

		private:

			elements_type elements;

			static elements_type initialize()
			{
				elements_type result = { 1, 0, 0, 0,
										 0, 1, 0, 0,
										 0, 0, 1, 0,
										 0, 0, 0, 1 };

				return result;
			}
		public:
			matrix():
				elements(initialize())
			{}

			matrix(const elements_type src):
				elements(src)
			{}

			matrix(const matrix& src):
				elements(src.elements)
			{}

			const elements_type& get_elements() const
			{
				return elements;
			}
		};
	}
}

#endif /* RISA_MATRIX_HPP_ */
