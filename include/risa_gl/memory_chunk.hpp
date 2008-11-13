#ifndef RISA_MEMORY_CHUNK_HPP_
#define RISA_MEMORY_CHUNK_HPP_

#include <risa_gl/risa_types.hpp>

namespace risa_gl {
	template <size_t chunk_size>
	struct memory_chunk
	{
		byte chunk_data[chunk_size];

		byte* get()
		{
			return reinterpret_cast<byte*>(this);
		}
		
		byte* const get() const
		{
			return reinterpret_cast<byte* const>(this);
		}

		byte& operator[](int offset)
		{
			return chunk_data[offset];
		}

		int operator[](int offset) const
		{
			return chunk_data[offset];
		}
	};
}
#endif /* RISA_MEMORY_CHUNK_HPP_ */
