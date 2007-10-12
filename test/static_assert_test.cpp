#include <static_assert.hpp>
#include <pixel.hpp>

using namespace risa_gl;

int main()
{
	RISA_STATIC_ASSERT(sizeof(pixel) == 4);
	RISA_STATIC_ASSERT(sizeof(opaque) == 1);
	RISA_STATIC_ASSERT(sizeof(rgba) == 4);
	RISA_STATIC_ASSERT(sizeof(abgr) == 4);
#ifdef COMPILE_ERROR_ENABLE
	RISA_STATIC_ASSERT(sizeof(pixel) == 1);
#endif
	return 0;
}
