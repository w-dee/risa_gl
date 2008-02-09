#ifndef RISA_ALLOCATE_IMLEMENTS_HPP_
#define RISA_ALLOCATE_IMLEMENTS_HPP_

#include <risa_gl/risa_types.hpp>
#ifdef _WIN32
#include <windows.h>
#endif /* _WIN32 */

namespace risa_gl
{
	struct default_allocate_implements
	{
		static risa_gl::byte* allocate(size_t size)
		{
			return new risa_gl::byte[size];
		}

		static void deallocate(risa_gl::byte* p)
		{
			delete[] p;
		}
	};

#ifdef _WIN32
	struct global_alloc_allocate_implements
	{
		static risa_gl::byte* allocate(size_t size)
		{
			return
				reinterpret_cast<risa_gl::byte*>(
					GlobalAlloc(GMEM_FIXED, size));
		}

		static void deallocate(risa_gl::byte* p)
		{
			GlobalFree(p);
		}
	};
#endif /* _WIN32 */

}

#endif /* RISA_ALLOCATE_IMLEMENTS_HPP_ */
