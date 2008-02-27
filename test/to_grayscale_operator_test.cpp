#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/operators/to_grayscale_operator.hpp>
#include <risa_gl/pixel.hpp>
#include <risa_gl/pixel_store.hpp>
#include "range.hpp"

class to_grayscale_operator_test : public CppUnit::TestFixture
{
private:
	CPPUNIT_TEST_SUITE(to_grayscale_operator_test);
	CPPUNIT_TEST(set_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void set_test()
	{
		risa_gl::pixel_store<risa_gl::pixel> source(16, 16);
		risa_gl::pixel_store<risa_gl::pixel> result(16, 16);

		std::fill(source.begin(), source.end(),
				  risa_gl::pixel(129, 66, 25, 256));
		risa_gl::operators::to_grayscale_operator oper;
		oper(source.begin(), result.begin());
		CPPUNIT_ASSERT(range(static_cast<int>(result.begin()->get_red()),
							 80, 3));
		CPPUNIT_ASSERT(range(static_cast<int>(result.begin()->get_green()),
							 80, 3));
		CPPUNIT_ASSERT(range(static_cast<int>(result.begin()->get_blue()),
							 80, 3));
		CPPUNIT_ASSERT(result.begin()->get_alpha() == 256);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( to_grayscale_operator_test );
