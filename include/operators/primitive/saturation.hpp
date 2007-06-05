#ifndef RISA_PRIMITIVE_SATURATION_HPP_
#define RISA_PRIMITIVE_SATURATION_HPP_

namespace risa_gl {
	namespace primitive {
		/**
		 * �O�a���Z�֐�
		 * @param value ���Z����
		 * @return �O�a������̐��l
		 */
		byte saturation(int value)
		{
			if (value > 255)
				return static_cast<byte>(255);
			return static_cast<byte>(value);
		};
	};
};

#endif /* RISA_PRIMITIVE_SATURATION_HPP_ */
