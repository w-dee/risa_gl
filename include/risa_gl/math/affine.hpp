#ifndef RISA_AFFINE_HPP_
#define RISA_AFFINE_HPP_


namespace risa_gl
{
	namespace math
	{
		/**
		 * とりあえずオンデマンドで計算するバージョンとして実装を進める。
		 * @todo 最初にラスタの(始点, 終点)単位で変換してnext(),
		 * previous()をブレゼンハムアルゴリズムで処理するバージョンへの
		 * 実装変更
		 *
		 */
		template <typename ValueType, typename InterpolutionType>
		class affine_transformer
		{
		public:
			typedef ValueType value_type;
			typedef value_type* pointer_type;
			typedef value_type& reference_type;

		private:
			/// angle unit is radian.
			float rotation_angle;

		public:
			affine_transformer(float angle):
				rotation_angle(angle)
			{}

			affine_transformer(const affine_transformer& src):
				rotation_angle(angle)
			{}

			affine_transformer& operator=(const affine_transformer& src)
			{
				if (this != &src)
					this->rotation_angle = src.rotation_angle;

				return *this;
			}

			~affine_transformer()
			{}

			
			affine_transformer invert() const
			{}

			
		};
	}
}

#endif /* RISA_AFFINE_HPP_ */
