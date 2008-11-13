#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/operators/add_alpha_to_alpha_operator.hpp>
#include <risa_gl/pixel_store.hpp>
#include <risa_gl/pixel.hpp>
#include "range.hpp"

class add_alpha_to_alpha_operator_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(add_alpha_to_alpha_operator_test);
	CPPUNIT_TEST(to_alpha_test);
	CPPUNIT_TEST_SUITE_END();
public:
	void to_alpha_test()
	{
		risa_gl::pixel src, result;
		src = risa_gl::pixel(255/2, 255/2, 255/2, 256/2);

		risa_gl::operators::add_alpha_to_alpha_operator oper;
		oper(&src, &result);
		CPPUNIT_ASSERT(range<int>(result.get_red(), 255, 1));
		CPPUNIT_ASSERT(range<int>(result.get_green(), 255, 1));
		CPPUNIT_ASSERT(range<int>(result.get_blue(), 255, 1));
		CPPUNIT_ASSERT(range<int>(result.get_alpha(), 256/2, 1));

		src = risa_gl::pixel(255/4, 128/4, 64/4, 256/4);
		oper(&src, &result);
		//離散数での計算なのでこれくらいは誤差出てしまうなぁ・・・
		CPPUNIT_ASSERT(range<int>(result.get_red(), 255, 3));
		CPPUNIT_ASSERT(range<int>(result.get_green(), 128, 1));
		CPPUNIT_ASSERT(range<int>(result.get_blue(), 64, 1));
		CPPUNIT_ASSERT(range<int>(result.get_alpha(), 256/4, 1));
		
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( add_alpha_to_alpha_operator_test );
