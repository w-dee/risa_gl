#include <static_assert.hpp>
#include <pixel.hpp>

using namespace risa_gl;

int main()
{
	RISA_STATIC_ASSERT(sizeof(pixel) == 4);
	RISA_STATIC_ASSERT(sizeof(brightness) == 1);
//	RISA_STATIC_ASSERT(sizeof(pixel) == 1);

	return 0;
}
