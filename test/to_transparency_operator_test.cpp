#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/operators/to_transparency_operator.hpp>
#include <risa_gl/pixel_store.hpp>
#include <risa_gl/pixel.hpp>
#include "range.hpp"

class to_transparency_operator_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(to_transparency_operator_test);
	CPPUNIT_TEST(to_transparency_test);
	CPPUNIT_TEST_SUITE_END();
public:
	void to_transparency_test()
	{
		risa_gl::pixel src, result;
		src = risa_gl::pixel(255/2, 255/2, 255/2, 256/2);

		risa_gl::operators::to_transparency_operator oper;
		oper(&src, &result);
		CPPUNIT_ASSERT(range<int>(result.get_red(), 255/2, 1));
		CPPUNIT_ASSERT(range<int>(result.get_green(), 255/2, 1));
		CPPUNIT_ASSERT(range<int>(result.get_blue(), 255/2, 1));
		CPPUNIT_ASSERT(range<int>(result.get_alpha(), 1, 1));

		src = risa_gl::pixel(255/4, 128/4, 64/4, 256/4);
		oper(&src, &result);
		CPPUNIT_ASSERT(range<int>(result.get_red(), 255/4, 3));
		CPPUNIT_ASSERT(range<int>(result.get_green(), 128/4, 1));
		CPPUNIT_ASSERT(range<int>(result.get_blue(), 64/4, 1));
		CPPUNIT_ASSERT(range<int>(result.get_alpha(), 1, 1));
		
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( to_transparency_operator_test );
