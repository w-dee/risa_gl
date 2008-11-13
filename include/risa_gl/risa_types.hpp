#ifndef RISA_RISA_TYPES_HPP_
#define RISA_RISA_TYPES_HPP_

namespace risa_gl
{
	typedef unsigned char byte;
	typedef unsigned short word;
	typedef unsigned int dword;

	typedef unsigned char uint8;
	typedef unsigned short uint16;
	typedef unsigned int uint32;

	typedef signed char int8;
	typedef signed short int16;
	typedef signed int int32;

	template <typename T>
	struct type_traits
	{
		typedef typename T::value_type value_type;
	};

	template <typename T>
	struct type_traits<T*>
	{
		typedef T value_type;
	};
}

#endif /* RISA_RISA_TYPES_HPP_ */
