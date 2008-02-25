#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/operators/set_opacity_operator.hpp>
#include <risa_gl/pixel.hpp>

class set_opacity_operator_test : public CppUnit::TestFixture
{
private:
	CPPUNIT_TEST_SUITE(set_opacity_operator_test);
	CPPUNIT_TEST(set_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void set_test()
	{
		risa_gl::pixel source(129, 66, 25, 256);
		risa_gl::pixel result;

		risa_gl::operators::set_opacity_operator oper(129);
		oper(&source, &result);

		CPPUNIT_ASSERT(source.get_red() == result.get_red());
		CPPUNIT_ASSERT(source.get_green() == result.get_green());
		CPPUNIT_ASSERT(source.get_blue() == result.get_blue());
		CPPUNIT_ASSERT(source.get_alpha() != result.get_alpha());
		CPPUNIT_ASSERT(result.get_alpha() == 129);

	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( set_opacity_operator_test );
