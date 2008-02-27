#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/operators/set_color_operator.hpp>
#include <risa_gl/pixel.hpp>

class set_color_operator_test : public CppUnit::TestFixture
{
private:
	CPPUNIT_TEST_SUITE(set_color_operator_test);
	CPPUNIT_TEST(set_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void set_test()
	{
		risa_gl::pixel source(129, 66, 25, 256);
		risa_gl::pixel result;

		risa_gl::operators::set_color_operator oper(
			risa_gl::pixel(128, 128, 128));
		oper(&source, &result);

		CPPUNIT_ASSERT(result.get_red() == 128);
		CPPUNIT_ASSERT(result.get_green() == 128);
		CPPUNIT_ASSERT(result.get_blue() == 128);
		CPPUNIT_ASSERT(result.get_alpha() == 256);

	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( set_color_operator_test );
