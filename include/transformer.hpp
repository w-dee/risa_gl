#ifndef RISA_TRANSFORMER_HPP_
#define RISA_TRANSFORMER_HPP__

#include <rectangle.hpp>
#include <iterator.hpp>
#include <math/vector.hpp>
#include <vector>

namespace risa_gl
{
	class linear_transformer
	{
	private:
		/// @todo ほんとはtemplateベースのコンパイル時固定長配列のほうが・・・
		typedef std::vector<std::vector<float> > matrix_t;
		matrix_t matrix;

		static matrix_t initial()
		{
			matrix_t result(4);
			std::vector<float> line;

			line.resize(4);

			for (int row = 0; row < 4; ++row)
			{
				for (int column = 0; column < 4; ++column)
					line[column] = (row == column ? 1.0f : 0.0f);

				result[row] = line;
			}
			
			return result;
		}

		static matrix_t initial(const float matrces[4][4])
		{
			matrix_t result(4);
			std::vector<float> line;

			for (int row = 0; row < 4; ++row)
			{
				result[row].resize(4);
				for (int column = 0; column < 4; ++column)
					result[row][column] = matrces[row][column];
			}
			
			return result;
			
		}

	public:
		linear_transformer():
			matrix(initial())
		{}
		linear_transformer(const float matrices[4][4]):

			matrix(initial(matrices))
		{}

		linear_transformer(const linear_transformer& src):
			matrix(src.matrix)
		{}

		~linear_transformer()
		{}

		math::vector2 operator*(const math::vector2& coord) const
		{
			return math::vector2(
				coord.x * matrix[0][0] + coord.y * matrix[1][0],
				coord.x * matrix[0][1] + coord.y * matrix[1][1]);
		}

		math::vector3 operator*(const math::vector3& coord) const
		{
			return math::vector3(
				coord.x * matrix[0][0] +
				coord.y * matrix[1][0] +
				coord.z * matrix[2][0],
				coord.x * matrix[0][1] +
				coord.y * matrix[1][1] +
				coord.z * matrix[2][1],
				coord.x * matrix[0][2] +
				coord.y * matrix[1][2] +
				coord.z * matrix[2][2]);
		}

		math::vector4 operator*(const math::vector4& coord) const
		{
			return math::vector4(
				coord.x * matrix[0][0] + coord.y * matrix[1][0] +
				coord.z * matrix[2][0] + coord.w * matrix[3][0],
				coord.x * matrix[0][1] + coord.y * matrix[1][1] +
				coord.z * matrix[2][1] + coord.w * matrix[3][1],
				coord.x * matrix[0][2] + coord.y * matrix[1][2] +
				coord.z * matrix[2][2] + coord.w * matrix[3][2],
				coord.x * matrix[0][3] + coord.y * matrix[1][3] +
				coord.z * matrix[2][3] + coord.w * matrix[3][3]);
		}
	};
}


#endif /* RISA_ITERATOR_HPP_ */
