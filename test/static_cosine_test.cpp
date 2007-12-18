#include <cppunit/extensions/HelperMacros.h>
#include <math/cosine.hpp>
#include <cmath>
#include <iostream>

class cosine_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(cosine_test);
	CPPUNIT_TEST(differTest);
	CPPUNIT_TEST_SUITE_END();

public:

	void differTest()
	{
		for (float v = -1.f; v < 1.f; v+= 0.01f)
		{
			CPPUNIT_ASSERT(
				std::abs(std::cos(v) -
						 risa_gl::math::cosine<float>::get(v)) < 0.01f);
		}
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( cosine_test );
