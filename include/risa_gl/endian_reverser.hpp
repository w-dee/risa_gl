#ifndef RISA_ENDIAN_REVERSER_HPP_
#define RISA_ENDIAN_REVERSER_HPP_


namespace risa_gl
{
	template <int value_, typename T = int, int size = sizeof(T)>
	struct byte_endian_reverser
	{
		enum {
			msb = (value_ >> ((size - 1) * 8)),
			other = (value_ - (msb << ((size - 1) * 8))),
			reverse_value =
			(byte_endian_reverser<other, T, size-1>::reverse_value << 8) +
			byte_endian_reverser<other, T, size-1>::msb,
			value = (reverse_value << 8) + msb
		};
	};

	template <int value_, typename T>
	struct byte_endian_reverser<value_, T, 1>
	{
		enum
		{
			msb = value_,
			other = 0,
			reverse_value = 0,
			value = msb
		};
	};

	template <int value_, typename T = int, int length = sizeof(T) * 8>
	struct bit_endian_reverser
	{
        enum {
			lsb = (value_ & 1),
			other = ((value_ - lsb) >> 1) & ~(1 << (length - 1)),
			value = (lsb << (length - 1)) |
			bit_endian_reverser<other, T, length-1>::value
        };
	};

	template <int value_, typename T>
	struct bit_endian_reverser<value_, T, 1>
	{
		enum {
			lsb = 0,
			other = 0,
			value = lsb
		};
	};

}

#endif /* RISA_ENDIAN_REVERSER_HPP_ */
