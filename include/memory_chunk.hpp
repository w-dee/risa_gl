#ifndef RISA_MEMORY_CHUNK_HPP_
#define RISA_MEMORY_CHUNK_HPP_

#include "risa_types.hpp"

namespace risa_gl {
	template <size_t chunk_size>
	class memory_chunk
	{
	private:
		byte chunk_data[chunk_size];

	public:
		memory_chunk():
			chunk_data()
		{}

		~memory_chunk()
		{}

		byte* get()
		{
			return reinterpret_cast<byte*>(this);
		}
		
		byte* const get() const
		{
			return reinterpret_cast<byte* const>(this);
		}
	};
};
#endif /* RISA_MEMORY_CHUNK_HPP_ */
