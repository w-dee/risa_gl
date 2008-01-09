#ifndef RISA_MATRIX_HPP_
#define RISA_MATRIX_HPP_
#include <static_array.hpp>
#include <ostream>

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

			static elements_type initialize(const value_type value = 1)
			{
				elements_type result;
				for (size_t offset = 0; offset < result.size(); ++offset)
					result[offset] = static_cast<value_type>(0);

				if (max_rows == max_columns)
					for (int offset = 0; offset < max_rows; ++offset)
						result[offset + offset * max_columns] = value;

				return result;
			}
		public:
			matrix():
				elements(initialize())
			{}

			matrix(const value_type src):
				elements(initialize(src))
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

			matrix& negate()
			{
				for (typename elements_type::iterator itor = elements.begin();
					 itor != elements.end(); ++itor)
					*itor = -*itor;

				return *this;
			}

			matrix get_negate() const
			{
				return matrix(*this).negate();
			}

			value_type& operator()(const int row, const int column = 0)
			{
				return elements[row * max_columns + column];
			}

			const value_type& operator()(const int row,
										 const int column = 0) const
			{
				return elements[row * max_columns + column];
			}

			template <typename destination_matrix_type>
			matrix<value_type, max_rows, destination_matrix_type::max_columns>
			operator*(const destination_matrix_type& rhs) const
			{
				typedef destination_matrix_type rhs_type;
				typedef matrix<value_type, max_rows, rhs_type::max_columns>
					result_matrix_type;
				
				result_matrix_type result(0);

				for (int row = 0; row != max_rows; ++row)
					for (int column = 0;
						 column != rhs_type::max_columns; ++column)
						for (int i = 0; i != max_columns; ++i)
							result(row, column) +=
								(*this)(row, i) * rhs(i, column);

				return result;
			}

			matrix& operator*=(const matrix& rhs)
			{
				return *this = this->operator*(rhs);
			}

			matrix& operator+=(const matrix& rhs)
			{
				typename elements_type::iterator lhs_itor = elements.begin();
				typename elements_type::const_iterator rhs_itor =
					rhs.elements.begin();

				while (lhs_itor != elements.end())
					*lhs_itor++ += *rhs_itor++;

				return *this;
			}

			matrix operator+(const matrix& rhs) const
			{
				return matrix(*this).operator+=(rhs);
			}

			matrix& operator-=(const matrix& rhs)
			{
				return this->operator+=(rhs.get_negate());
			}

			matrix operator-(const matrix& rhs) const
			{
				return matrix(*this).operator-=(rhs);
			}

			bool operator==(const matrix& src) const
			{
				typename elements_type::const_iterator lhs_itor =
					elements.begin();
				typename elements_type::const_iterator rhs_itor =
					src.elements.begin();

				while (lhs_itor != elements.end())
					if (*lhs_itor++ != *rhs_itor++)
						return false;

				return true;
			}

			friend std::ostream&
			operator<<(std::ostream& out, const matrix& mat)
			{
				for (int row = 0; row < max_rows; ++row)
				{
					out << "[ ";
					for ( int column = 0; column < max_columns; ++column)
						out << (column == 0 ? "" : ", ") << mat(row,column);
					out << "] " << std::endl;
				}
				return out;
			}
		};
	}
}

#endif /* RISA_MATRIX_HPP_ */
