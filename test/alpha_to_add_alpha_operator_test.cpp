#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/operators/alpha_to_add_alpha_operator.hpp>
#include <risa_gl/pixel_store.hpp>
#include <risa_gl/pixel.hpp>
#include "range.hpp"

class alpha_to_add_alpha_operator_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(alpha_to_add_alpha_operator_test);
	CPPUNIT_TEST(to_add_alpha_test);
	CPPUNIT_TEST_SUITE_END();
public:
	void to_add_alpha_test()
	{
		risa_gl::pixel src, result;
		src = risa_gl::pixel(255, 255, 255, 256);

		risa_gl::operators::alpha_to_add_alpha_operator oper;
		oper(&src, &result);
		CPPUNIT_ASSERT(range<int>(result.get_red(), 255, 1));
		CPPUNIT_ASSERT(range<int>(result.get_green(), 255, 1));
		CPPUNIT_ASSERT(range<int>(result.get_blue(), 255, 1));
		CPPUNIT_ASSERT(range<int>(result.get_alpha(), 256, 1));

		src = risa_gl::pixel(255/4, 128/4, 64/4, 256/4);
		oper(&src, &result);
		CPPUNIT_ASSERT(range<int>(result.get_red(), 255/(4*4), 1));
		CPPUNIT_ASSERT(range<int>(result.get_green(), 128/(4*4), 1));
		CPPUNIT_ASSERT(range<int>(result.get_blue(), 64/(4*4), 1));
		CPPUNIT_ASSERT(range<int>(result.get_alpha(), 256/4, 1));
		
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( alpha_to_add_alpha_operator_test );
